from ctypes import *
from PIL import Image, ImageColor
# requires pip install pillow
shared_library_path = "./mandelbrot.so"

my_funcs = CDLL(shared_library_path)
# my_funcs.e.restype = POINTER(c_int)

my_funcs.build_image()



# pointer = my_funcs.e()
# print(pointer)

# #res = [[[pointer[i * 1080 * 3 + j * 3 + k] for k in range(3)] for j in range(1080)] for i in range(1920)]

# res = [pointer[i] for i in range(1920 * 1080 * 3)]
# a = []
im = Image.new('RGB', (1920, 1080), "black") # starts as a black image
pixels = im.load() #creates pixel map, whatever that is

for i in range(im.size[0]): #for every col
   for j in range(im.size[1]): #for every row
        r = my_funcs.r(i, j, 0)
        g = my_funcs.r(i, j, 1)
        b = my_funcs.r(i, j, 2)
        pixels[i, j] = (r, g, b)
        #    a.append()

im.show()

# print(res[0:50])