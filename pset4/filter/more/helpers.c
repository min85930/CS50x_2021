#include "helpers.h"
#include "math.h"

int limit(int value);
int Pos(int value, int start, int end);

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

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width / 2; col++)
        {
            RGBTRIPLE tmp = image[row][col];

            image[row][col] = image[row][width - col - 1];

            image[row][width - col - 1] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp[height][width];
    // Copy image to tmp
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            tmp[row][col] = image[row][col];
        }
    }

    // Blur image each pixel
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            int sumb = 0;
            int sumg = 0;
            int sumr = 0;
            float count = 0;

            // From tmp to calaaulate nine grids b.g.r and count
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

            image[row][col].rgbtBlue = (int) round(sumb / count);
            image[row][col].rgbtGreen = (int) round(sumg / count);
            image[row][col].rgbtRed = (int) round(sumr / count);
        }

    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    RGBTRIPLE tmp[height][width];
    // Copy image to tmp
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
            int gx_b = 0;
            int gx_g = 0;
            int gx_r = 0;

            int gy_b = 0;
            int gy_g = 0;
            int gy_r = 0;

            // From tmp to calaaulate nine grids b.g.r and count
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
                        int PosX = Pos(r, row - 1, row + 1);
                        int PosY = Pos(c, col - 1, col + 1);

                        gx_b += (tmp[r][c].rgbtBlue * gx[PosX][PosY]);
                        gx_g += (tmp[r][c].rgbtGreen * gx[PosX][PosY]);
                        gx_r += (tmp[r][c].rgbtRed * gx[PosX][PosY]);

                        gy_b += (tmp[r][c].rgbtBlue * gy[PosX][PosY]);
                        gy_g += (tmp[r][c].rgbtGreen * gy[PosX][PosY]);
                        gy_r += (tmp[r][c].rgbtRed * gy[PosX][PosY]);
                    }
                }
            }

            image[row][col].rgbtBlue = limit(round(sqrt(gx_b * gx_b + gy_b * gy_b)));
            image[row][col].rgbtGreen = limit(round(sqrt(gx_g * gx_g + gy_g * gy_g)));
            image[row][col].rgbtRed = limit(round(sqrt(gx_r * gx_r + gy_r * gy_r)));
        }

    }
    return;
}

// Get Gx or Gy Matrix Position
int Pos(int value, int start, int end)
{
    int pos = 0;

    for (int i = start; i <= end; i++)
    {
        if (i == value)
        {
            break;
        }
        pos++;
    }
    return pos;
}

// Limit RGB number in 255
int limit(int value)
{
    if (value > 255)
    {
        return 255;
    }
    return value;
}
