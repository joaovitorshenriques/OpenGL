#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "ObjLoader.h"
#include "Entidade.h"
#include "jogo.h"
#include <GL/freeglut.h>
#include <iostream>
#include <cmath>
#include "camera.h"


extern Entidade vaca;
extern Entidade ufo;

extern bool cameraSendoSeguida;
extern float posX;
extern float posZ;
extern float angulo;

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

/*void desenhaTerreno(float size, GLuint texturaID) {
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
}*/

void desenhaEntidade(const Entidade& e) {
    if(e.modelo == nullptr) return;

    glPushMatrix();

    glTranslatef(e.x, e.y, e.z);
    glScalef(e.scale, e.scale, e.scale);

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

void desenhaGrama(float x, float z) {
    float h = 0.5f;
    float w = 0.1f;

    glColor3f(0.1f, 0.7f, 0.1f);

    glBegin(GL_QUADS);
        glVertex3f(x - w, 0.0f, z);
        glVertex3f(x + w, 0.0f, z);
        glVertex3f(x + w, h, z);
        glVertex3f(x - w, h, z);
    glEnd();

    glBegin(GL_QUADS);
        glVertex3f(x, 0.0f, z - w);
        glVertex3f(x, 0.0f, z + w);
        glVertex3f(x, h, z + w);
        glVertex3f(x, h, z - w);
    glEnd();
}

void quantGrama(int colunas, int linhas) {
    float tamanho = 50.0f; 
    float margem = 0.1f;   
    
    float stepX = (tamanho * 2 - (margem * 2)) / (colunas - 1);
    float stepZ = (tamanho * 2 - (margem * 2)) / (linhas - 1);

    for (int i = 0; i < colunas; i++) {
        for (int j = 0; j < linhas; j++) {

            float posX = (-tamanho + margem) + (i * stepX);
            float posZ = (-tamanho + margem) + (j * stepZ);
            
            desenhaGrama(posX, posZ);
        }
    }
}

void inicializa(){

    /*texGrama = carregarTextura("textures/grama.jpg");
    if (texGrama == 0) {
        std::cout << "Aviso: Textura do gramado não encontrada!" << std::endl;
    }*/
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


}

constexpr float PI = 3.14159265359f;


void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(
        60.0,        
        800.0 / 600.0, 
        0.1,         
        1000.0       
    );

    float radRot = camRot * PI / 180.0f;
    float radInc = camInc * PI / 180.0f;

    float targetX = vaca.x;
    float targetY = vaca.y + 2.0f;
    float targetZ = vaca.z;

    float camX = targetX + camDist * cos(radInc) * sin(radRot);
    float camY = targetY + camDist * sin(radInc);
    float camZ = targetZ + camDist * cos(radInc) * cos(radRot);

    gluLookAt(
        camX, camY, camZ,
        targetX, targetY, targetZ,
        0.0f, 1.0f, 0.0f
    );


    desenhaTerreno();
    quantGrama(100, 100);
    desenhaVaca();
    desenhaUFO();

    glutSwapBuffers();
}
