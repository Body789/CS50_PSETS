#include "helpers.h"
#include <math.h>
#include <stdlib.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    //loop for all pixels
    for (int i = 0; i < height; i++)
    {
        //loop for all pixels
        for (int j = 0; j < width; j++)
        {
            //finding average
            int average = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            //changing average
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    //rows loop
    for (int i = 0; i < height; i++)
    {
        //width loop
        for (int j = 0; j < width; j++)
        {
            //storing main colors
            //red
            int originalRed = image[i][j].rgbtRed;
            //green
            int originalGreen = image[i][j].rgbtGreen;
            //blue
            int originalBlue = image[i][j].rgbtBlue;
            //saving sepia colors
            int sepiaRed = round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue);
            //checking if value exceeded maximum
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            int sepiaGreen = round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue);
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            int sepiaBlue = round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue);
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            //changing values
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //loop for all rows
    for (int i = 0; i < height; i++)
    {
        //loop for half width
        for (int j = 0; j < width / 2.0; j++)
        {
            //temp for every color
            int t = image[i][j].rgbtRed;
            //swaping
            image[i][j].rgbtRed = image[i][width - 1 - j].rgbtRed;
            //correct middle
            if (width % 2 == 0 || (width % 2 != 0 && width - 1 - j != round((width - 1) / 2.0)))
            {
                image[i][width - 1 - j].rgbtRed = t;
            }
            //again
            t = image[i][j].rgbtGreen;
            image[i][j].rgbtGreen = image[i][width - 1 - j].rgbtGreen;
            if (width % 2 == 0 || width - 1 - j != round((width - 1) / 2.0))
            {
                image[i][width - 1 - j].rgbtGreen = t;
            }
            t = image[i][j].rgbtBlue;
            image[i][j].rgbtBlue = image[i][width - 1 - j].rgbtBlue;
            if (width % 2 == 0 || width - 1 - j != round((width - 1) / 2.0))
            {
                image[i][width - 1 - j].rgbtBlue = t;
            }
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //create a temporary image to implement blurred algorithm on it.
    RGBTRIPLE temp[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int total_Red, total_Blue, total_Green;
            total_Red = total_Blue = total_Green = 0;
            float counter = 0.00;

            //Get the neighbouring pexels
            for (int x = -1; x < 2; x++)
            {
                for (int y = -1; y < 2; y++)
                {
                    int currentX = i + x;
                    int currentY = j + y;

                    //check for valid neighbouring pexels
                    if (currentX < 0 || currentX > (height - 1) || currentY < 0 || currentY > (width - 1))
                    {
                        continue;
                    }

                    //Get the image value
                    total_Red += image[currentX][currentY].rgbtRed;
                    total_Green += image[currentX][currentY].rgbtGreen;
                    total_Blue += image[currentX][currentY].rgbtBlue;

                    counter++;
                }

                //do the average of neigbhouring pexels
                temp[i][j].rgbtRed = round(total_Red / counter);
                temp[i][j].rgbtGreen = round(total_Green / counter);
                temp[i][j].rgbtBlue = round(total_Blue / counter);
            }
        }

    }

    //copy the blurr image to the original image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
        }
    }
    return;
}
