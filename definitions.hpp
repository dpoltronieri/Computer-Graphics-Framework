#ifndef _DEFINITIONS_H_
#define _DEFINITIONS_H_

#include <cstdio>
#include <iostream>
#include <array>
#include <cmath>
using namespace std;

#define IMAGE_WIDTH  512 // número de colunas da imagem.
#define IMAGE_HEIGHT 512 // número de linhas da imagem.

unsigned char * FBptr;

typedef struct XY {
    int&operator [] (int i){
        return ponto[i];
    }

    std::array<int, 2> ponto;
} XY;

typedef struct RGBA {
    float&operator [] (int i){
        return cor[i];
    }

    std::array<float, 4> cor;
} RGBA;

RGBA red = { 255, 0, 0, 255 };
RGBA green = { 0, 255, 0, 255 };
RGBA blue = { 0, 0, 255, 255 };
RGBA yellow = { 255, 255, 0, 255 };
RGBA magenta = { 255, 0, 255, 255 };
RGBA cyan = { 0, 255, 255, 255 };
RGBA white = { 255, 255, 255, 255 };
RGBA black = { 0, 0, 0, 255 };

/* tive que mudar a estrutura interna do armazenamento do RGBA para float para a
 * interpolaćão funcionar
 * quando armazenava internamente como char, ele tinha alguns
 * problemas de conversão de tipo, rusultando em dar pau
 * fodamente
 */


#endif // _DEFINITIONS_H_
