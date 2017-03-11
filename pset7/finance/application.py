from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session, url_for
from flask_session import Session
from passlib.apps import custom_app_context as pwd_context
from tempfile import gettempdir
from datetime import datetime

from helpers import *

# configure application
app = Flask(__name__)

# ensure responses aren't cached
if app.config["DEBUG"]:
    @app.after_request
    def after_request(response):
        response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
        response.headers["Expires"] = 0
        response.headers["Pragma"] = "no-cache"
        return response

# custom filter
app.jinja_env.filters["usd"] = usd


# configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = gettempdir()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

@app.route("/")
@login_required
def index():
    
    rows = db.execute("SELECT * FROM users WHERE id = :id", id=session.get("user_id"))
    
    portfolio = get_portfolio(session.get("user_id"))
    
    cash = rows[0]['cash']
    
    grand_total = float(cash)
    
    for stock in portfolio:
        
        grand_total += float(stock['total'])
        
    return render_template('index.html', cash=cash, grand_total=grand_total, portfolio=portfolio)

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock."""
    
    if request.method == "GET":
        
        return render_template("buy.html")
        
    else:
        
        if not request.form.get("symbol") or not request.form.get("number"):
            
            return apology("Must input symbol and number")
            
        if float(request.form.get("number")) <= 0:
            
            return apology("Must input a number greater than 0")
            
        result = lookup(request.form.get("symbol"))
        
        if not result:
            
            return apology("Must input valid stock symbol")
        
        rows = db.execute("SELECT * FROM users WHERE id = :id", id=session.get("user_id"))
        
        total = float(result['price'])*float(request.form.get("number"))
        
        if float(rows[0]['cash']) < total:
            
            return apology("Insufficient funds.")
            
        db.execute("UPDATE users SET CASH = :cash WHERE id = :id", cash=float(rows[0]['cash']) - total, id=session.get("user_id"))
        
        db.execute("""INSERT INTO transactions (username, symbol, price, quantity, total, timestamp) 
                      VALUES (:username, :symbol, :price, :quantity, :total, :timestamp)""",
                    username=rows[0]['username'],
                    symbol=request.form.get("symbol"),
                    price=float(result['price']),
                    quantity=int(request.form.get("number")),
                    total = total,
                    timestamp = str(datetime.now()))
        
        return redirect(url_for("index"))           
        
        

@app.route("/history")
@login_required
def history():
    """Show history of transactions."""
    
    rows = db.execute("SELECT * FROM users WHERE id = :id", id=session.get("user_id"))
        
    history = db.execute("SELECT * FROM transactions WHERE username=:username", username=rows[0]["username"])
    
    return render_template("history.html", history=history)

@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in."""

    # forget any user_id
    session.clear()

    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")

        # ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password")

        # query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))

        # ensure username exists and password is correct
        if len(rows) != 1 or not pwd_context.verify(request.form.get("password"), rows[0]["hash"]):
            return apology("invalid username and/or password")

        # remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # redirect user to home page
        return redirect(url_for("index"))

    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")

@app.route("/logout")
def logout():
    """Log user out."""

    # forget any user_id
    session.clear()

    # redirect user to login form
    return redirect(url_for("login"))

@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    
    if request.method == "GET":
        
        return render_template("quote.html")
        
    else:
        
        result = lookup(request.form.get("symbol"))
        
        if not result:
            
            return apology("Not a valid stock symbol")
        
        return render_template("quoted.html", result=result)
        
@app.route("/register", methods=["GET", "POST"])
def register():
    
    if request.method == "POST":
        
        # ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")

        # ensure password was submitted
        elif not request.form.get("password") or not request.form.get("password-repeat"):
            return apology("must provide password")
            
        elif request.form.get("password") != request.form.get("password-repeat"):
            return apology("passwords must match")
            
        # query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))
        
        if len(rows) > 0:
            
            return apology("duplicate user")
            
        db.execute("INSERT INTO users (username, hash) VALUES (:username, :hash);", 
                    username=request.form.get("username"), 
                    hash=pwd_context.encrypt(request.form.get("password")))
                    
        return redirect(url_for('login'))
            
        
    
    else:
        
        return render_template("register.html")

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock."""
    
    if request.method == "GET":
        
        stocks = get_portfolio(session.get("user_id"))
                           
        return render_template("sell.html", stocks=stocks)
        
    else:
        
        result = lookup(request.form.get("symbol"))
        
        rows = db.execute("SELECT * FROM users WHERE id = :id", id=session.get("user_id"))
        
        stocks = db.execute("""SELECT symbol, SUM(quantity) as total_shares FROM transactions 
                           WHERE username=:username GROUP BY symbol""", username=rows[0]["username"])
                           
        for stock in stocks:
            
            if stock['symbol'] == request.form.get("symbol"):
                
                stock_to_sell = stock
        
        total = float(result['price'])*float(stock_to_sell['total_shares'])
            
        db.execute("UPDATE users SET CASH = :cash WHERE id = :id", cash=float(rows[0]['cash']) + total, id=session.get("user_id"))
        
        db.execute("""INSERT INTO transactions (username, symbol, price, quantity, total, timestamp) 
                      VALUES (:username, :symbol, :price, :quantity, :total, :timestamp)""",
                    username=rows[0]['username'],
                    symbol=request.form.get("symbol"),
                    price=float(result['price']),
                    quantity=int(stock_to_sell['total_shares'])*-1,
                    total = total,
                    timestamp = str(datetime.now()))
        
        return redirect(url_for("index"))
        
@app.route("/cash", methods=["GET", "POST"])
@login_required
def cash():
    """Add additional cash."""
    
    if request.method == "GET":
        
        return render_template("cash.html")
        
    else:
        
        if float(request.form.get("cash")) <= 0:
            
            return apology("Must input a number greater than zero")
        
        rows = db.execute("SELECT * FROM users WHERE id = :id", id=session.get("user_id"))
        
        db.execute("UPDATE users SET CASH = :cash WHERE id = :id", cash=float(rows[0]['cash']) + float(request.form.get("cash")), id=session.get("user_id"))
        
        return redirect(url_for("index"))
        