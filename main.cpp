#include "main.hpp"

// -----------------------------------------------------------------------------
void MyGlDraw(void){
    // *************************************************************************
    // Chame aqui as funções do mygl.h
    // *************************************************************************
    XY ponto, ponto2, ponto3;
    glm::vec2 vonto, vonto2, vonto3;
    RGBA cor, cor2;

    ponto  = { 50, 50 };
    ponto2 = { 450, 50 };
    ponto3 = { 250, 500 };
    DrawTriangle(ponto, ponto2, ponto3, red, green, blue, 5, 5, 5);
    ponto  = { 50, 450 };
    ponto2 = { 450, 450 };
    ponto3 = { 250, 50 };
    vonto  = glm::vec2(40, 450);
    vonto2 = glm::vec2(450, 450);
    vonto3 = glm::vec2(
      250,
      50);

    // cout << glm::to_string(vonto) << endl; //nice
    DrawTriangle(vonto, vonto2, vonto3, magenta, cyan, yellow);

    // funcionando sem mais problemas


    ponto  = { 250, 250 };
    ponto2 = { 350, 250 };
    ponto3 = { 120, 140 };

    // DrawLineBW(ponto, ponto3);
    int addx = 50, addy = 50;

    for (int k = 0; k < 80; k++) {
        // nao consegui fazer um for legal
        // DrawLine(ponto, ponto2, cyan, magenta,5);
        // DrawLineBW(ponto, ponto2);
        ponto2[0] += addx;
        DrawLine(ponto, ponto2, yellow, red, 5);

        // DrawLineBW(ponto, ponto2);
        ponto2[1] += addy;

        if ((ponto2[0] >= 400) || (ponto2[0] <= 100)) addx = -addx;

        if ((ponto2[1] >= 400) || (ponto2[1] <= 100)) addy = -addy;
    }

    // */
} // MyGlDraw

// -----------------------------------------------------------------------------
int main(int argc, char ** argv){
    // Inicializações.
    InitOpenGL(&argc, argv);
    InitCallBacks();
    InitDataStructures();

    // Ajusta a função que chama as funções do mygl.h
    DrawFunc = MyGlDraw;

    // Framebuffer scan loop.
    glutMainLoop();

    return 0;
}
