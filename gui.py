from ctypes import *
from PIL import Image, ImageTk
import tkinter as tk

# requires pip install pillow
shared_library_path = "./mandelbrot.so"

print("Carregando...")

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

im.save('mandelbrot.png')
my_funcs.free_image()

root = tk.Tk()
root.title("Mandelbrot")

image = ImageTk.PhotoImage(im)
image_label = tk.Label(root, image=image)

def on_button_click():
        image_label.pack()

button = tk.Button(root, text="Gerar Imagem", command=on_button_click)
button.pack()

root.mainloop()