# PyCInterop_CLP

Este projeto usa código em C para gerar um array com as informações dos pixels de uma imagem de um fractal de mandelbrot, e Python para pegar essas informações e gerar a imagem.

## Arquivos do Projeto

- **mandelbrot.c**: Contém as funções que geram o fractal.
- **gui.py**: Script Python que carrega a biblioteca C, cria a interface gráfica e mostra a imagem.
- **Makefile**: Compila o código em C para uma biblioteca compartilhada e executa o arquivo gui.py.

## Compilação e Execução

Para compilar a biblioteca C e executar o script Python, siga os passos abaixo:

1. **Compilar a biblioteca**:
   ```bash
   make
2. **Executar script python**:
   ```bash
   make run
### Ou, Execução manual:

1. **Compilar a biblioteca**:
   ```bash
   gcc -fPIC -shared -o mandelbrot.so mandelbrot.c
2. **Executar script python**:
   ```bash
   python3 gui.py
## Requisitos:
- GCC: Para compilar o código C e gerar a biblioteca compartilhada.
- Python 3: Para executar o script Python. Com as bibliotecas que serão listadas.
- Make: Para executar o makefile.

## Bibliotecas necessárias e instalação:
1. **pillow**:
   ```bash
   pip install pillow
