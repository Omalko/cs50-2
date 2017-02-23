from flask import Flask, redirect, render_template, request, url_for

import helpers
from analyzer import Analyzer
import os
from sys import path

# absolute paths to lists
positives = os.path.join(path[0], "positive-words.txt")
negatives = os.path.join(path[0], "negative-words.txt")

# instantiate analyzer
analyzer = Analyzer(positives, negatives)

app = Flask(__name__)

@app.route("/")
def index():
    return render_template("index.html")

@app.route("/search")
def search():

    # validate screen_name
    screen_name = request.args.get("screen_name", "").lstrip("@")
    if not screen_name:
        return redirect(url_for("index"))

    # get screen_name's tweets
    tweets = helpers.get_user_timeline(screen_name)

    # TODO
    positives, negatives, neutrals = 0, 0, 0

    for tweet in tweets:
        
        score = analyzer.analyze(tweet)
        
        if score == 1:
            
            positives += 1
            
        elif score == -1:
            
            negatives +=1
            
        else:
            
            neutrals +=1
            
    positive = positives / len(tweets)
    negative = negatives / len(tweets)
    neutral = neutrals / len(tweets)
        
    
    # generate chart
    chart = helpers.chart(positive, negative, neutral)

    # render results
    return render_template("search.html", chart=chart, screen_name=screen_name)
