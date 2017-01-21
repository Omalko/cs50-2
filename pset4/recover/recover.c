#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE; 

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover infile\n");
        return 1;
    }
    
    // remember filenames
    char *infile = argv[1];

    // open input file 
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }
    
    BYTE buffer[512];
    
    int jpegs = 0;
    
    do
    {
        fread(buffer, 512, 1, inptr);
        if (buffer[0] == 0xff &&
            buffer[1] == 0xd8 &&
            buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            printf("Found a jpeg!\n");
            jpegs ++;
        }
    }
    while (!feof(inptr));
    printf("Total: %d\n", jpegs);
    /*
    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }
    */

    // close infile
    fclose(inptr);

    // success
    return 0;
}
