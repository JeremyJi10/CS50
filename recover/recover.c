#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }
    else
    {
        FILE* card = fopen(argv[1], "r");
        FILE* image = NULL;
        int num = 0; //counter used to update names of image file
        BYTE block[512];
        char filename[8];

        while (fread(block, sizeof(BYTE), 512, card) == 512)
        {
            //check jpeg header
            if (block[0] == 0xff && block[1] == 0xd8 && block[2] == 0xff && (block[3] & 0xf0) == 0xe0)
            {
                //check whether it's the first jpeg file in 'card.raw', and close last recovered jpeg if it's not the first one
                if (num > 0)
                {
                    fclose(image);
                }
                sprintf(filename, "%03i.jpg", num);
                image = fopen(filename, "a");
                fwrite(block, sizeof(BYTE), 512, image);
                num += 1;
            }
            //check if this non-header block comes after the first block of all saved images
            else if (num > 0)
            {
                fwrite(block, sizeof(BYTE), 512, image);
            }
        }
        fclose(image);
        fclose(card);
        return 0;
    }
}
