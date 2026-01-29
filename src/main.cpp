#include <GL/freeglut.h>
#include <iostream>
#include <cmath>
#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif
// Configurações de Estado
bool cameraSendoSeguida = false;
float posX = 0.0f, posZ = 0.0f; // Posição do personagem
float angulo = 0.0f;           // Rotação do personagem
float vel = 0.5f;              // Velocidade de translação

// Protótipos (Você deve implementar o carregador OBJ aqui depois)
void desenhaTerreno() {
    glBegin(GL_QUADS);
    glColor3f(0.2f, 0.5f, 0.2f); // Verde (pode usar textura aqui)
    glVertex3f(-50.0f, 0.0f, -50.0f);
    glVertex3f(-50.0f, 0.0f,  50.0f);
    glVertex3f( 50.0f, 0.0f,  50.0f);
    glVertex3f( 50.0f, 0.0f, -50.0f);
    glEnd();
}

void desenhaPersonagem() {
    glPushMatrix();
        glTranslatef(posX, 0.5f, posZ);
        glRotatef(angulo, 0.0f, 1.0f, 0.0f);
        
        // Substitua este cubo pelo seu modelo OBJ usando carregarArquivo2.cpp
        glColor3f(0.0f, 0.0f, 1.0f);
        glutSolidCube(1.0f); 
        
        // Pequeno "nariz" para saber para onde ele está olhando
        glTranslatef(0, 0, 0.6f);
        glColor3f(1.0f, 0.0f, 0.0f);
        glutSolidCube(0.2f);
    glPopMatrix();
}

void configurarIluminacao() {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    GLfloat lightPos[] = { 0.0f, 10.0f, 0.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glEnable(GL_COLOR_MATERIAL); // Facilita usar glColor com iluminação
}

void mudaTamanho(int w, int h) {
    // Previne divisão por zero
    if (h == 0) h = 1;
    float aspecto = (float)w / (float)h;

    // Define a projeção (a lente da câmera)
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    // Configura o volume de visão: ângulo, aspecto, perto, longe
    gluPerspective(45.0, aspecto, 0.1, 500.0);

    // Volta para o modo de desenho de objetos
    glMatrixMode(GL_MODELVIEW);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    if (cameraSendoSeguida) {
        // Câmera atrás e acima: calcula posição baseada na rotação do personagem
        float camX = posX - sin(angulo * M_PI / 180.0) * 10.0f;
        float camZ = posZ - cos(angulo * M_PI / 180.0) * 10.0f;
        gluLookAt(camX, 5.0f, camZ, posX, 1.0f, posZ, 0, 1, 0);
    } else {
        // Câmera fixa (visão geral)
        gluLookAt(0, 40, 50, 0, 0, 0, 0, 1, 0);
    }

    desenhaTerreno();
    desenhaPersonagem();

    glutSwapBuffers();
}

void teclado(unsigned char key, int x, int y) {
    switch (key) {
        case 'w': case 'W': // Anda para frente na direção da rotação
            posX += sin(angulo * M_PI / 180.0) * vel;
            posZ += cos(angulo * M_PI / 180.0) * vel;
            break;
        case 'a': case 'A': angulo += 5.0f; break; // Gira
        case 'd': case 'D': angulo -= 5.0f; break; // Gira
        case 'c': case 'C': cameraSendoSeguida = !cameraSendoSeguida; break;
        case 27: exit(0); break; // ESC
    }
    glutPostRedisplay();
}

void inicializar() {
    glClearColor(0.5f, 0.8f, 1.0f, 1.0f); // Céu azul
    glEnable(GL_DEPTH_TEST);
    configurarIluminacao();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1024, 768);
    glutCreateWindow("Trabalho Final CG - UFOP");

    inicializar();

    glutDisplayFunc(display);
    glutKeyboardFunc(teclado);
    glutReshapeFunc(mudaTamanho);
    
    glutMainLoop();
    return 0;
}