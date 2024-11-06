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
    void movimientoTableroBender(glm::vec3& posicion, float& rotacionBender, float& saltoBenderY, float& desplazamientoBender, int& pasos, float& deltaTime, Window& mainWindow, float& Tiempo, float& desplazamientoBenderz, float& rotacionBenderAux);
    void movimientoTableroDipper(glm::vec3& posicion, float& rotacionBender, float& saltoBenderY, float& desplazamientoBender, int& pasos, float& deltaTime, Window& mainWindow, float& Tiempo, float& desplazamientoBenderz, float& rotacionBenderAux);

    //animaciones para tablero modelos
    void animacionTablero(float& posYObjeto, float& rotacionObjeto, float deltaTime, float Tiempo);
    void controlAnimacionTablero(glm::vec3& posicion,
        float& posY1, float& rotacion1,
        float& posY2, float& rotacion2,
        float& posY3, float& rotacion3,
        float& posY4, float& rotacion4,
        float& posY5, float& rotacion5,
        float& posY6, float& rotacion6,
        float& posY7, float& rotacion7,
        float& posY8, float& rotacion8,
        float& posY9, float& rotacion9,
        float& posY10, float& rotacion10,
        float& posY11, float& rotacion11,
        float& posY12, float& rotacion12,
        float& posY13, float& rotacion13,
        float& posY14, float& rotacion14,
        float& posY15, float& rotacion15,
        float& posY16, float& rotacion16,
        float& posY17, float& rotacion17,
        float& posY18, float& rotacion18,
        float& posY19, float& rotacion19,
        float& posY20, float& rotacion20,
        float& posY21, float& rotacion21,
        float& posY22, float& rotacion22,
        float& posY23, float& rotacion23,
        float& posY24, float& rotacion24,
        float& posY25, float& rotacion25,
        float& posY26, float& rotacion26,
        float& posY27, float& rotacion27,
        float& posY28, float& rotacion28,
        float& posY29, float& rotacion29,
        float& posY30, float& rotacion30,
        float& posY31, float& rotacion31,
        float& posY32, float& rotacion32,
        float& posY33, float& rotacion33,
        float& posY34, float& rotacion34,
        float& posY35, float& rotacion35,
        float& posY36, float& rotacion36,
        float& posY37, float& rotacion37,
        float& posY38, float& rotacion38,
        float& posY39, float& rotacion39,
        float& posY40, float& rotacion40,
        float deltaTime, float Tiempo);
    int obtenerIDCasilla(glm::vec3& posicion);
    // Declaraciones públicas de las variables
    int randomNumber1;
    int randomNumber2;
    int cantidadCasillas = 0;
    bool numRandom = false;
    bool numRandom1 = false;
    bool animacionActiva = false;
    GLfloat tiempo3segundos;
};