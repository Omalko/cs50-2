#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

/**
 * Modified a function from 
 * http://stackoverflow.com/questions/29248585/c-checking-command-line-argument-is-integer-or-not
 * 
 **/
bool isNumber(string number)
{
    for (int i=0; i<strlen(number); i++)
    {
        if (isdigit(number[i]))
            return true;
    }
    return false;
}

int main(int argc, string argv[1])
{
    if (argc != 2)
    {
        printf("Usage: ./vigenere str\n");
        return 1;
    }
    if (isNumber(argv[1]))
    {
        printf("Usage: ./vigenere str\n");
        return 1;
    }
    
    string pword = argv[1];
    
    int pword_len = strlen(pword);
    
    printf("plaintext: ");
    
    string ptext = get_string();
    
    printf("ciphertext: ");
    
    int curr_pos = 0;
    int curr_pword_pos = 0;
    
    while (curr_pos < strlen(ptext))
    {
        int ascii = (int) ptext[curr_pos];
        // checks if curr_pos is a letter
        if ((ascii > 64 && ascii < 91) || (ascii > 96 && ascii < 123))
        {
            int pword_ascii = (int) pword[curr_pword_pos % pword_len];
            curr_pword_pos ++;

            int pword_lower = tolower(pword_ascii);
            
            int pword_reg_index = pword_lower - 97;
            

            //handle upper case
            if (ascii > 64 && ascii < 91)
            {
                int result = ascii + pword_reg_index;
                if (result <= 90)
                {
                    printf("%c", result);
                }
                else
                {
                    int zshift = result - 90;
                    printf("%c", zshift + 64);
                }
            }
            //handle lower case
            else if (ascii > 96 && ascii < 123)
            {
                int result = ascii + pword_reg_index;
                if (result <= 122)
                {
                    printf("%c", result);
                } else
                {
                    int zshift = result - 122;
                    printf("%c", zshift + 96);
                }
            }
            
        }
        else
        {
            printf("%c", ptext[curr_pos]);
        }
        curr_pos ++;
    }
    //printf("\n");
    return 0;
}