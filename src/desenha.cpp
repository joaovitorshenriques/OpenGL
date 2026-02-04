#include "ObjLoader.h"
#include "Entidade.h"
#include <GL/freeglut.h>

extern Entidade vaca;
extern Entidade ufo;


bool cameraSendoSeguida = false;
float angulo = 0.0f;          


void desenhaEntidade(const Entidade& e) {
    if(e.modelo == nullptr) return;

    glPushMatrix();

    glTranslatef(e.x, e.y, e.z);
    glRotatef();
    glScalef(e.scale, e.scale, e.scale)

    e.modelo -> draw();

    glPopMatrix();
}

void desenhaVaca(){
    desenhaEntidade(vaca);
}

void desenhaUFO(){
    desenhaEntidade(ufo);
}



void desenhaTerreno() {
    glBegin(GL_QUADS);
    glColor3f(0.2f, 0.5f, 0.2f); 
    glVertex3f(-50.0f, 0.0f, -50.0f);
    glVertex3f(-50.0f, 0.0f,  50.0f);
    glVertex3f( 50.0f, 0.0f,  50.0f);
    glVertex3f( 50.0f, 0.0f, -50.0f);
    glEnd();
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    if (cameraSendoSeguida) {
       
        float camX = posX - sin(angulo * M_PI / 180.0) * 10.0f;
        float camZ = posZ - cos(angulo * M_PI / 180.0) * 10.0f;
        gluLookAt(camX, 5.0f, camZ, posX, 1.0f, posZ, 0, 1, 0);
    } else {
        
        gluLookAt(0, 40, 50, 0, 0, 0, 0, 1, 0);
    }

    desenhaTerreno();
    desenhaVaca();
    desenhaUFO();
    glutSwapBuffers();
}