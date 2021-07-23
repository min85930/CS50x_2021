#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc == 2)
    {
        FILE *file = fopen(argv[1], "r");

        if (file == NULL)
        {
            printf("Could not open %s\n", argv[1]);
            return 1;
        }
        else
        {
            uint8_t buffer[512];
            FILE *img = NULL;
            char filename[8];
            int count = 0;

            while (fread(buffer, sizeof(uint8_t), 512, file))
            {
                // check start new jpeg header
                if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
                {
                    // close previous image
                    if (count != 0)
                    {
                        fclose(img);
                    }

                    sprintf(filename, "%03i.jpg", count);
                    img = fopen(filename, "w");
                    count++;
                }

                if (count != 0)
                {
                    fwrite(buffer, sizeof(uint8_t), 512, img);
                }
            }
            // Close image
            fclose(img);
        }
        // Close file
        fclose(file);
    }
    else
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    return 0;
}