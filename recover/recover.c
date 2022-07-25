#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
// #include <cs50.h>

const int block_size = 512;

int main(int argc, char *argv[])
{
    uint8_t bytes[block_size];

    if (argc != 2)
    {
        printf("./recover IMAGE\n");
        return 1;
    }

    FILE *input = fopen(argv[1], "r");

    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    int num_jpgs = 0;
    char *filename = malloc(8 * sizeof(char));
    //checks to see if the file still has more data
    sprintf(filename, "000.jpg");
    FILE *output = fopen(filename, "w");
    while (fread(&bytes, sizeof(uint8_t), block_size, input) == block_size)
    {
        //checks the first 4 btyes of the file to see of it is a jpg.The & 0xf0 is a bitwise operator that means only the first four bits or ints of the index are checked
        if (bytes[0] == 0xff && bytes[1] == 0xd8 && bytes[2] == 0xff && (bytes[3] & 0xf0) == 0xe0)
        {
            if (num_jpgs == 0)
            {
                fwrite(bytes, sizeof(uint8_t), block_size, output);
                num_jpgs++;
            }
            else
            {
                //if a jpeg is found after the first one, the original file is closed and data is written to a new file
                sprintf(filename, "%03i.jpg", num_jpgs);
                num_jpgs++;
                fclose(output);
                output = fopen(filename, "w");
                fwrite(bytes, sizeof(uint8_t), block_size, output);
            }
        }
        else
        {
            //if a jpeg was found more data is written to the file until the next jpeg is found
            if (num_jpgs > 0)
            {
                fwrite(bytes, sizeof(uint8_t), block_size, output);
            }
        }
    }
    fclose(input);
    free(filename);
}
