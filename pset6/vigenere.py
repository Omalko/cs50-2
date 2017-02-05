from sys import argv
from cs50 import get_string


def validate_input():
    
    '''Validate user input'''
    
    if len(argv) != 2:
        
        print("Usage: python vigenere k")
        
def calculate_shift(first, second):
    
    fl = first.lower()
    
    sl = second.lower()
    
    res = (ord(sl) - ord(fl))
    
    if res < 0:
        
        return (26 + res)
    
    else:
        
        return res
        
def apply_shift(shift, char):
    
    res = ord(char) + shift
    
    if res<=122 and res>=97:
        
        return chr(res)
        
    elif res >= 65 and res <=90:
        
        return chr(res)
    
    else:
        
        return chr((res % 122) + 96)
        

def main():
    
    validate_input()
    
    key = argv[1]
    
    print("plaintext: ", end="")
    
    plaintext = get_string()
    
    decrypted = ""
    
    count = 0
    
    for letter in plaintext:
        
        if letter != " ":
            
            shift = calculate_shift('a', key[count % len(key)])
            
            shifted_letter = apply_shift(shift, letter)
            
            decrypted += shifted_letter
            
            count += 1
        
        else:
            
            decrypted += " "
    
    print("ciphertext: " + decrypted)
            
    
if __name__ == "__main__":
    main()