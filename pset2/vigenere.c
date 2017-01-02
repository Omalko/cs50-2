#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[1])
{
    if (argc != 2)
    {
        printf("Usage: ./vigenere str\n");
        return 1;
    }
    
    string pword = argv[1];
    
    int pword_len = strlen(pword);
    
    printf("plaintext: ");
    
    string ptext = get_string();
    
    int curr_pos = 0;
    int curr_pword_pos = 0;
    
    while (curr_pos < strlen(ptext))
    {
        int ascii = (int) ptext[curr_pos];
        // checks if curr_pos is a letter
        if ((ascii > 64 && ascii < 91) || (ascii > 96 && ascii < 123))
        {
            int ptext_ascii = (int) ptext[curr_pos];
            int pword_ascii = (int) pword[curr_pword_pos % pword_len];
            curr_pword_pos ++;
            
            printf("ptext_ascii is: %d\n", ptext_ascii);
            printf("pword_ascii is: %d\n", pword_ascii);
            printf("reg letter is: %c\n", ptext[curr_pos]);
            
            int ptext_lower = tolower(ptext_ascii);
            int pword_lower = tolower(pword_ascii);
            
            int pword_reg_index = pword_lower - 97;
            
            int shift = (int) pword_lower - (int) ptext_lower;
            
            printf("PWord_reg_index is: %d\n", pword_reg_index);
            printf("Shift is %d\n", shift);
            
            if (ptext_ascii > 64 && ptext_ascii < 91)
            {
                int result = ptext_ascii + pword_reg_index;
                if (result <= 90)
                {
                    printf("###########\n");
                    printf("%c", result);
                    printf("###########\n");
                }
            }
            else if (ptext_ascii > 96 && ptext_ascii < 123)
            {
                int result = ptext_ascii + pword_reg_index;
                if (result <= 122)
                {
                    printf("###########\n");
                    printf("%c", result);
                    printf("###########\n");
                }
            }
            
        }
        else
        {
            printf("%c\n", ptext[curr_pos]);
        }
        curr_pos ++;
    }
    
    /**
    for (int i=0; i<strlen(ptext); i++)
    {
        int ptext_ascii = (int) ptext[i];
        if ((ascii > 64 && ascii < 91) || (ascii > 96 && ascii < 123))
        {
            
        }
        int pword_ascii = (int) pword[i % pword_len];
        
        printf("ptext_ascii is: %d\n", ptext_ascii);
        printf("pword_ascii is: %d\n", pword_ascii);
        
    }
    **/
    
    printf("%s\n", argv[1]);
    printf("%s\n", pword);
}