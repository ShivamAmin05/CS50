#include "helpers.h"
#include <stdio.h>
#include <math.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            int grayscale = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);

            image[i][j].rgbtRed = grayscale;
            image[i][j].rgbtGreen = grayscale;
            image[i][j].rgbtBlue = grayscale;
        }
    }
    return;
}

//limits the RGB value from going higher than 255
int cap(int val)
{
    if(val > 255)
    {
        val = 255;
    }
    return val;
}
// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
     for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            int sepia_red = cap(round((image[i][j].rgbtRed * 0.393) + (image[i][j].rgbtGreen * 0.769) + (image[i][j].rgbtBlue * 0.189)));
            int sepia_green = cap(round((image[i][j].rgbtRed * 0.349) + (image[i][j].rgbtGreen * 0.686) + (image[i][j].rgbtBlue * 0.168)));
            int sepia_blue = cap(round((image[i][j].rgbtRed * 0.272) + (image[i][j].rgbtGreen * 0.534) + (image[i][j].rgbtBlue * 0.131)));

            image[i][j].rgbtRed = sepia_red;
            image[i][j].rgbtGreen = sepia_green;
            image[i][j].rgbtBlue = sepia_blue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width/2; j++)
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

// Blurs image by adding together the RGB values of the surroudning pixels and avergaing them out to make the image look less sharp
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int original_red[height][width];
    int original_green[height][width];
    int original_blue[height][width];

    //stores the orginal rgb values of the image in 3 different arrays
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            original_red[i][j] = image[i][j].rgbtRed;
            original_green[i][j] = image[i][j].rgbtGreen;
            original_blue[i][j] = image[i][j].rgbtBlue;
        }
    }
    for(int k = 0; k < height; k++)
    {
        for(int l = 0; l < width; l++)
        {
            int combined_red = 0;
            int combined_green = 0;
            int combined_blue = 0;
            float num_values = 0.0;
            for(int y = -1; y < 2; y++)
            {
                for(int x = -1; x < 2; x++)
                {
            //checks the adjecent indexs of the arrays by adding -1,0,1 to the x and y indexes
                   int xpos = l + x;
                   int ypos = k + y;
                // checks is the index is invalid
                if(xpos < 0 || xpos > width - 1 || ypos < 0 || ypos > height -1)
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