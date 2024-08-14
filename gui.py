from ctypes import *
from PIL import Image, ImageColor
# requires pip install pillow
shared_library_path = "./mandelbrot.so"

my_funcs = CDLL(shared_library_path)

my_funcs.build_image()

im = Image.new('RGB', (1920, 1080), "black") # starts as a black image
pixels = im.load() #creates pixel map, whatever that is

for i in range(im.size[0]): #for every col
   for j in range(im.size[1]): #for every row
        r = my_funcs.get_pixel(i, j, 0)
        g = my_funcs.get_pixel(i, j, 1)
        b = my_funcs.get_pixel(i, j, 2)
        pixels[i, j] = (r, g, b)

im.save('mandelbrot2.png')
my_funcs.free_image()