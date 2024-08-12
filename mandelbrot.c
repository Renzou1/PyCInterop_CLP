#include <complex.h>
#include <tgmath.h>
#include <stdio.h>
 
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
        int c = 128 - 128 * cabs(t) / cabs(c);
        out_pixel_t pixel = {creal(c) * Y / 2 + X / 2, cimag(c) * Y / 2 + Y / 2, {c, c, c}};
        return pixel;
    }
 
    // To put about the end of the fractal,
    // the higher the value of the counter,
    // The more accurate the fractal is generated,
    // however, higher values cause
    // more processing time.
    if (counter == 100) {
        int c = 255 * (cabs((t * t)) / cabs((t - c) * c));
        out_pixel_t pixel = {creal(c) * Y / 2 + X / 2, cimag(c) * Y / 2 + Y / 2, {c, 0, 0}};
        return pixel;
    }
 
    // recursively calling Mandle with increased counter
    // and passing the value of the squares of t into it.
    return Mandle(c, cpow(t, 2) + c, counter + 1);
}
 
int MandleSet(out_pixel_t* image)
{
    int count = 0;
    // Calling Mandle function for every
    // point on the screen.
    for (double x = -2; x < 2; x += 0.0015) {
        for (double y = -1; y < 1; y += 0.0015) {
            double _Complex temp = x + y * _Complex_I;
            image[count] = Mandle(temp, 0, 0);
            count++;
        }
    }
    return 0;
}
 
int main()
{
    int n_generated_pixels = 3557778;
    out_pixel_t out_image[n_generated_pixels];
    out_pixel_t* ptr = &out_image[0];
    MandleSet(ptr);
    return 0;
}