<<<<<<< HEAD
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <iostream>
#include <GL/gl.h>
#include <GL/freeglut.h>


GLuint texGrama;

GLuint carregarTextura(const char* filename) {
    int width, height, channels;
    // Carrega os pixels do arquivo usando a stb_image
    unsigned char* data = stbi_load(filename, &width, &height, &channels, 0);

    if (!data) {
        std::cerr << "Erro ao carregar a textura: " << filename << " | Razao: " << stbi_failure_reason() << std::endl;
        return 0;
    }

    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Converte para formato RGBA se a imagem for apenas RGB (3 canais)
    if (channels == 3) {
        unsigned char* rgbaData = new unsigned char[width * height * 4];
        for (int i = 0; i < width * height; ++i) {
            rgbaData[i * 4 + 0] = data[i * 3 + 0]; // R
            rgbaData[i * 4 + 1] = data[i * 3 + 1]; // G
            rgbaData[i * 4 + 2] = data[i * 3 + 2]; // B
            rgbaData[i * 4 + 3] = 255;             // Alpha (opacidade total)
        }
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, rgbaData);
        delete[] rgbaData; 
    } 
    else if (channels == 4) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    }

    // Configura os parâmetros básicos de filtragem e repetição
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    stbi_image_free(data); // Libera a memória da CPU
    return textureID;
}


void desenhaTerreno(float size, GLuint texturaID) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texturaID);
    
    // Cor branca para não interferir na cor da textura
    glColor3f(1.0f, 1.0f, 1.0f); 

    glBegin(GL_QUADS);
        // Mapeamento: (0,0) até (1,1) faz a imagem cobrir o chão todo uma vez
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-size, 0.0f, -size);
        glTexCoord2f(1.0f, 0.0f); glVertex3f( size, 0.0f, -size);
        glTexCoord2f(1.0f, 1.0f); glVertex3f( size, 0.0f,  size);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-size, 0.0f,  size);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

void desenhaPersonagem() {
    glPushMatrix();
        glTranslatef(posX, 0.5f, posZ);
        glRotatef(angulo, 0.0f, 1.0f, 0.0f);
        
      
        glColor3f(0.0f, 0.0f, 1.0f);
        glutSolidCube(1.0f); 
        
      
        glTranslatef(0, 0, 0.6f);
        glColor3f(1.0f, 0.0f, 0.0f);
        glutSolidCube(0.2f);
    glPopMatrix();
}

void inicializa(){

    texGrama = carregarTextura("external/textures/grama.jpg");
    if (texGrama == 0) {
        std::cout << "Aviso: Textura do gramado não encontrada!" << std::endl;
    }

}

void display() {


    desenhaTerreno();
    desenhaPersonagem();

    glutSwapBuffers();
}