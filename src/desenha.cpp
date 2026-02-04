bool cameraSendoSeguida = false;
float posX = 0.0f, posZ = 0.0f;
float angulo = 0.0f;          


void desenhaTerreno() {
    glBegin(GL_QUADS);
    glColor3f(0.2f, 0.5f, 0.2f); 
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
        
      
        glColor3f(0.0f, 0.0f, 1.0f);
        glutSolidCube(1.0f); 
        
      
        glTranslatef(0, 0, 0.6f);
        glColor3f(1.0f, 0.0f, 0.0f);
        glutSolidCube(0.2f);
    glPopMatrix();
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
    desenhaPersonagem();

    glutSwapBuffers();
}