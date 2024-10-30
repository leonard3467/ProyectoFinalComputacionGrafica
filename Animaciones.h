#pragma once

#include <cstdlib> // Para std::srand y std::rand
#include <ctime>   // Para std::time
#include "Window.h" // Para las banderas de el teclado 

class Animaciones
{
public:
    Animaciones();
    // M�todo que sincroniza las animaciones de manera b�sica para un dado de 8 caras
    void animacionDado8Caras(float* rotDadox, float* rotDadoy, float* rotDadoz, float* rotDadoxOffset, float* rotDadoyOffset, float* rotDadozOffset, float* movDado, float* movOffset, Window& mainWindow, float* deltaTime);

    // Declaraciones p�blicas de las variables
    int randomNumber;
    bool numRandom = false;
};