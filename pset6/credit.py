from cs50 import get_int

def digit_sum(int_digit):
    
    small_list = []
    
    str_digit = str(int_digit)
    
    for digit in str_digit:
        
        small_list.append(int(digit))
        
    return sum(small_list)

def main():

    ready = False
    
    while not ready:
        
        print("Number: ", end="")
        
        number = get_int()
        
        if number > 0:
            
            ready = True
            
    digit_list = []
    
    for digit in str(number):
        
        digit_list.append(int(digit))
        
    
    checksum = 0
    
    curr_index = 0
    
    for digit in reversed(digit_list):
        
        if curr_index % 2 != 0:
            
            double = digit*2
            
            checksum += digit_sum(double)
            
            curr_index += 1
            
        else:
            
            checksum += digit_sum(digit)
            
            curr_index += 1
            
    if checksum % 10 != 0:
        
        print("INVALID")
    
    if digit_list[0] == 4:
        
        print("VISA")
    
    elif digit_list[0] == 5:
        
        print("MASTERCARD")
        
    elif digit_list[0] == 3:
        
        print("AMEX")
        
if __name__ == "__main__":
    main()