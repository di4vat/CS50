/********************************************************************************
 * whodunit.c
 *
 * Divine Attipoe
 * divineattipoe@gmail.com
 *
 * A solution to cs50 pset 4, 
 *******************************************************************************/
       
#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 3)
    {
        printf("Usage: ./whodunit clue.bmp verdict.bmp\n");
        return 1;
    }

     /* remember filenames
       char* clue_ptr = argv[1];
       char* verdict_ptr = argv[2];
    */
   
    // open clue.bmp file 
    FILE* clue_ptr = fopen("clue.bmp", "r");
    if (clue_ptr == NULL)
    {
        printf("Could not open %s.\n", "clue.bmp");
        return 2;
    }

    // open verdict.bmp file
    FILE* verdict_ptr = fopen("verdict.bmp", "w");
    if (verdict_ptr == NULL)
    {
        fclose(clue_ptr);
        fprintf(stderr, "Could not create %s.\n", "verdict.bmp");
        return 3;
    }

    // read clue.bmp BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, clue_ptr);
    
    // read clue.bmp BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, clue_ptr);

    // ensure clue.bmp is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(verdict_ptr);
        fclose(clue_ptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // write verdict.bmp's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, verdict_ptr);

    // write verdict.bmp's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, verdict_ptr);

    // determine padding for scanlines
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // iterate over clue.bmp scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // iterate over pixels in scanline
        for (int j = 0; j < bi.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from clue.bmp
            fread(&triple, sizeof(RGBTRIPLE), 1, clue_ptr);

            // write RGB triple to verdict.bmp
           if (triple.rgbtRed > 235)
            {
                triple.rgbtBlue = 0x30;
                triple.rgbtGreen = 0x30;
                triple.rgbtRed = 0x10;
            }      
            
             fwrite(&triple, sizeof(RGBTRIPLE), 1, verdict_ptr);
            }
        // skip over padding, if any
        fseek(clue_ptr, padding, SEEK_CUR);

        // then add it back (to demonstrate how)
        for (int k = 0; k < padding; k++)
        {
            fputc(0x00, verdict_ptr);
        }
       }

    // close clue.bmp
    fclose(clue_ptr);

    // close verdict.bmp
    fclose(verdict_ptr);

    // that's all folks
    return 0;
    }
    
