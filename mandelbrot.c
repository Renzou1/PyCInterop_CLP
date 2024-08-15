#include <complex.h>
#include <tgmath.h>
#include <stdio.h>
#include <stdlib.h>

// Definindo o tamanho da tela.
#define Y 1080  // Altura da imagem
#define X 1920  // Largura da imagem

// Estrutura que representa um pixel na imagem.
typedef struct pixel
{
    int x;          // Coordenada x do pixel
    int y;          // Coordenada y do pixel
    int color[3];   // Array que armazena as componentes de cor RGB do pixel
} pixel_t;

// Função recursiva que calcula o Conjunto de Mandelbrot para cada pixel na tela.
// Argumentos:
//   c: Número complexo que representa a coordenada atual na tela
//   t: Valor de iteração atual (inicialmente 0)
//   counter: Contador de iterações (inicialmente 0)
// Retorna:
//   Um pixel_t contendo as coordenadas e a cor do pixel correspondente
pixel_t Mandel(double _Complex c,
               double _Complex t,
               int counter)
{

    // Verifica se o valor absoluto de t excede 4, indicando que o ponto está fora do conjunto.
    if (cabs(t) > 4)
    {
        // Calcula a cor com base no valor absoluto de t
        int color = -(int)(128 - 128 * cabs(t) / cabs(c)) % 255;
        pixel_t pixel = {creal(c) * X / 4 + X / 2,
                         cimag(c) * Y / 2 + Y / 2,
                         {color, color, color}};
        return pixel;
    }

    // Verifica se o contador atingiu 100, limitando o número de iterações.
    // Quanto maior o contador, mais preciso será o fractal gerado, mas com maior custo de processamento.
    if (counter == 100)
    {
        // Calcula a cor com base no valor atual de t
        int color = 255 * (int)(cabs((t * t)) / cabs((t - c) * c)) % 255;
        pixel_t pixel = {creal(c) * X / 4 + X / 2,
                         cimag(c) * Y / 2 + Y / 2,
                         {color, 0, 0}};
        return pixel;
    }

    // Chama recursivamente a função Mandel, incrementando o contador
    // e passando o valor do quadrado de t mais c.
    return Mandel(c, cpow(t, 2) + c, counter + 1);
}

// Função que gera o Conjunto de Mandelbrot para cada ponto da tela.
// Argumentos:
//   image: Matriz 3D que armazena as cores dos pixels da imagem
void MandelSet(int ***image)
{
    // Itera sobre cada ponto na tela, chamando a função Mandel para calcular a cor do pixel.
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

// Função para alocar dinamicamente a memória para a imagem.
// Retorna:
//   Um ponteiro para a matriz 3D que representa a imagem.
int ***malloc_image()
{
    // Aloca memória para as linhas da imagem.
    int ***image = (int ***)malloc(sizeof(int **) * X);

    for (int i = 0; i < X; i++)
    {
        image[i] = (int **)malloc(sizeof(int *) * Y);
    }

    // Aloca memória para as colunas da imagem.
    for (int i = 0; i < X; i++)
    {
        for (int j = 0; j < Y; j++)
        {
            image[i][j] = (int *)malloc(sizeof(int) * 3);
        }
    }

    return image;
}

// Ponteiro global para a imagem.
int ***img;

// Função para liberar a memória alocada para a imagem.
void free_image()
{
    // Libera a memória alocada para cada pixel.
    for (int i = 0; i < X; i++)
    {
        for (int j = 0; j < Y; j++)
        {
            free(img[i][j]);
        }
    }

    // Libera a memória alocada para as linhas.
    for (int i = 0; i < X; i++)
    {
        free(img[i]);
    }

    // Libera a memória alocada para a imagem.
    free(img);
}

// Função para obter o valor de uma componente de cor (R, G, B) de um pixel.
// Argumentos:
//   x: Coordenada x do pixel
//   y: Coordenada y do pixel
//   z: Índice da componente de cor (0 para R, 1 para G, 2 para B)
// Retorna:
//   O valor da componente de cor especificada
int get_pixel(int x, int y, int z)
{
    return img[x][y][z];
}

// Função principal para gerar a imagem do Conjunto de Mandelbrot.
void build_image()
{
    // Aloca memória para a imagem.
    int ***image = malloc_image();
    
    // Gera o Conjunto de Mandelbrot.
    MandelSet(image);
    
    // Atribui o ponteiro global para a imagem gerada.
    img = image;
}

// Função principal do programa.
int main(int argc, char const *argv[])
{
    // Gera a imagem do Conjunto de Mandelbrot.
    build_image();
    
    // Retorna 0 para indicar que o programa terminou com sucesso.
    return 0;
}
