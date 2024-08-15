#include <complex.h>
#include <tgmath.h>
#include <stdio.h>
#include <stdlib.h>

// Defining the size of the screen.
#define Y 1080
#define X 1920

typedef struct pixel
{
    int x;
    int y;
    int color[3];
} pixel_t;

// Recursive function to provide the iterative every 100th
// f^n (0) for every pixel on the screen.
pixel_t Mandel(double _Complex c,
               double _Complex t,
               int counter)
{

    // To eliminate out of bound values.
    if (cabs(t) > 4)
    {
        int color = -(int)(128 - 128 * cabs(t) / cabs(c)) % 255;
        pixel_t pixel = {creal(c) * X / 4 + X / 2,
                         cimag(c) * Y / 2 + Y / 2,
                         {color, color, color}};
        return pixel;
    }

    // To put about the end of the fractal,
    // the higher the value of the counter,
    // The more accurate the fractal is generated,
    // however, higher values cause
    // more processing time.
    if (counter == 100)
    {
        int color = 255 * (int)(cabs((t * t)) / cabs((t - c) * c)) % 255;
        pixel_t pixel = {creal(c) * X / 4 + X / 2,
                         cimag(c) * Y / 2 + Y / 2,
                         {color, 0, 0}};
        return pixel;
    }

    // recursively calling Mandle with increased counter
    // and passing the value of the squares of t into it.
    return Mandel(c, cpow(t, 2) + c, counter + 1);
}

void MandelSet(int ***image)
{
    // Calling Mandle function for every
    // point on the screen.
    for (double x = -2; x < 2; x += 0.0015)
    {
        for (double y = -1; y < 1; y += 0.0015)
        {
            double _Complex temp = x + y * _Complex_I;
            pixel_t pixel = Mandel(temp, 0, 0);
            image[pixel.x][pixel.y][0] = pixel.color[0];
            image[pixel.x][pixel.y][1] = pixel.color[1];
            image[pixel.x][pixel.y][2] = pixel.color[2];
        }
    }
}

int ***malloc_image()
{
    int ***image = (int ***)malloc(sizeof(int **) * X);

    for (int i = 0; i < X; i++)
    {
        image[i] = (int **)malloc(sizeof(int *) * Y);
    }

    for (int i = 0; i < X; i++)
    {
        for (int j = 0; j < Y; j++)
        {
            image[i][j] = (int *)malloc(sizeof(int) * 3);
        }
    }

    return image;
}

int ***img;

void free_image()
{

    for (int i = 0; i < X; i++)
    {
        for (int j = 0; j < Y; j++)
        {
            free(img[i][j]);
        }
    }
    for (int i = 0; i < X; i++)
    {
        free(img[i]);
    }

    free(img);
}

int get_pixel(int x, int y, int z)
{
    return img[x][y][z];
}

void build_image()
{
    int ***image = malloc_image();
    MandelSet(image);
    img = image;
}

int main(int argc, char const *argv[])
{
    build_image();
    return 0;
}
