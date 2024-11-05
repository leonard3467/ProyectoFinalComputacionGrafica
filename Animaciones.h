#pragma once
#include <iostream>
#include <cstdlib> // Para std::srand y std::rand
#include <ctime>   // Para std::time
#include "Window.h" // Para las banderas de el teclado 
#include <vector>
#include <glew.h>
#include <glfw3.h>
#include <glm.hpp>
class Animaciones
{
public:
    Animaciones();
    // Método que sincroniza las animaciones de manera básica para un dado de 8 caras
    void animacionDado8Caras(float* rotDadox, float* rotDadoy, float* rotDadoz, float* rotDadoxOffset, float* rotDadoyOffset, float* rotDadozOffset, float* movDado, float* movOffset, Window& mainWindow, float* deltaTime);
    void animacionDado4Caras(float* rotDado4x, float* rotDado4y, float* rotDado4z, float* rotDado4xOffset, float* rotDado4yOffset, float* rotDado4zOffset, float* movDado4, float* mov4Offset, Window& mainWindow, float* deltaTime);
    void movimientoTablero(glm::vec3& posicion, float& rotacionBender, float& saltoBenderY, float& desplazamientoBender, int& pasos, float& deltaTime,  Window& mainWindow, float& Tiempo, float& desplazamientoBenderz, float& rotacionBenderAux);
    // Declaraciones públicas de las variables
    int randomNumber1;
    int randomNumber2;
    int cantidadCasillas=0;
    bool numRandom = false;
    bool numRandom1 = false;
};