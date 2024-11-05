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
            randomNumber1 = (std::rand() % 8) + 1;
            printf(" \nel numero random numero 1 para dado de 8 caras es de : %d \n", randomNumber1);
            cantidadCasillas += randomNumber1;
            numRandom = true;
        }

        if (*movDado > -10.0f) {
            *movDado -= (*movOffset) * (*deltaTime);
        }

        switch (randomNumber1) {
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
            if (*rotDadoz > -360 + 52) {
                *rotDadoz -= (*rotDadozOffset) * .7 * (*deltaTime);
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
void Animaciones::animacionDado4Caras(float* rotDado4x, float* rotDado4y, float* rotDado4z, float* rotDado4xOffset, float* rotDado4yOffset, float* rotDado4zOffset, float* movDado4, float* mov4Offset, Window& mainWindow, float* deltaTime) {
    
    //punto mas bajo  4 en 3
        //PARA 3 CON SIMPLEMENTA BAJAR EN 4 QUEDA
        //para 4 rottar en x -110  pero el punto mas bajo pasa a ser de 0
        //para 1  angulo en x de 27   angulo en y de -12  y en z de -105
        //para 2 es rotacion en x de 250  y en y de -120 
    if (mainWindow.getAvanza() == true) {
        static bool initialized = false;

        if (!initialized) {
            std::srand(static_cast<unsigned int>(std::time(nullptr)));
            initialized = true;
        }
        if (!numRandom1) {
            randomNumber2 = (std::rand() % 4) + 1;
            printf(" \nel numero random numero 2 para dado de 4 caras es de : %d \n", randomNumber2);
            cantidadCasillas += randomNumber2;
            printf(" \n ----- nos dezplazaremos : %d \n", cantidadCasillas);
            numRandom1 = true;
        }

        if (randomNumber2 == 3){
            if(*movDado4 > -10.0f) {
                *movDado4 -= (*mov4Offset) * (*deltaTime);
            }
        }
        else {
            if (*movDado4 > -14.0f) {
                *movDado4 -= (*mov4Offset) * (*deltaTime);
            }
        }

        switch (randomNumber2) {
        case 1:
            if (*rotDado4x < 360 + 27) {
                *rotDado4x += (*rotDado4xOffset) * .5 * (*deltaTime);
            }
            if (*rotDado4y > -360-12) {
                *rotDado4y -= (*rotDado4yOffset) * .8 * (*deltaTime);
            }
            if (*rotDado4z > -360 - 105) {
                *rotDado4z -= (*rotDado4zOffset) * .7 * (*deltaTime);
            }
            break;

        case 2:
            if (*rotDado4y > -360 - 120) {
                *rotDado4y -= (*rotDado4yOffset) * .6* (*deltaTime);
            }
            if (*rotDado4x <  250) {
                *rotDado4x += (*rotDado4xOffset) * .8 * (*deltaTime);
            }
            break;

        case 3:
            if (*rotDado4x > -360) {
                *rotDado4x -= (*rotDado4xOffset) * (*deltaTime);
            }
            if (*rotDado4y < 360) {
                *rotDado4y += (*rotDado4yOffset) * .7 * (*deltaTime);
            }
            break;

        case 4:
            if (*rotDado4x > -360-110) {
                *rotDado4x -= (*rotDado4xOffset) * .6* (*deltaTime);
            }
            if (*rotDado4z < 360 ) {
                *rotDado4z += (*rotDado4zOffset) * .4 * (*deltaTime);
            }

            break;

       

        }

    }
    else {
        *movDado4 = 0.0f;
        *mov4Offset = 0.05f;
        *rotDado4x = 0.0f;
        *rotDado4xOffset = 3.0f;
        *rotDado4y = 0.0f;
        *rotDado4yOffset = 3.0f;
        *rotDado4z = 0.0f;
        *rotDado4zOffset = 3.0f;
        numRandom1 = false;
        cantidadCasillas = 0;
    }
}

void Animaciones::movimientoTablero(glm::vec3& posicion, float& rotacionBender, float& saltoBenderY, float& desplazamientoBender, int& pasos , float& deltaTime,Window& mainWindow, float& Tiempo,float& desplazamientoBenderz, float& rotacionBenderAux) {
    // el offset de el dezplazamiento de mi modelo sera siempre de .05
    GLfloat rotacionBenderauxiliar = 0;
    GLfloat desplazamientoBenderauxiliar = 0;
   if (cantidadCasillas !=0 ) {
       // esquina inferior izquierda
        if (posicion.x > -32.0f && posicion.x < -22.0f && posicion.z > -34.0f && posicion.z < -24.0f) {
            if (rotacionBender > -90.0f) {
                rotacionBender -= (.5f) * (deltaTime);
            }
            else if (desplazamientoBender < 7.75f && rotacionBender < -90.0f) {
                desplazamientoBender += (.05f) * (deltaTime);
            }
            else if (desplazamientoBender > 7.75f) {
                cantidadCasillas--;
                rotacionBenderAux -= 90;
                rotacionBender = 0;
                posicion.x += 7.75f;
                desplazamientoBender = 0;
                std::cout << "Posición actual del modelo: "
                    << "X: " << posicion.x << ", "
                    << "Y: " << posicion.y << ", "
                    << "Z: " << posicion.z << std::endl;
            }

        }
        // esquina inferior derecha
        else if (posicion.x >= 22.0f && posicion.x <= 32.0f && posicion.z >= -34.0f && posicion.z <= -24.0f) {
            if (rotacionBender > -90.0f) {
                rotacionBender -= (.5f) * (deltaTime);
            }else if (desplazamientoBenderz < 7.4f && rotacionBender < -90.0f) {
                desplazamientoBenderz += (.05f) * (deltaTime);
               
            }
            else if (desplazamientoBenderz > 7.4f) {
                cantidadCasillas--;
                rotacionBenderAux -= 90;
                rotacionBender = 0;
                posicion.z += 7.4f;
                desplazamientoBenderz = 0;
                std::cout << "Posición actual del modelo: "
                    << "X: " << posicion.x << ", "
                    << "Y: " << posicion.y << ", "
                    << "Z: " << posicion.z << std::endl;
                
            }

        }
        // esquina Superior derecha
        else if (posicion.x >= 22.0f && posicion.x <= 32.0f && posicion.z >= 24.0f && posicion.z <= 34.0f) {
            if (rotacionBender  > -90.0f) {
                rotacionBender -= (.5f) * (deltaTime);
            }
            else if (desplazamientoBender  > -7.75f && rotacionBender < -90.0f) {
                desplazamientoBender -= (.05f) * (deltaTime);
            }
            else if (desplazamientoBender < -7.75f) {
                cantidadCasillas--;
                rotacionBenderAux -= 90;
                rotacionBender = 0;
                posicion.x -= 7.75f;
                desplazamientoBender = 0;
                std::cout << "Posición actual del modelo: "
                    << "X: " << posicion.x << ", "
                    << "Y: " << posicion.y << ", "
                    << "Z: " << posicion.z << std::endl;
            }

        }
        // esquina Superior Izquierda
        if (posicion.x >= -32.0f && posicion.x <= -22.0f && posicion.z >= 24.0f && posicion.z <= 34.0f) {
            if (rotacionBender > -90.0f) {
                rotacionBender -= (.5f) * (deltaTime);

            }
            else if (desplazamientoBenderz  > -7.4f && rotacionBender < -90.0f) {
                desplazamientoBenderz -= (.05f) * (deltaTime);
            }
            else if (desplazamientoBenderz < -7.4f) {
                cantidadCasillas--;
                rotacionBenderAux -= 90;
                rotacionBender = 0;
                posicion.z -= 7.4f;
                desplazamientoBenderz = 0;
                std::cout << "Posición actual del modelo: "
                    << "X: " << posicion.x << ", "
                    << "Y: " << posicion.y << ", "
                    << "Z: " << posicion.z << std::endl;
            }

        }
        // lineas verticales 1
        else if ((posicion.x >= -22.0f && posicion.x <= 22.0f) && posicion.z <= -29.0f) {
            if (posicion.x == 19.25f) {
                if (desplazamientoBender < 7.75f) {
                    desplazamientoBender += (.05f) * (deltaTime);

                }
                else if (desplazamientoBender > 7.75f) {
                    cantidadCasillas--;

                    posicion.x += 7.75f;
                    desplazamientoBender = 0;
                    std::cout << "Posición actual del modelo: "
                        << "X: " << posicion.x << ", "
                        << "Y: " << posicion.y << ", "
                        << "Z: " << posicion.z << std::endl;
                }
            }
            else {
                if (desplazamientoBender < 5.5f) {
                    desplazamientoBender += (.05f) * (deltaTime);
                }
                else if (desplazamientoBender > 5.5f) {
                    cantidadCasillas--;

                    posicion.x += 5.5f;
                    desplazamientoBender = 0;
                    std::cout << "Posición actual del modelo: "
                        << "X: " << posicion.x << ", "
                        << "Y: " << posicion.y << ", "
                        << "Z: " << posicion.z << std::endl;
                }
            }
            

        }
        // lineas verticales 2
        else if ((posicion.x >= -22.0f && posicion.x <= 22.0f) && posicion.z >= 29.0f) {
            if ( posicion.x == -19.25f) {
                if (desplazamientoBender  > -7.75f) {
                    desplazamientoBender -= (.05f) * (deltaTime);

                }
                else if (desplazamientoBender < -7.75f) {
                    cantidadCasillas--;

                    posicion.x -= 7.75f;
                    desplazamientoBender = 0;
                    std::cout << "Posición actual del modelo: "
                        << "X: " << posicion.x << ", "
                        << "Y: " << posicion.y << ", "
                        << "Z: " << posicion.z << std::endl;
                }
            }
            else {
                if (desplazamientoBender  > -5.5f) {
                    desplazamientoBender -= (.05f) * (deltaTime);
                }
                else if (desplazamientoBender < -5.5f) {
                    cantidadCasillas--;

                    posicion.x -= 5.5f;
                    desplazamientoBender = 0;
                    std::cout << "Posición actual del modelo: "
                        << "X: " << posicion.x << ", "
                        << "Y: " << posicion.y << ", "
                        << "Z: " << posicion.z << std::endl;
                }
            }


        }
        // Lineas Horizontales
        else if ((posicion.z >= -24.0f && posicion.z <= 24.0f) && posicion.x == 27.0f) {
            if ( posicion.z >= 21.6f) { // se pone mayur  o igual ya que puede que el aumento lo tetecte como 21.600000000005 
                if (desplazamientoBenderz < 7.4f) {
                    desplazamientoBenderz += (.05f) * (deltaTime);
                }
                else if (desplazamientoBenderz > 7.4f) {
                    cantidadCasillas--;
                    posicion.z += 7.4f;
                    desplazamientoBenderz = 0;
                    std::cout << "-----Posición actual del modelo: "
                        << "X: " << posicion.x << ", "
                        << "Y: " << posicion.y << ", "
                        << "Z: " << posicion.z << std::endl;
                }
            }
            else {
                if (desplazamientoBenderz < 4.8f) {
                    desplazamientoBenderz += (.05f) * (deltaTime);
                }
                else if (desplazamientoBenderz > 4.8f) {
                    cantidadCasillas--;
                    posicion.z += 4.8f;
                    desplazamientoBenderz = 0;
                    std::cout << "Posición actual del modelo: "
                        << "X: " << posicion.x << ", "
                        << "Y: " << posicion.y << ", "
                        << "Z: " << posicion.z << std::endl;

                }
            }
        }
        // Lineas Horizontales 2
        else if ((posicion.z >= -24.0f && posicion.z <= 24.0f) && posicion.x == -27.0f) {
            if (posicion.z >= -21.7f && posicion.z <= -21.5f) {
                if (desplazamientoBenderz  > -7.4f) {
                   
                    desplazamientoBenderz -= (.05f) * (deltaTime);
                }
                else if (desplazamientoBenderz < -7.4f) {
                    // como esta es la casilla en general vamos a resetear todooo
                    cantidadCasillas--;
                    posicion.x = -27.0f;
                    posicion.y =  2.5f;
                    posicion.z = -29.0f;
                    desplazamientoBenderz = 0;
                    desplazamientoBender = 0;
                    rotacionBender = 0;
                    rotacionBenderAux = 0;
                    std::cout << "-----Posición actual del modelo: "
                        << "X: " << posicion.x << ", "
                        << "Y: " << posicion.y << ", "
                        << "Z: " << posicion.z << std::endl;
                }
            }
            else {
                if (desplazamientoBenderz > -4.8f) {
                    desplazamientoBenderz -= (.05f) * (deltaTime);
                }
                else if (desplazamientoBenderz < -4.8f) {
                    cantidadCasillas--;
                    posicion.z -= 4.8f;
                    desplazamientoBenderz = 0;
                    std::cout << "Posición actual del modelo: "
                        << "X: " << posicion.x << ", "
                        << "Y: " << posicion.y << ", "
                        << "Z: " << posicion.z << std::endl;

                }
            }
            }
   }

}
        
    
