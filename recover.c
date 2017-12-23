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

    // remember filename
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
        // setting start of jpeg as false each time new bytes are read
        start_of_a_new_jpeg = false;

        // find beginning of JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // if found new jpeg, setting flag to true
            start_of_a_new_jpeg = true;
            jpeg_count++;
        }

        // whenever new jpeg found, will close the file and open a new file
        if (start_of_a_new_jpeg)
        {
            if ( img != NULL )
            {
                fclose(img);
            }

            sprintf(filename, "%03i.jpg", jpeg_count);
            img = fopen(filename, "w");

        }

        // will keep appending bytes to the already opened file
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