#include "helpers.h"
#include <math.h>
#include <stdio.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int grayscale = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);

            image[i][j].rgbtRed = grayscale;
            image[i][j].rgbtGreen = grayscale;
            image[i][j].rgbtBlue = grayscale;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            int temp_red = image[i][j].rgbtRed;
            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;
            image[i][width - j - 1].rgbtRed = temp_red;

            int temp_green = image[i][j].rgbtGreen;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
            image[i][width - j - 1].rgbtGreen = temp_green;

            int temp_blue = image[i][j].rgbtBlue;
            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;
            image[i][width - j - 1].rgbtBlue = temp_blue;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int original_red[height][width];
    int original_green[height][width];
    int original_blue[height][width];

    //stores the orginal rgb values of the image in 3 different arrays
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            original_red[i][j] = image[i][j].rgbtRed;
            original_green[i][j] = image[i][j].rgbtGreen;
            original_blue[i][j] = image[i][j].rgbtBlue;
        }
    }
    for (int k = 0; k < height; k++)
    {
        for (int l = 0; l < width; l++)
        {
            int combined_red = 0;
            int combined_green = 0;
            int combined_blue = 0;
            float num_values = 0.0;
            for (int y = -1; y < 2; y++)
            {
                for (int x = -1; x < 2; x++)
                {
                    //checks the adjecent indexs of the arrays by adding -1,0,1 to the x and y indexes
                    int xpos = l + x;
                    int ypos = k + y;
                    // checks is the index is invalid
                    if (xpos < 0 || xpos > width - 1 || ypos < 0 || ypos > height - 1)
                    {
                        //skips back to the begginng of the loop if the value is invalid
                        continue;
                    }
                    combined_red += original_red[ypos][xpos];
                    combined_green += original_green[ypos][xpos];
                    combined_blue += original_blue[ypos][xpos];
                    num_values++;
                }
            }
            image[k][l].rgbtRed = round(combined_red / num_values);
            image[k][l].rgbtGreen = round(combined_green / num_values);
            image[k][l].rgbtBlue = round(combined_blue / num_values);
        }
    }
    return;
}

//limits the RGB value from going higher than 255
int cap(int val)
{
    if (val > 255)
    {
        val = 255;
    }
    return val;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    //keys for the
    int Gx[3][3] =
    {
        {-1, 0, 1,},
        {-2, 0, 2,},
        {-1, 0, 1}
    };

    int Gy[3][3] =
    {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1}
    };

    int original_red[height][width];
    int original_green[height][width];
    int original_blue[height][width];

    //stores the orginal rgb values of the image in 3 different arrays
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            original_red[i][j] = image[i][j].rgbtRed;
            original_green[i][j] = image[i][j].rgbtGreen;
            original_blue[i][j] = image[i][j].rgbtBlue;
        }
    }
    for (int k = 0; k < height; k++)
    {
        for (int l = 0; l < width; l++)
        {
            int combined_red_x = 0;
            int combined_green_x = 0;
            int combined_blue_x = 0;
            int combined_red_y = 0;
            int combined_green_y = 0;
            int combined_blue_y = 0;
            int combined_red_final = 0;
            int combined_green_final = 0;
            int combined_blue_final = 0;


            //checks the adjecent indexs of the arrays by adding -1,0,1 to the x and y indexes
            for (int y = -1; y < 2; y++)
            {
                for (int x = -1; x < 2; x++)
                {
                    int xpos = l + x;
                    int ypos = k + y;

                    if (xpos < 0 || xpos > width - 1 || ypos < 0 || ypos > height - 1)
                    {
                        continue;
                    }

                    combined_red_x += original_red[ypos][xpos] * Gx[y + 1][x + 1];
                    combined_green_x += original_green[ypos][xpos] * Gx[y + 1][x + 1];
                    combined_blue_x += original_blue[ypos][xpos] * Gx[y + 1][x + 1];

                    combined_red_y += original_red[ypos][xpos] * Gy[y + 1][x + 1];
                    combined_green_y += original_green[ypos][xpos] * Gy[y + 1][x + 1];
                    combined_blue_y += original_blue[ypos][xpos] * Gy[y + 1][x + 1];

                    combined_red_final = cap(round(sqrt(((combined_red_x * combined_red_x) + (combined_red_y * combined_red_y)))));
                    combined_green_final = cap(round(sqrt(((combined_green_x * combined_green_x) + (combined_green_y * combined_green_y)))));
                    combined_blue_final = cap(round(sqrt(((combined_blue_x * combined_blue_x) + (combined_blue_y * combined_blue_y)))));
                }
            }
            image[k][l].rgbtRed = combined_red_final;
            image[k][l].rgbtGreen = combined_green_final;
            image[k][l].rgbtBlue = combined_blue_final;
        }
    }
    return;
}
