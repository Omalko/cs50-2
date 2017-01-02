#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main(int argc, string argv[1])
{
    if (argc != 2) 
    {
        printf("Usage: ./caesar k\n");
        return 1;
    }
    int argv_to_int = atoi(argv[1]);
    int shift = argv_to_int % 26;
    printf("plaintext: ");
    string ptext = get_string();
    printf("ciphertext: ");
    for (int i=0; i<strlen(ptext); i++)
    {
        int ascii = (int) ptext[i];
        // check if uppercase letter
        if (ascii > 64 && ascii < 91)
        {
            int result = ascii + shift;
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
        else if (ascii > 96 && ascii < 123)
        {
            int result = ascii + shift;
            if (result <= 122)
            {
                printf("%c", result);
            }
            else
            {
                int zshift = result - 122;
                printf("%c", zshift + 96);
            }
        }
        else
        {
            printf("%c", ascii);
        }
    }
    //printf("\n");
    return 0;
}