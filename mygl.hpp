#ifndef _MYGL_H_
#define _MYGL_H_

// #define GLM_FORCE_INLINE
#define GLM_SWIZZLE // ajudando muito
// Header file
#include <glm/fwd.hpp>
// Source file
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "definitions.hpp"

// *****************************************************************************
// Defina aqui as suas funções gráficas
// *****************************************************************************

template <typename T>
void Swap(T * a1, T * a2){
    T * temp = a1;

    a1 = a2;
    a2 = temp;
}

// Esse template gera as duas funcões abaixo

/*
 * void Swap(XY* a1, XY* a2){
 *  XY* temp = a1;
 *  a1 = a2;
 *  a2 = temp;
 * }
 * void Swap(RGBA* a1, RGBA* a2){
 *  RGBA* temp = a1;
 *  a1 = a2;
 *  a2 = temp;
 * }
 * //*/

// /////////////////////////////////////////////////////////////////////////////
// //////////////////// PutPixel //////////////////////////////////////////////
// ///////////////////////////////////////////////////////////////////////////

void PutPixel(XY ponto, RGBA cor){
    FBptr[4 * ponto[0] + 4 * ponto[1] * IMAGE_WIDTH + 0] = cor[0];
    FBptr[4 * ponto[0] + 4 * ponto[1] * IMAGE_WIDTH + 1] = cor[1];
    FBptr[4 * ponto[0] + 4 * ponto[1] * IMAGE_WIDTH + 2] = cor[2];
    FBptr[4 * ponto[0] + 4 * ponto[1] * IMAGE_WIDTH + 3] = cor[3];
}

void PutPixel(int x, int y, RGBA cor){
    FBptr[4 * x + 4 * y * IMAGE_WIDTH + 0] = cor[0];
    FBptr[4 * x + 4 * y * IMAGE_WIDTH + 1] = cor[1];
    FBptr[4 * x + 4 * y * IMAGE_WIDTH + 2] = cor[2];
    FBptr[4 * x + 4 * y * IMAGE_WIDTH + 3] = cor[3];
}

void PutDot(XY dot, RGBA cor, int size){
    int i, j;

    for (i = -size; i < size; i++)
        for (j = -size; j < size; j++)
            PutPixel(dot[0] + i, dot[1] + j, cor);
}

void SmoothDot(int x, int y, RGBA cor, int size){
    int i, j;
    RGBA tmpcor;

    for (i = -1; i <= 1; i++) {
        for (j = -1; j <= 1; j++) {
            if (i != 0 && j != 0) {
                tmpcor[0] = cor[0] / abs(size * fmax(i, j));
                tmpcor[1] = cor[1] / abs(size * fmax(i, j));
                tmpcor[2] = cor[2] / abs(size * fmax(i, j));
                tmpcor[3] = cor[3] / abs(size * fmax(i, j));
                PutPixel(x + i, y + j, tmpcor);
            }
        }
    }
    PutPixel(x, y, cor);
}

// /////////////////////////////////////////////////////////////////////////////
// /////////////////// DrawLine rasterizados //////////////////////////////////
// ///////////////////////////////////////////////////////////////////////////

void DrawLineBW(XY p0, XY p1){
    int addy, addx, dx, dy;

    dx = abs(p1[0] - p0[0]); // tamanho da reta
    dy = abs(p1[1] - p0[1]);

    if (dx > dy) {
        if (p0[0] > p1[0]) addx = -1;  // pseudo reflexao no eixo x
        else addx = 1;
        if (p0[1] > p1[1]) addy = -1;  // pseudo reflexao no eixo y
        else addy = 1;

        int d      = 2 * dy - dx; // variavel de decisao
        int incrE  = 2 * dy;
        int incrNE = 2 * (dy - dx);
        XY pi      = p0;

        PutPixel(pi, white);
        int loop = dx;

        while (loop) {
            // pi[0]!=p1[0] tem que cuidar dos dois casos
            if (d <= 0) {
                d     += incrE;
                pi[0] += addx;
            } else {
                d     += incrNE;
                pi[0] += addx; // aquele polimento
                pi[1] += addy;
            }
            PutPixel(pi, white);
            loop--;
        }
    } else {
        if (p0[0] > p1[0]) addx = -1;  // pseudo reflexao no eixo x
        else addx = 1;
        if (p0[1] > p1[1]) addy = -1;  // pseudo reflexao no eixo y
        else addy = 1;

        int d      = 2 * dx - dy; // variavel de decisao
        int incrE  = 2 * dx;
        int incrNE = 2 * (dx - dy);
        XY pi      = p0;

        PutPixel(pi, white);
        int loop = dy; // j'a tinha feito

        while (loop) {
            // pi[0]!=p1[0] tem que cuidar dos dois casos
            if (d <= 0) {
                d     += incrE;
                pi[1] += addy;
            } else {
                d     += incrNE;
                pi[0] += addx; // aquele polimento
                pi[1] += addy;
            }
            PutPixel(pi, white);
            loop--;
        }
    }
} // DrawLineBW

void DrawLine(XY p0, XY p1, RGBA cor0, RGBA cor1){
    int addy, addx, dx, dy;

    dx = abs(p1[0] - p0[0]); // tamanho da reta
    dy = abs(p1[1] - p0[1]);

    RGBA cor_inter = cor0;
    // Distância entre dois pontos
    int linear = sqrt(pow(p1[0] - p0[0], 2) + pow(p1[1] - p0[1], 2));

    if (dx > dy) {
        float dr = (cor1[0] - cor0[0]) / dx;
        float dg = (cor1[1] - cor0[1]) / dx;
        float db = (cor1[2] - cor0[2]) / dx;
        float da = (cor1[3] - cor0[3]) / dx;

        if (p0[0] > p1[0]) addx = -1;  // pseudo reflexao no eixo x
        else addx = 1;
        if (p0[1] > p1[1]) addy = -1;  // pseudo reflexao no eixo y
        else addy = 1;

        int d      = 2 * dy - dx; // variavel de decisao
        int incrE  = 2 * dy;
        int incrNE = 2 * (dy - dx);
        XY pi      = p0;

        PutPixel(pi, cor_inter);
        int loop = dx; // ja tinha feito

        while (loop) {
            // pi[0]!=p1[0] tem que cuidar dos dois casos
            if (d <= 0) {
                d     += incrE;
                pi[0] += addx;
            } else {
                d     += incrNE;
                pi[0] += addx; // aquele polimento
                pi[1] += addy;
            }
            cor_inter[0] += dr;
            cor_inter[1] += dg;
            cor_inter[2] += db;
            cor_inter[3] += da;
            PutPixel(pi, cor_inter);
            loop--;
        }
    } else {
        float dr = (cor1[0] - cor0[0]) / dy;
        float dg = (cor1[1] - cor0[1]) / dy;
        float db = (cor1[2] - cor0[2]) / dy;
        float da = (cor1[3] - cor0[3]) / dy;

        if (p0[0] > p1[0]) addx = -1;  // pseudo reflexao no eixo x
        else addx = 1;
        if (p0[1] > p1[1]) addy = -1;  // pseudo reflexao no eixo y
        else addy = 1;

        int d      = 2 * dx - dy; // variavel de decisao
        int incrE  = 2 * dx;
        int incrNE = 2 * (dx - dy);
        XY pi      = p0;

        PutPixel(pi, cor_inter);
        int loop = dy; // j'a tinha feito

        while (loop) {
            // pi[0]!=p1[0] tem que cuidar dos dois casos
            if (d <= 0) {
                d     += incrE;
                pi[1] += addy;
            } else {
                d     += incrNE;
                pi[0] += addx; // aquele polimento
                pi[1] += addy;
            }
            cor_inter[0] += dr;
            cor_inter[1] += dg;
            cor_inter[2] += db;
            cor_inter[3] += da;
            PutPixel(pi, cor_inter);
            loop--;
        }
    } // */
}     // DrawLine

void DrawLine(XY p0, XY p1, RGBA cor0, RGBA cor1, int espessura){
    int addy, addx, dx, dy;

    dx = abs(p1[0] - p0[0]); // tamanho da reta
    dy = abs(p1[1] - p0[1]);

    RGBA cor_inter = cor0;
    int linear     = sqrt(pow(p1[0] - p0[0], 2) + pow(p1[1] - p0[1], 2));

    if (dx > dy) {
        float dr = (cor1[0] - cor0[0]) / dx;
        float dg = (cor1[1] - cor0[1]) / dx;
        float db = (cor1[2] - cor0[2]) / dx;
        float da = (cor1[3] - cor0[3]) / dx;

        if (p0[0] > p1[0]) addx = -1;  // pseudo reflexao no eixo x
        else addx = 1;
        if (p0[1] > p1[1]) addy = -1;  // pseudo reflexao no eixo y
        else addy = 1;

        int d      = 2 * dy - dx; // variavel de decisao
        int incrE  = 2 * dy;
        int incrNE = 2 * (dy - dx);
        XY pi      = p0;

        // PutDot(pi, cor_inter, espessura);
        int loop = dx; // ja tinha feito

        while (loop) {
            // pi[0]!=p1[0] tem que cuidar dos dois casos
            if (d <= 0) {
                d     += incrE;
                pi[0] += addx;
            } else {
                d     += incrNE;
                pi[0] += addx; // aquele polimento
                pi[1] += addy;
            }
            cor_inter[0] += dr;
            cor_inter[1] += dg;
            cor_inter[2] += db;
            cor_inter[3] += da;
            PutPixel(pi, cor_inter);
            for (int k = 1; k <= espessura; k++) {
                PutPixel(pi[0], pi[1] + k, cor_inter);
                PutPixel(pi[0], pi[1] - k, cor_inter);
            }
            loop--;
        }
        // PutDot(pi, cor_inter, espessura);
    } else {
        float dr = (cor1[0] - cor0[0]) / dy;
        float dg = (cor1[1] - cor0[1]) / dy;
        float db = (cor1[2] - cor0[2]) / dy;
        float da = (cor1[3] - cor0[3]) / dy;

        if (p0[0] > p1[0]) addx = -1;  // pseudo reflexao no eixo x
        else addx = 1;
        if (p0[1] > p1[1]) addy = -1;  // pseudo reflexao no eixo y
        else addy = 1;

        int d      = 2 * dx - dy; // variavel de decisao
        int incrE  = 2 * dx;
        int incrNE = 2 * (dx - dy);
        XY pi      = p0;

        // PutDot(pi, cor_inter, espessura);
        int loop = dy; // j'a tinha feito

        while (loop) {
            // pi[0]!=p1[0] tem que cuidar dos dois casos
            if (d <= 0) {
                d     += incrE;
                pi[1] += addy;
            } else {
                d     += incrNE;
                pi[0] += addx; // aquele polimento
                pi[1] += addy;
            }
            cor_inter[0] += dr;
            cor_inter[1] += dg;
            cor_inter[2] += db;
            cor_inter[3] += da;
            PutPixel(pi, cor_inter);
            for (int k = 1; k <= espessura; k++) {
                PutPixel(pi[0] + k, pi[1], cor_inter);
                PutPixel(pi[0] - k, pi[1], cor_inter);
            }
            loop--;
        }
        // PutDot(pi, cor_inter, espessura);
    } // */
}     // DrawLine

// /////////////////////////////////////////////////////////////////////////////
// ///////////////////Os DrawTriangle rasterizados ////////////////////////////
// ///////////////////////////////////////////////////////////////////////////
void DrawTriangle(XY p0, XY p1, XY p2, RGBA cor0, RGBA cor1, RGBA cor2){
    DrawLine(p0, p1, cor0, cor1);
    DrawLine(p0, p2, cor0, cor2);
    DrawLine(p1, p2, cor1, cor2);
}

void DrawTriangle(XY p0, XY p1, XY p2, RGBA cor0, RGBA cor1, RGBA cor2, int e1, int e2, int e3){
    DrawLine(p0, p1, cor0, cor1, e1);
    DrawLine(p0, p2, cor0, cor2, e2);
    DrawLine(p1, p2, cor1, cor2, e3);
}

// */

// /////////////////////////////////////////////////////////////////////////////
// /////////////////// Compatibilidade com GLM ////////////////////////////////
// ///////////////////////////////////////////////////////////////////////////
void DrawTriangle(glm::vec2 const & p0i, glm::vec2 const & p1i, glm::vec2 const & p2i, glm::vec4 const & cor0i,
  glm::vec4 const & cor1i,
  glm::vec4 const & cor2i){
    XY p0     = { p0i.x, p0i.y };
    XY p1     = { p1i.x, p1i.y };
    XY p2     = { p2i.x, p2i.y };
    RGBA cor0 = { cor0i.x, cor0i.y, cor0i.z };
    RGBA cor1 = { cor1i.x, cor1i.y, cor1i.z };
    RGBA cor2 = { cor2i.x, cor2i.y, cor2i.z };

    DrawTriangle(p0, p1, p2, cor0, cor1, cor2);
}

void DrawTriangle(glm::vec2 const & p0i, glm::vec2 const & p1i, glm::vec2 const & p2i, RGBA cor0, RGBA cor1,
  RGBA cor2){
    XY p0 = { p0i.x, p0i.y };
    XY p1 = { p1i.x, p1i.y };
    XY p2 = { p2i.x, p2i.y };

    DrawTriangle(p0, p1, p2, cor0, cor1, cor2);
}

void DrawTriangle(glm::vec2 const & p0i, glm::vec2 const & p1i, glm::vec2 const & p2i, glm::vec4 const & cor0i,
  glm::vec4 const & cor1i, glm::vec4 const & cor2i, int e1, int e2,
  int e3){
    XY p0     = { p0i.x, p0i.y };
    XY p1     = { p1i.x, p1i.y };
    XY p2     = { p2i.x, p2i.y };
    RGBA cor0 = { cor0i.x, cor0i.y, cor0i.z };
    RGBA cor1 = { cor1i.x, cor1i.y, cor1i.z };
    RGBA cor2 = { cor2i.x, cor2i.y, cor2i.z };

    DrawTriangle(p0, p1, p2, cor0, cor1, cor2, e1, e2, e3);
}

// /////////////////////testes

glm::mat4 setMVP(glm::vec3 const& Translate,
  glm::vec3 const               & Rotate){
    glm::mat4 Projection    = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.f);
    glm::mat4 ViewTranslate = glm::translate(glm::mat4(1.0f), Translate);
    glm::mat4 ViewRotateX   = glm::rotate(ViewTranslate, Rotate.y, glm::vec3(-1.0f, 0.0f, 0.0f));
    glm::mat4 View  = glm::rotate(ViewRotateX, Rotate.x, glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 Model = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));
    glm::mat4 MVP   = Projection * View * Model;

    return MVP;
}

#endif // _MYGL_H_
