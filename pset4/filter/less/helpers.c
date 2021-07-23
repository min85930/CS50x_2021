#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            int b = image[row][col].rgbtBlue;
            int g = image[row][col].rgbtGreen;
            int r = image[row][col].rgbtRed;
            int grayscale = (int) round((b + g + r) / 3.0);

            image[row][col].rgbtBlue = grayscale;
            image[row][col].rgbtGreen = grayscale;
            image[row][col].rgbtRed = grayscale;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            int b = image[row][col].rgbtBlue;
            int g = image[row][col].rgbtGreen;
            int r = image[row][col].rgbtRed;
            int sepia_b = (int) round(0.131 * b + 0.534 * g + 0.272 * r);
            int sepia_g = (int) round(0.168 * b + 0.686 * g + 0.349 * r);
            int sepia_r = (int) round(0.189 * b + 0.769 * g + 0.393 * r);

            if (sepia_b > 255)
            {
                sepia_b = 255;
            }
            if (sepia_g > 255)
            {
                sepia_g = 255;
            }
            if (sepia_r > 255)
            {
                sepia_r = 255;
            }

            image[row][col].rgbtBlue = sepia_b;
            image[row][col].rgbtGreen = sepia_g;
            image[row][col].rgbtRed = sepia_r;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width / 2; col++)
        {
            int tmp_b = image[row][col].rgbtBlue;
            int tmp_g = image[row][col].rgbtGreen;
            int tmp_r = image[row][col].rgbtRed;

            image[row][col].rgbtBlue = image[row][width - col - 1].rgbtBlue;
            image[row][col].rgbtGreen = image[row][width - col - 1].rgbtGreen;
            image[row][col].rgbtRed = image[row][width - col - 1].rgbtRed;

            image[row][width - col - 1].rgbtBlue = tmp_b;
            image[row][width - col - 1].rgbtGreen = tmp_g;
            image[row][width - col - 1].rgbtRed = tmp_r;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp[height][width];

    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            tmp[row][col] = image[row][col];
        }
    }

    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            int sumb = 0;
            int sumg = 0;
            int sumr = 0;
            int count = 0;

            for (int r = row - 1; r <= row + 1; r++)
            {
                for (int c = col - 1; c <= col + 1; c++)
                {
                    if (r < 0 || r >= height || c < 0 || c >= width)
                    {
                        // out of range
                        continue;
                    }
                    else
                    {
                        sumb += tmp[r][c].rgbtBlue;
                        sumg += tmp[r][c].rgbtGreen;
                        sumr += tmp[r][c].rgbtRed;
                        count++;
                    }
                }
            }

            image[row][col].rgbtBlue = (int) round(sumb / (float) count);
            image[row][col].rgbtGreen = (int) round(sumg / (float) count);
            image[row][col].rgbtRed = (int) round(sumr / (float) count);
        }

    }
    return;
}
