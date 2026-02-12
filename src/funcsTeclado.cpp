#include <GL/freeglut.h>
#include <cmath>
extern float vacaX;
extern float vacaZ;
extern float camRot;
const float PI = 3.14159265359f;
float vacaRot = 0.0f;





void teclado(unsigned char tecla, int x, int y) {
    float velocidade = 0.5f;
    float limite = 49.5f;

    // Converte o ângulo da câmera para Radianos
    float anguloRad = camRot * PI / 180.0f;

    // Calcula as direções baseadas no ângulo da câmera
    // Seno e Cosseno nos dão a direção "para frente" da câmera
    float dx = sin(anguloRad);
    float dz = cos(anguloRad);

        switch (tecla) {

        case 'w': case 'W':
            vacaRot = camRot;
            vacaX -= dx * velocidade;
            vacaZ -= dz * velocidade;
            break;

        case 's': case 'S':
            vacaRot = camRot + 180;
            vacaX += dx * velocidade;
            vacaZ += dz * velocidade;
            break;

        case 'a': case 'A':
            vacaRot = camRot + 90;
            vacaX -= dz * velocidade;
            vacaZ += dx * velocidade;
            break;

        case 'd': case 'D':
            vacaRot = camRot - 90;
            vacaX += dz * velocidade;
            vacaZ -= dx * velocidade;
            break;
        }

    // Mantém a vaca no terreno
    if (vacaX > limite)  vacaX = limite;
    if (vacaX < -limite) vacaX = -limite;
    if (vacaZ > limite)  vacaZ = limite;
    if (vacaZ < -limite) vacaZ = -limite;
}