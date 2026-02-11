#include <GL/freeglut.h>

extern float vacaX;
extern float vacaZ;

void teclado(unsigned char tecla, int x, int y) {
    float velocidade = 0.5f;
    float limite = 49.5f; // Para não sair do terreno de 50.0

    switch (tecla) {
        case 'w': case 'W':
            vacaZ -= velocidade;
            break;
        case 's': case 'S':
            vacaZ += velocidade;
            break;
        case 'a': case 'A':
            vacaX -= velocidade;
            break;
        case 'd': case 'D':
            vacaX += velocidade;
            break;
    }

    // Impede a vaca de sair do terreno
    if (vacaX > limite)  vacaX = limite;
    if (vacaX < -limite) vacaX = -limite;
    if (vacaZ > limite)  vacaZ = limite;
    if (vacaZ < -limite) vacaZ = -limite;

    glutPostRedisplay();
}