#ifndef ENTIDADE_H
#define ENTIDADE_H

#include "ObjLoader.h"

struct Entidade {
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;

    float scale = 1.0f;

    ObjLoader* modelo = nullptr;
};

#endif