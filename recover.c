#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

int main(int argc, char *argv[])
{

    typedef uint8_t  BYTE;
    // ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover card.raw\n");
        return 1;
    }

    // open memory card file

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

    char filename[8];
    int jpeg_count = -1;
    bool start_of_a_new_jpeg = false;
    FILE *img = NULL;

    while (fread(&buffer, sizeof(buffer), 1, inptr) > 0)
    {
        // read one chunk of 512 bytes in a buffer
        //fread(&buffer, 512, 1, inptr);
        start_of_a_new_jpeg = false;
        //printf("Reading %d", (int)fread(buffer, 512 , 1, inptr));

        // find beginning of JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            //printf("Reading new buffer %d %d %d %d\n", buffer[0], buffer[1], buffer[2], buffer[3]);
            start_of_a_new_jpeg = true;
            jpeg_count++;
        }

        // will not start till we found our first JPEG
        if (start_of_a_new_jpeg)
        {
            if ( img != NULL )
            {
                fclose(img);
            }

            sprintf(filename, "%03i.jpg", jpeg_count);
            img = fopen(filename, "w");


        }

        if ( img != NULL )
        {
            fwrite(&buffer, 512, 1, img);
        }


    }
    if (img != NULL)
    {
        fclose(img);
    }
    if ( inptr != NULL )
    {
        fclose(inptr);
    }
    return 0;

}