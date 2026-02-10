#include "camera.h"
#include <GL/freeglut.h>

float camRot = 0.0f;
float camInc = 20.0f;

float camDist = 30.0f;

int mouseX = 0;
int mouseY = 0;
bool pressed = false;


void mouseMove(int x, int y) {
    if (!pressed) return;

    float sensi = 0.3f;

    camRot += (x - mouseX) * sensi;
    camInc += (y - mouseY) * sensi;

    if(camInc > 85.0f) camInc = 85.0f;
    if(camInc < -10.0f) camInc = -10.0f;

    mouseX = x;
    mouseY = y;

    glutPostRedisplay();
}

void mouseClick(int button, int state, int x, int y) {

    if (state == GLUT_DOWN) {
        if (button == 3) camDist -= 2.0f;
        if (button == 4) camDist += 2.0f;

        if (camDist < 5.0f) camDist = 5.0f;
        if (camDist > 55.0f) camDist = 55.0f;
    }

    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            pressed = true;
            mouseX = x;
            mouseY = y;
        } else {
            pressed = false;
        }
    }

    glutPostRedisplay();
}
