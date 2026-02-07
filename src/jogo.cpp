#include <GL/freeglut.h>
#include "jogo.h"


ObjLoader vacaModel;
ObjLoader ufoModel;

Entidade vaca;
Entidade ufo;

bool cameraSendoSeguida = false;
float posX = 0.0f;
float posZ = 0.0f;
float angulo = 0.0f;


void Inicializa(){
    vacaModel.load("models/LP_cow.obj");
    ufoModel.load("models/UFO.obj");


    vaca.modelo = &vacaModel;
    vaca.x = 0.0f;
    vaca.y = 0.0f;
    vaca.z = 0.0f;
    vaca.scale = 2.0f; 

    ufo.modelo = &ufoModel;
    ufo.x = 0.0f;
    ufo.y = 15.0f;
    ufo.z = 0.0f;
    ufo.scale = 0.5f; 
}