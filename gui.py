from ctypes import *
from PIL import Image, ImageTk
import tkinter as tk

# Caminho para a biblioteca compartilhada que contém o código C
shared_library_path = "./mandelbrot.so"

print("Carregando...")

# Carrega a biblioteca compartilhada usando ctypes
my_funcs = CDLL(shared_library_path)

# Chama a função build_image() da biblioteca C, que gera a imagem do Conjunto de Mandelbrot
my_funcs.build_image()

# Cria uma nova imagem RGB com tamanho 1920x1080, inicializada como uma imagem preta
im = Image.new('RGB', (1920, 1080), "black")
pixels = im.load()  # Cria um mapa de pixels para a manipulação direta da imagem

# Itera sobre cada pixel na imagem para atribuir as cores calculadas pelo código C
for i in range(im.size[0]):  # Para cada coluna
   for j in range(im.size[1]):  # Para cada linha
        # Obtém as componentes de cor (R, G, B) para o pixel (i, j) através da função get_pixel() em C
        r = my_funcs.get_pixel(i, j, 0)
        g = my_funcs.get_pixel(i, j, 1)
        b = my_funcs.get_pixel(i, j, 2)
        # Atribui as cores ao pixel correspondente na imagem
        pixels[i, j] = (r, g, b)

# Salva a imagem gerada como um arquivo PNG
im.save('mandelbrot.png')

# Libera a memória alocada pelo código C para a imagem
my_funcs.free_image()

# Cria uma janela principal para a GUI usando Tkinter
root = tk.Tk()
root.title("Mandelbrot")

# Converte a imagem gerada para um formato compatível com Tkinter
image = ImageTk.PhotoImage(im)
image_label = tk.Label(root, image=image)

# Define a função a ser chamada quando o botão "Gerar Imagem" for clicado
def on_button_click():
        # Exibe a imagem na interface gráfica
        image_label.pack()

# Cria um botão na interface gráfica para gerar a imagem
button = tk.Button(root, text="Gerar Imagem", command=on_button_click)
button.pack()

# Inicia o loop principal da GUI do Tkinter
root.mainloop()
