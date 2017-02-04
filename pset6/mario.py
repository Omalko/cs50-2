from cs50 import get_int

ready = False

while(not ready):
    
    print("Height: ", end="")
    
    height = get_int()
    
    if (height >= 0 and height <= 23):
        
        ready = True
        
for i in range(height):
    
    blank_space = height - i - 1
    
    print(" " * blank_space, end="")
    print("#" * ( i + 1 ), end="")
    print("  ", end="")
    print("#" * ( i + 1 ), end="")
    print(" " * blank_space)




