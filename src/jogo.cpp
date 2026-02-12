#include <GL/freeglut.h>
#include "jogo.h"


ObjLoader vacaModel;
ObjLoader ufoModel;
ObjLoader alienModel;
Entidade vaca;
Entidade ufo;
const int MAX_ALIENS = 20;
Entidade aliens[MAX_ALIENS];
GLuint alienList;
bool cameraSendoSeguida = false;
float posX = 0.0f;
float posZ = 0.0f;
float angulo = 0.0f;


void Inicializa(){
    vacaModel.load("models/cow.obj");
    ufoModel.load("models/UFO.obj");
    alienModel.load("models/alien_11.obj");

    alienList = glGenLists(1);
    glNewList(alienList, GL_COMPILE);
        alienModel.draw();
    glEndList();

    vaca.modelo = &vacaModel;
    vaca.x = 0.0f;
    vaca.y = 0.0f;
    vaca.z = 0.0f;
    vaca.scale = 0.002f; 

    ufo.modelo = &ufoModel;
    ufo.x = 0.0f;
    ufo.y = 15.0f;
    ufo.z = 0.0f;
    ufo.scale = 0.5f; 

    for(int i = 0; i < MAX_ALIENS; i++) {
        aliens[i].modelo = &alienModel;
        aliens[i].y = -10.0f;
        aliens[i].scale = 0.3f;
    }

}