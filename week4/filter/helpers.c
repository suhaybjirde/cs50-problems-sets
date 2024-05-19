#include <math.h>

#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int average = round((image[height][width].rgbtRed + image[height][width].rgbtBlue +image[height][width].rgbtGreen) / 3);

            image[i][j].rgbtBlue = average;
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = calulate_bsepia(image[i][j].rgbtRed, image[i][j].rgbtGreen, image[i][j].rgbtBlue);
            image[i][j].rgbtGreen = calulate_gsepia(image[i][j].rgbtRed, image[i][j].rgbtGreen, image[i][j].rgbtBlue);
            image[i][j].rgbtRed = calulate_rsepia(image[i][j].rgbtRed, image[i][j].rgbtGreen, image[i][j].rgbtBlue);
        }
    }

    return;
}

int calulate_rsepia(int red, int green, int blue)
{
    int sepiaRed = round((.393 * red) + (.769 * green) + (.189 * blue)); 

    if (sepiaRed > 255)
        sepiaRed = 255;
    return sepiaRed;
}
int calulate_bsepia(int red, int green, int blue)
{
    int sepiaBlue = round((.272 * red) + (.534 * green) + (.131 * blue));
    if (sepiaBlue > 255)
        sepiaBlue = 255;
    return sepiaBlue;
}
int calulate_gsepia(int red, int green, int blue)
{
    int sepiaGreen = round((.349 * red) + (.686 * green) + (.168 * blue)); 
    if (sepiaGreen > 255)
        sepiaGreen = 255;
    return sepiaGreen;
}

// Reflect image horizontally
// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        reverse(image[i], width);
    }
    return;
}

void reverse(RGBTRIPLE array[], int len)
{
    int start = 0;
    int end = len - 1;

    while (start < end)
    {
        RGBTRIPLE temp = array[start];
        array[start] = array[end];
        array[end] = temp;

        start++;
        end--;
    }
}


// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; i < width; j++)
        {
            int Ared = 0;
            int Ablue = 0;
            int Agreen = 0;
            int count = 0;


            for (int k = -1; k <= 1; k++)
            {
                for (int l = -1; l <= 1; l++)
                {
                    if (k + i >= 0 && k + i < height && l + j >= 0 && l + j < width)
                    {
                        Ared += image[i + k][j + l].rgbtRed;
                        Agreen += image[i + k][j + l].rgbtGreen;
                        Ablue += image[i + k][j + l].rgbtBlue;
                        count++;
                    }
                }
            }

            image[i][j].rgbtBlue = round((float) Ablue / count);
            image[i][j].rgbtGreen = round((float) Agreen / count);
            image[i][j].rgbtRed = round((float) Ared / count);
        }
    }
    return;
}