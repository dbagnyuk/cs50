/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Recovers JPEGs from a forensic image.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> // uint8_t
#include <string.h> // memcmp

#define BLOCK_SIZE 512 

int main(void)
{
    // TODO

    // file name for analyze
    char* infile = "card.raw";

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 1;
    }

    // for name of output files
    int fnum = -1;
    char* outfile = malloc(8);
    FILE* outptr = NULL;

    // two jpg headers
    uint8_t header1[4] = {0xff, 0xd8, 0xff, 0xe0};
    uint8_t header2[4] = {0xff, 0xd8, 0xff, 0xe1};

    // pointer for buffer size 512 bytes
    char* buffer = (char*)malloc(sizeof(char)*BLOCK_SIZE);

    // read until EOF
    while(!feof(inptr))
    {
        // read and check for size 512 bytes from infile to buffer
        if (fread(buffer, sizeof(char), BLOCK_SIZE, inptr) == BLOCK_SIZE)
        {
            // compare first 4 byte with jpg header if compare ok
            if(memcmp(buffer, header1, 4) == 0 || memcmp(buffer, header2, 4) == 0)
            {
                // close previous out file if exists
                if (outptr != NULL)
                {
                    fclose(outptr);
                }
                
                // create name for new output file
                fnum++;
                sprintf(outfile, "%03i.jpg", fnum);
                
                // open and check new output file
                outptr = fopen(outfile, "a");
                if (outptr == NULL)
                {
                    fclose(inptr);
                    fprintf(stderr, "Could not create %s.\n", outfile);
                    return 3;
                }

                // write buffer to new outfile
                fwrite(buffer, sizeof(char), BLOCK_SIZE, outptr);
            }
            // if first 4 byte is not jpg template and exists opened file
            else if (outptr != NULL)
            {
                // write buffer to already opened outfile
                fwrite(buffer, sizeof(char), BLOCK_SIZE, outptr);
            }
        }
     }

    // free memory for buffer
    free(buffer);
    
    // free memory for out file name
    free(outfile);

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
