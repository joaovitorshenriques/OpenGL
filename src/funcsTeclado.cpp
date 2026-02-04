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