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
    
    int jpegs = 0;
    
    // This line was taken from a GitHub repo, and helped with conditions
    // inside the do while loop
    FILE *fw = NULL;
    
    BYTE buffer[512];
    
    do
    {
        fread(buffer, 512, 1, inptr);
        if (buffer[0] == 0xff &&
            buffer[1] == 0xd8 &&
            buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            // another helpful line from a GitHub repo.
            // makes sense, if there was a JPEG transfer in progress, close it
            if (fw !=NULL)
            {
                fclose(fw);
            }
            
            // originally had this at 7, think that caused issues.
            char fn[8];
            sprintf(fn, "%03i.jpg", jpegs);

            // If the file pointer is declared outside the block, you can just
            // keep reassigning it.
            fw = fopen(fn, "w");
            jpegs ++;
        }
        
        // Found this on a GitHub repo, I like the simplicity of a single
        // if statment to check if a JPEG transfer is in progress.
        if (fw != NULL)
        {
            fwrite(buffer, 512, 1, fw);
        }
    }
    while (!feof(inptr));

    // close infile
    fclose(inptr);

    // success
    return 0;
}
