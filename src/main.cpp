#include <iostream>
#include <cmath> // Necessário para sin() e cos()
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Protótipo da função de callback para redimensionamento da janela
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

int main() {
    // 1. Inicialização do GLFW
    if (!glfwInit()) {
        std::cout << "Falha ao inicializar GLFW.\n";
        return -1;
    }

    // Configurações do contexto OpenGL (Versão 3.3 Core Profile)
    glfwWindowHint(GLFW_SAMPLES, 4); // Anti-aliasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // 2. Criação da Janela
    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Test - Dynamic Colors", NULL, NULL);
    if (window == NULL) {
        std::cout << "Falha ao criar a janela GLFW.\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    
    // Define a função de callback para quando a janela for redimensionada
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // 3. Inicialização do GLAD (Carrega os ponteiros das funções OpenGL)
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Falha ao inicializar GLAD.\n";
        return -1;
    }

    // 4. Loop de Renderização Principal
    while (!glfwWindowShouldClose(window)) {
        // --- Lógica de Cores Dinâmicas ---
        float timeValue = glfwGetTime(); // Tempo em segundos desde o início
        
        // As funções sin e cos retornam valores entre -1.0 e 1.0. 
        // Ajustamos para o intervalo 0.0 a 1.0 para as cores (RGB).
        float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
        float blueValue = (cos(timeValue) / 2.0f) + 0.5f;

        // Define a cor de fundo (R, G, B, A)
        glClearColor(0.1f, greenValue, blueValue, 1.0f);
        
        // Limpa o buffer de cor
        glClear(GL_COLOR_BUFFER_BIT);

        // --- Troca de Buffers e Eventos ---
        glfwSwapBuffers(window); // Troca o buffer de desenho pelo buffer de exibição
        glfwPollEvents();        // Verifica eventos de entrada (teclado/mouse)
    }

    // 5. Finalização
    glfwTerminate();
    return 0;
}