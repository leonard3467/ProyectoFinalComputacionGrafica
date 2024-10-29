#include "Animaciones.h"
Animaciones::Animaciones()
{
}
void Animaciones::animacionDado8Caras(float* rotDadox, float* rotDadoy, float* rotDadoz, float* rotDadoxOffset, float* rotDadoyOffset, float* rotDadozOffset, float* movDado, float* movOffset, Window& mainWindow, float* deltaTime) {
    if (mainWindow.getAvanza() == true) {
        // Inicializar el generador de números aleatorios solo una vez
        //en 2 se queda paralela al suelo
        // // teoria cada 90 grados se va moviendo en una nueva cara 
        // para obtener el numero 3 rotar directamente 52 grados en eje x 
        // para obtener elnuemro 2 rotar 52 grados en x y 90 en y 
        // para obtener el numero 8 rotar -52 gradosx
        // para obtener el numero 5 rotar  -52 grados en z 
        // con eso concluye cara piramide superiro
        // 180 grados en x para poder mostrar la cara de abajo
        // para obtener el numero 4 rotar 52 grados en z 
        // para obtener el numero 7 rotar -52 grados en z
        // para obtener el numero 1 rotar -52 grados en eje x 
        // para obtener el numero 6 rotar 52 grados en eje x 
        static bool initialized = false;
        
        if (!initialized) {
            std::srand(static_cast<unsigned int>(std::time(nullptr)));
            initialized = true;
        }
        if (!numRandom) {
            randomNumber = (std::rand() % 8) + 1;
           
            numRandom = true;
        }

        if (*movDado > -10.0f) {
            *movDado -= (*movOffset) * (*deltaTime);
        }

        switch (randomNumber) {
        case 1:
            if (*rotDadox > -360 - 52 - 180) {
                *rotDadox -= (*rotDadoxOffset) * (*deltaTime);
            }
            if (*rotDadoy < 360) {
                *rotDadoy += (*rotDadoyOffset) * .7*(*deltaTime);
            }
            break;

        case 2:
            if (*rotDadoy < 360 + 90) {
                *rotDadoy += (*rotDadoyOffset) * .7 * (*deltaTime);
            }
            if (*rotDadox < 360 + 52) {
                *rotDadox += (*rotDadoxOffset) * .7 * (*deltaTime);
            }
            break;

        case 3:
            if (*rotDadox < 360 + 52) {
                *rotDadox += (*rotDadoxOffset) * .7*(*deltaTime);
            }
            if (*rotDadoz > -360) {
                *rotDadoz -= (*rotDadozOffset) * .7*(*deltaTime);  
            }
            // multiplicamos por un escalar para que se vea natural la caida
            
            break;

        case 4:
            if (*rotDadox < 360 + 180) {
                *rotDadox += (*rotDadoxOffset) * .9 * (*deltaTime);
            }
            if (*rotDadoz < 360 - 52) {
                *rotDadoz += (*rotDadozOffset) * .8 * (*deltaTime);
            }
           
            break;

        case 5:
            if (*rotDadoz > -360 - 52) {
                *rotDadoz -= (*rotDadozOffset) *.7*(*deltaTime);
            }
            if (*rotDadoy > -360 ) {
                *rotDadoy -= (*rotDadoyOffset) * .8 * (*deltaTime);
            }
            break;

        case 6:
            if (*rotDadox < 52+360+180) {
                *rotDadox += (*rotDadoxOffset) * .8*(*deltaTime);
            }
            if (*rotDadoz < 360) {
                *rotDadoz += (*rotDadozOffset) *.9* (*deltaTime);
            }
            
            break;

        case 7:
            if (*rotDadox < 360 + 180) {
                *rotDadox += (*rotDadoxOffset) * (*deltaTime);
            }
            if (*rotDadoz < 360 - 52) {
                *rotDadoz += (*rotDadozOffset) * (*deltaTime);
            }
            break;

        case 8:
            if (*rotDadox > -360 - 52) {
                *rotDadox -= (*rotDadoxOffset) * .7 * (*deltaTime);
            }
            
            if (*rotDadoy < 360 ) {
                *rotDadoy += (*rotDadoyOffset) * (*deltaTime);
            }
            break;

     
        }

    }
    else {
        *movDado = 0.0f;
        *movOffset = 0.05f;
        *rotDadox = 0.0f;
        *rotDadoxOffset = 3.0f;
        *rotDadoy = 0.0f;
        *rotDadoyOffset = 3.0f;
        *rotDadoz = 0.0f;
        *rotDadozOffset = 3.0f;
        numRandom = false;
    }
}