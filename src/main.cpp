#include <GL/freeglut.h>
#include <iostream>
#include <cmath>
#include "ObjLoader.h" 
#include "jogo.h"
#include "desenha.h"
#include "camera.h"

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Vaca");

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, 800.0/600.0, 0.1, 500.0);

    glMatrixMode(GL_MODELVIEW);


    glEnable(GL_DEPTH_TEST);
    
    Inicializa();
    inicializa();

    glutDisplayFunc(display);
    glutMouseFunc(mouseClick);
    glutMotionFunc(mouseMove);

    glutMainLoop();
    return 0;
}


