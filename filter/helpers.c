#include <math.h>
#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int avg;
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            avg = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.000);

            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtBlue = avg;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        int h_width = width / 2;

        for (int j = 0; j < h_width; j++)
        {
            //create three variables used to record original rgb values of the left one pixel of a horizontally symmetrical pixel pair
            int l_red = image[i][j].rgbtRed;
            int l_green = image[i][j].rgbtGreen;
            int l_blue = image[i][j].rgbtBlue;

            //replace rgb values of left pixel with those of the horizontally symmetrical one
            image[i][j].rgbtRed = image[i][width - 1 - j].rgbtRed;
            image[i][j].rgbtGreen = image[i][width - 1 - j].rgbtGreen;
            image[i][j].rgbtBlue = image[i][width - 1 - j].rgbtBlue;

            //replace rgb values of right pixel with original values of the horizontally symmetrical one
            image[i][width - 1 - j].rgbtRed = l_red;
            image[i][width - 1 - j].rgbtGreen = l_green;
            image[i][width - 1 - j].rgbtBlue = l_blue;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //get a copy of original rgb values
    RGBTRIPLE image_c[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image_c[i][j].rgbtRed = image[i][j].rgbtRed;
            image_c[i][j].rgbtGreen = image[i][j].rgbtGreen;
            image_c[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
    }

    //make pixels blured (average of values of itself and the surrounding pixels)
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //capture the 3x3 grid centered by this pixel (firstly reset the number of counted pixels and create a array of integers with sum of rgb values)
            float count = 0.000;
            int sumRGB[3] = {0, 0, 0};

            for (int h = i - 1; h < i + 2; h++)
            {
                for (int w = j - 1; w < j + 2; w++)
                {
                    //count the number of valid pixels (in the range) and add corresponding rgb values to sumRGB
                    if (h >= 0 && h < height && w >= 0 && w < width)
                    {
                        count++;

                        sumRGB[0] += image_c[h][w].rgbtRed;
                        sumRGB[1] += image_c[h][w].rgbtGreen;
                        sumRGB[2] += image_c[h][w].rgbtBlue;
                    }
                }
            }

            //update blured rgb values of this pixel
            image[i][j].rgbtRed = round(sumRGB[0] / count);
            image[i][j].rgbtGreen = round(sumRGB[1] / count);
            image[i][j].rgbtBlue = round(sumRGB[2] / count);
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    //get a copy of original rgb values
    RGBTRIPLE image_c[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image_c[i][j].rgbtRed = image[i][j].rgbtRed;
            image_c[i][j].rgbtGreen = image[i][j].rgbtGreen;
            image_c[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
    }

    //reassign rgb values of each pixel (square root of Gx^2 + Gy^2)
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //create a new 3x3 grid centered by this pixel (image segment)
            RGBTRIPLE image_s[3][3];

            for (int h = i - 1; h < i + 2; h++)
            {
                for (int w = j - 1; w < j + 2; w++)
                {
                    //assign actual rgb values to valid pixels (in the range)
                    if (h >= 0 && h < height && w >= 0 && w < width)
                    {
                        image_s[h - i + 1][w - j + 1].rgbtRed = image_c[h][w].rgbtRed;
                        image_s[h - i + 1][w - j + 1].rgbtGreen = image_c[h][w].rgbtGreen;
                        image_s[h - i + 1][w - j + 1].rgbtBlue = image_c[h][w].rgbtBlue;
                    }
                    //assign 0 as rgb values to invalid pixels (out of range)
                    else
                    {
                        image_s[h - i + 1][w - j + 1].rgbtRed = 0;
                        image_s[h - i + 1][w - j + 1].rgbtGreen = 0;
                        image_s[h - i + 1][w - j + 1].rgbtBlue = 0;
                    }
                }
            }
        
            int Gx_r = image_s[0][2].rgbtRed - image_s[0][0].rgbtRed + 2 * (image_s[1][2].rgbtRed - image_s[1][0].rgbtRed) + image_s[2][2].rgbtRed - image_s[2][0].rgbtRed;
            int Gx_g = image_s[0][2].rgbtGreen - image_s[0][0].rgbtGreen + 2 * (image_s[1][2].rgbtGreen - image_s[1][0].rgbtGreen) + image_s[2][2].rgbtGreen - image_s[2][0].rgbtGreen;
            int Gx_b = image_s[0][2].rgbtBlue - image_s[0][0].rgbtBlue + 2 * (image_s[1][2].rgbtBlue - image_s[1][0].rgbtBlue) + image_s[2][2].rgbtBlue - image_s[2][0].rgbtBlue;
                    
            int Gy_r = image_s[2][0].rgbtRed - image_s[0][0].rgbtRed + 2 * (image_s[2][1].rgbtRed - image_s[0][1].rgbtRed) + image_s[2][2].rgbtRed - image_s[0][2].rgbtRed;
            int Gy_g = image_s[2][0].rgbtGreen - image_s[0][0].rgbtGreen + 2 * (image_s[2][1].rgbtGreen - image_s[0][1].rgbtGreen) + image_s[2][2].rgbtGreen - image_s[0][2].rgbtGreen; 
            int Gy_b = image_s[2][0].rgbtBlue - image_s[0][0].rgbtBlue + 2 * (image_s[2][1].rgbtBlue - image_s[0][1].rgbtBlue) + image_s[2][2].rgbtBlue - image_s[0][2].rgbtBlue;
                        
            //update rgb values of this pixel
            int newRGB[3] = {0, 0, 0};
            
            newRGB[0] = round(sqrt(Gx_r * Gx_r + Gy_r * Gy_r));
            newRGB[1] = round(sqrt(Gx_g * Gx_g + Gy_g * Gy_g));
            newRGB[2] = round(sqrt(Gx_b * Gx_b + Gy_b * Gy_b));
            
            for (int index = 0; index < 3; index++)
            {
                if (newRGB[index] > 255)
                {
                    newRGB[index] = 255;
                }
            }
            
            image[i][j].rgbtRed = newRGB[0];
            image[i][j].rgbtGreen = newRGB[1];
            image[i][j].rgbtBlue = newRGB[2];
        }
    }
            
    return;
}
