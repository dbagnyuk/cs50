/**
 * copy.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./copy factor infile outfile\n");
        return 1;
    }

    // ensure that the factr is number between 1 and 100
    char* key = argv[1];
    int i = 0;
    while (key[i] != '\0')
    {
        if (isalpha(key[i]) != 0)
        {
            printf ("Usage: second argument shoud be a number between 1 and 100\n");
            return 1;
        }
        i++;
    }
    // remember factor and filenames
    int factor = atoi(argv[1]);
    char* infile = argv[2];
    char* outfile = argv[3];
    
    // ensure that the factr is number between 1 and 100
    if (factor < 1 || factor > 100)
    {
        printf ("Usage: second argument shoud be a number between 1 and 100\n");
        return 1;
    }

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf_n, bf_o;
    fread(&bf_o, sizeof(BITMAPFILEHEADER), 1, inptr);
    bf_n = bf_o;

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi_n, bi_o;
    fread(&bi_o, sizeof(BITMAPINFOHEADER), 1, inptr);
    bi_n = bi_o;

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf_n.bfType != 0x4d42 || bf_n.bfOffBits != 54 || bi_n.biSize != 40 || 
        bi_n.biBitCount != 24 || bi_n.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format of output file.\n");
        return 4;
    }

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf_o.bfType != 0x4d42 || bf_o.bfOffBits != 54 || bi_o.biSize != 40 || 
        bi_o.biBitCount != 24 || bi_o.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format of input file.\n");
        return 4;
    }

    // determine padding for scanlines
    int padding_n = (4 - (bi_o.biWidth * sizeof(RGBTRIPLE) * factor) % 4) % 4;
    int padding_o = (4 - (bi_o.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // multiplay the input parametr on factor
    bi_n.biWidth = bi_o.biWidth * factor;
    bi_n.biHeight = bi_o.biHeight * factor;
    bi_n.biSizeImage = ((bi_o.biWidth * sizeof(RGBTRIPLE) * factor) + padding_n) * (abs(bi_o.biHeight) * factor);
    bf_n.bfSize = bi_n.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

//biSizeImage = (sizeof(RGBTRIPLE) * bi_o.biWidth + padding_n) * bi_o.biHeight
//bfSize = biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

//    bi_n.biWidth = bi_o.biWidth * factor;
//    bi_n.biHeight = bi_o.biHeight * factor;
//    bi_n.biSizeImage = bi_o.biSizeImage * factor;
//    bf_n.bfSize = bi_o.biSize * factor;

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf_n, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi_n, sizeof(BITMAPINFOHEADER), 1, outptr);

    int t = factor;
        
    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi_o.biHeight); i < biHeight; i++)
    {
        // iterate over pixels in scanline
        for (int j = 0; j < bi_o.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;
            
            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            // write RGB triple to outfile
            for (int k = 0; k < factor; k++)
            {
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
            }
        }
        --t;

        // skip over padding, if any
        fseek(inptr, padding_o, SEEK_CUR);

        // then add it back (to demonstrate how)
        for (int k = 0; k < padding_n; k++)
        {
            fputc(0x00, outptr);
        }
        
        if (t != 0)
        {
            fseek(inptr, -(bi_o.biWidth * sizeof(RGBTRIPLE) + padding_o), SEEK_CUR);
            --i;
        }
        else
        {
            t = factor;
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
