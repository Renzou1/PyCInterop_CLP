from ctypes import *

shared_library_path = "./mandelbrot.so"

my_funcs = CDLL(shared_library_path)
# my_funcs.e.restype = POINTER(c_int)

my_funcs.build_image()



# pointer = my_funcs.e()
# print(pointer)

# #res = [[[pointer[i * 1080 * 3 + j * 3 + k] for k in range(3)] for j in range(1080)] for i in range(1920)]

# res = [pointer[i] for i in range(1920 * 1080 * 3)]
# a = []
for i in range(1920):
   for j in range(1080):
       for channel in range(3):
           print(my_funcs.r(i, j, channel))
        #    a.append()


# print(res[0:50])