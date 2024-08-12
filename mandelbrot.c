#include <complex.h>
#include <tgmath.h>
#include <stdio.h>
#include <string.h>
 
// Defining the size of the screen.
#define Y 1080
#define X 1920
 
typedef struct out_pixel{
  int x;
  int y;
  int color[3];
}out_pixel_t;

// Recursive function to provide the iterative every 100th
// f^n (0) for every pixel on the screen.
out_pixel_t Mandle(double _Complex c,
           double _Complex t,
           int counter)
{
 
    // To eliminate out of bound values.
    if (cabs(t) > 4) {
        int color = 128 - 128 * cabs(t) / cabs(c);
        out_pixel_t pixel = {creal(c) * X / 4 + X / 2,
                             cimag(c) * Y / 2 + Y / 2,
                             {color, color, color}};
        return pixel;
    }
 
    // To put about the end of the fractal,
    // the higher the value of the counter,
    // The more accurate the fractal is generated,
    // however, higher values cause
    // more processing time.
    if (counter == 100) {
        int color = 255 * (cabs((t * t)) / cabs((t - c) * c));
        out_pixel_t pixel = {creal(c) * X / 4 + X / 2,
                             cimag(c) * Y / 2 + Y / 2,
                             {color, 0, 0}};
        return pixel;
    }
 
    // recursively calling Mandle with increased counter
    // and passing the value of the squares of t into it.
    return Mandle(c, cpow(t, 2) + c, counter + 1);
}
 
void MandleSet(int out_image[X][Y][3])
{
    int count = 0;
    
    // Calling Mandle function for every
    // point on the screen.
    for (double x = -2; x < 2; x += 0.0015) {
        for (double y = -1; y < 1; y += 0.0015) {
            double _Complex temp = x + y * _Complex_I;
            out_pixel_t temp_pixel = Mandle(temp, 0, 0);
            out_image[temp_pixel.x][temp_pixel.y][0] = temp_pixel.color[0];
            out_image[temp_pixel.x][temp_pixel.y][1] = temp_pixel.color[1];
            out_image[temp_pixel.x][temp_pixel.y][2] = temp_pixel.color[2];
            count++;
        }
    }
}
 
int main()
{
    int image[X][Y][3];
    MandleSet(image);
    return 0;
}