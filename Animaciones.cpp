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
                *rotDadoy += (*rotDadoyOffset) * .7 * (*deltaTime);
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
                *rotDadox += (*rotDadoxOffset) * .7 * (*deltaTime);
            }
            if (*rotDadoz > -360) {
                *rotDadoz -= (*rotDadozOffset) * .7 * (*deltaTime);
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
                *rotDadoz -= (*rotDadozOffset) * .7 * (*deltaTime);
            }
            if (*rotDadoy > -360) {
                *rotDadoy -= (*rotDadoyOffset) * .8 * (*deltaTime);
            }
            break;

        case 6:
            if (*rotDadox < 52 + 360 + 180) {
                *rotDadox += (*rotDadoxOffset) * .8 * (*deltaTime);
            }
            if (*rotDadoz < 360) {
                *rotDadoz += (*rotDadozOffset) * .9 * (*deltaTime);
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

            if (*rotDadoy < 360) {
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

        if (randomNumber2 == 3) {
            if (*movDado4 > -10.0f) {
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
            if (*rotDado4y > -360 - 12) {
                *rotDado4y -= (*rotDado4yOffset) * .8 * (*deltaTime);
            }
            if (*rotDado4z > -360 - 105) {
                *rotDado4z -= (*rotDado4zOffset) * .7 * (*deltaTime);
            }
            break;

        case 2:
            if (*rotDado4y > -360 - 120) {
                *rotDado4y -= (*rotDado4yOffset) * .6 * (*deltaTime);
            }
            if (*rotDado4x < 250) {
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
            if (*rotDado4x > -360 - 110) {
                *rotDado4x -= (*rotDado4xOffset) * .6 * (*deltaTime);
            }
            if (*rotDado4z < 360) {
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

void Animaciones::movimientoTableroBender(glm::vec3& posicion, float& rotacionBender, float& saltoBenderY, float& desplazamientoBender, int& pasos, float& deltaTime, Window& mainWindow, float& Tiempo, float& desplazamientoBenderz, float& rotacionBenderAux) {
    // el offset de el dezplazamiento de mi modelo sera siempre de .05
    GLfloat rotacionBenderauxiliar = 0;
    GLfloat desplazamientoBenderauxiliar = 0;
    if (cantidadCasillas != 0 && mainWindow.turno==2) {
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
            }
            else if (desplazamientoBenderz < 7.4f && rotacionBender < -90.0f) {
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
            if (rotacionBender > -90.0f) {
                rotacionBender -= (.5f) * (deltaTime);
            }
            else if (desplazamientoBender > -7.75f && rotacionBender < -90.0f) {
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
            else if (desplazamientoBenderz > -7.4f && rotacionBender < -90.0f) {
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
            if (posicion.x == -19.25f) {
                if (desplazamientoBender > -7.75f) {
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
                if (desplazamientoBender > -5.5f) {
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
            if (posicion.z >= 21.6f) { // se pone mayur  o igual ya que puede que el aumento lo tetecte como 21.600000000005 
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
                if (desplazamientoBenderz > -7.4f) {

                    desplazamientoBenderz -= (.05f) * (deltaTime);
                }
                else if (desplazamientoBenderz < -7.4f) {
                    // como esta es la casilla en general vamos a resetear todooo
                    cantidadCasillas--;
                    posicion.x = -27.0f;
                    posicion.y = 2.5f;
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
void Animaciones::movimientoTableroDipper(glm::vec3& posicion, float& rotacionBender, float& saltoBenderY, float& desplazamientoBender, int& pasos, float& deltaTime, Window& mainWindow, float& Tiempo, float& desplazamientoBenderz, float& rotacionBenderAux) {
    // el offset de el dezplazamiento de mi modelo sera siempre de .05
    GLfloat rotacionBenderauxiliar = 0;
    GLfloat desplazamientoBenderauxiliar = 0;
    if (cantidadCasillas != 0 && mainWindow.turno == 1) {
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
            }
            else if (desplazamientoBenderz < 7.4f && rotacionBender < -90.0f) {
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
            if (rotacionBender > -90.0f) {
                rotacionBender -= (.5f) * (deltaTime);
            }
            else if (desplazamientoBender > -7.75f && rotacionBender < -90.0f) {
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
            else if (desplazamientoBenderz > -7.4f && rotacionBender < -90.0f) {
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
            if (posicion.x == -19.25f) {
                if (desplazamientoBender > -7.75f) {
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
                if (desplazamientoBender > -5.5f) {
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
            if (posicion.z >= 21.6f) { // se pone mayur  o igual ya que puede que el aumento lo tetecte como 21.600000000005 
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
                if (desplazamientoBenderz > -7.4f) {

                    desplazamientoBenderz -= (.05f) * (deltaTime);
                }
                else if (desplazamientoBenderz < -7.4f) {
                    // como esta es la casilla en general vamos a resetear todooo
                    cantidadCasillas--;
                    posicion.x = -27.0f;
                    posicion.y = 2.5f;
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

//parte animacion de otro modelos


void Animaciones::animacionTablero(float& posYObjeto, float& rotacionObjeto, float deltaTime,float Tiempo) {
    if (!animacionActiva ) {
        tiempo3segundos = Tiempo + 3.0f;
        animacionActiva = true;
    }
    // Usar `objetoID` para cambiar el comportamiento de la animación
    if (animacionActiva && cantidadCasillas == 0) {
        if (posYObjeto < 5.0f && Tiempo < tiempo3segundos ) {
            posYObjeto += 2.0f * deltaTime;
            rotacionObjeto += 90.0f * deltaTime;
        }
        else if (Tiempo >= tiempo3segundos) {
            posYObjeto -= 2.0f * deltaTime;
            rotacionObjeto += 90.0f * deltaTime;
            if (posYObjeto <= -5.0f) {
                animacionActiva = false;
                posYObjeto = -5.0f;
                rotacionObjeto = 0.0f;
            }
        }
    }
}
// Función para convertir (X, Z) a un ID de casilla único
/*int Animaciones::obtenerIDCasilla(float posXBici, float posZBici) {
    if (posXBici == -28.0098f && posZBici == -24.488f) return 1; // Inicio casilla perro
    if (posXBici == -28.0098f && posZBici == -18.8f) return 2; // Inicio casilla
    if (posXBici == -28.0098f && posZBici == -15.08f) return 3; //Inicio casilla
    if (posXBici == -28.0098f && posZBici == -10.77f) return 4; //Inicio casilla
    if (posXBici == -28.0098f && posZBici == -5.18f) return 5; //Inicio casilla
    if (posXBici == -28.0098f && posZBici == -0.49f) return 6; //Inicio casilla elefanbra
    if (posXBici == -28.0098f && posZBici == 4.29f) return 7; //Inicio casilla nueva luz
    if (posXBici == -28.0098f && posZBici == 9.53f) return 8; //Inicio casilla kinopio
    if (posXBici == -28.0098f && posZBici == 13.31f) return 9; //Inicio casilla oink
    if (posXBici == -28.0098f && posZBici == 18.68f) return 10; //Inicio casilla Puerto diversion
    if (posXBici == -28.0098f && posZBici == 22.37f) return 11; //Inicio casilla Insert Coin
    if (posXBici == -21.66f && posZBici == 28.0299f) return 12; //Inicio casilla mordelon
    if (posXBici == -16.08f && posZBici == 28.0299f) return 13; //Inicio casilla te tengo
    if (posXBici == -10.97f && posZBici == 28.0299f) return 14; //Inicio casilla destronador
    if (posXBici == -5.43f && posZBici == 28.0299f) return 15; //Inicio casilla trebol 7
    if (posXBici == -0.28f && posZBici == 28.0299f) return 16; //Inicio casilla estafado
    if (posXBici == 5.17f && posZBici == 28.0299f) return 17; //Inicio casilla Mazmorra
    if (posXBici == 10.2f && posZBici == 28.0299f) return 18; //Inicio casilla devorado
    if (posXBici == 16.28f && posZBici == 28.0299f) return 19; //Inicio casilla gnomo
    if (posXBici == 21.49f && posZBici == 28.0299f) return 20; //Inicio casilla Palacio (esquina)
    if (posXBici == 28.0067f && posZBici == 23.08f) return 21; //Inicio casilla saltarin
    if (posXBici == 28.0067f && posZBici == 18.87f) return 22; //Inicio casilla GOAT
    if (posXBici == 28.0067f && posZBici == 14.28f) return 23; //Inicio casilla a comer
    if (posXBici == 28.0067f && posZBici == 9.32f) return 24; //Inicio casilla mr langosta
    if (posXBici == 28.0067f && posZBici == 4.05f) return 25; //Inicio casilla mansion noroeste
    if (posXBici == 28.0067f && posZBici == 0.34f) return 26; //Inicio casilla furia
    if (posXBici == 28.0067f && posZBici == -4.67f) return 27; //Inicio casilla cuidado
    if (posXBici == 28.0067f && posZBici == -9.55f) return 28; //Inicio casilla relajate
    if (posXBici == 28.0067f && posZBici == -14.27f) return 29; //Inicio casilla castillo de terror
    if (posXBici == 28.0067f && posZBici == -18.64f) return 30; //Inicio casilla lento
    if (posXBici == 28.0067f && posZBici == -23.99f) return 31; //Inicio casilla Mystery Shack
    if (posXBici == 21.82f && posZBici == -28.0086f) return 32; //Inicio casilla yahoo
    if (posXBici == 15.99f && posZBici == -28.0086f) return 33; //Inicio casilla esperanza
    if (posXBici == 10.08f && posZBici == -28.0086f) return 34; //Inicio casilla sr bulldog
    if (posXBici == 4.87f && posZBici == -28.0086f) return 35; //Inicio casilla impacto
    if (posXBici == -0.20f && posZBici == -28.0086f) return 36; //Inicio casilla determined
    if (posXBici == -4.97f && posZBici == -28.0086f) return 37; //Inicio casilla brillantina
    if (posXBici == -10.72f && posZBici == -28.0086f) return 38; //Inicio casilla floripondio
    if (posXBici == -15.95f && posZBici == -28.0086f) return 39; //Inicio casilla chapoteo
    if (posXBici == -20.9104f && posZBici == -28.0086f) return 40; //Inicio casilla start
    return -1;  // Retorna -1 si no hay coincidencia
}*/


int Animaciones::obtenerIDCasilla(glm::vec3& posicion) {
    //Esquina start
    if (posicion.x > -32.0f && posicion.x < -22.0f && posicion.z > -34.0f && posicion.z < -24.0f) {
        return 1;
    }
    else if ((posicion.x >= -32.0f && posicion.x <= 32.0f) && posicion.z > -34.0f && posicion.z < -24.0f) {
        if (posicion.x >= -22.0f && posicion.x < -16.5f) return 2;
        else if (posicion.x >= -16.5f && posicion.x < -11.0f) return 3;
        else if (posicion.x >= -11.0f && posicion.x < -5.5f) return 4;
        else if (posicion.x >= -5.5f && posicion.x < 0.0f) return 5;
        else if (posicion.x >= 0.0f && posicion.x < 5.5f) return 6;
        else if (posicion.x >= 5.5f && posicion.x < 11.0f) return 7;
        else if (posicion.x >= 11.0f && posicion.x < 16.5f) return 8;
        else if (posicion.x >= 16.5f && posicion.x <= 22.0f) return 9;
        else if (posicion.x >= 22.0f && posicion.x <= 32.0f) return 10;
    }
    else if (posicion.z >= -24.0f && posicion.z <= 34.0f && posicion.x >= 22.0f && posicion.x <= 32.0f) {
        if (posicion.z >= -24.0f && posicion.z < -19.2f) return 11;
        if (posicion.z >= -19.2f && posicion.z < -14.4f) return 12;
        if (posicion.z >= -14.4f && posicion.z < -9.6f) return 13;
        if (posicion.z >= -9.6f && posicion.z < -4.8f) return 14;
        if (posicion.z >= -4.8f && posicion.z < 0.0f) return 15;
        if (posicion.z >= 0.0f && posicion.z < 4.8f) return 16;
        if (posicion.z >= 4.8f && posicion.z < 9.6f) return 17;
        if (posicion.z >= 9.6f && posicion.z < 14.4f) return 18;
        if (posicion.z >= 14.4f && posicion.z < 19.2f) return 19;
        if (posicion.z >= 19.2f && posicion.z <= 24.0f) return 20;
        if (posicion.z >= 24.0f && posicion.z <= 34.0f) return 21;
    }
    else if (posicion.x >= -32.0f && posicion.x <= 22.0f && posicion.z >= 24.0f && posicion.z <= 34.0f) {
        if (posicion.x <= 22.0f && posicion.x > 16.5f) return 22;
        if (posicion.x <= 16.5f && posicion.x > 11.0f) return 23;
        if (posicion.x <= 11.0f && posicion.x > 5.5f) return 24;
        if (posicion.x <= 5.5f && posicion.x > 0.0f) return 25;
        if (posicion.x <= 0.0f && posicion.x > -5.5f) return 26;
        if (posicion.x <= -5.5f && posicion.x > -11.0f) return 27;
        if (posicion.x <= -11.0f && posicion.x > -16.5f) return 28;
        if (posicion.x <= -16.5f && posicion.x >= -22.0f) return 29;
        if (posicion.x <= -22.0f && posicion.x >= -32.0f) return 30;
    }
    else if (posicion.x >= -32.0f && posicion.x <= -22.0f && posicion.z >= -24.0f && posicion.z <= 34.0f) {
        if (posicion.z <= 24.0f && posicion.z > 19.2f) return 31;
        if (posicion.z <= 19.2f && posicion.z > 14.4f) return 32;
        if (posicion.z <= 14.4f && posicion.z > 9.6f) return 33;
        if (posicion.z <= 9.6f && posicion.z > 4.8f) return 34;
        if (posicion.z <= 4.8f && posicion.z > 0.0f) return 35;
        if (posicion.z <= 0.0f && posicion.z > -4.8f) return 36;
        if (posicion.z <= -4.8f && posicion.z > -9.6f) return 37;
        if (posicion.z <= -9.6f && posicion.z > -14.4f) return 38;
        if (posicion.z <= -14.4f && posicion.z > -19.2f) return 39;
        if (posicion.z <= -19.2f && posicion.z >= -24.0f) return 40;
    }
    return -1; /// Retorna -1 si no hay coincidencia


}

/*
void Animaciones::controlAnimacionTablero(float posXBici, float posZBici,
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
    float deltaTime) {
    int idCasilla = obtenerIDCasilla(posXBici, posZBici);
    switch (idCasilla) {
    case 1:  // Casilla 1
        animacionTablero(posY1, rotacion1, deltaTime);
        break;
    case 2:  // Casilla 2
        animacionTablero(posY2, rotacion2, deltaTime);
        break;
    case 3:  // Casilla 3
        animacionTablero(posY3, rotacion3, deltaTime);
        break;
    case 4:  // Casilla 4
        animacionTablero(posY4, rotacion4, deltaTime);
        break;
    case 5:
        animacionTablero(posY5, rotacion5, deltaTime);
        break;
    case 6:
        animacionTablero(posY6, rotacion6, deltaTime);
        break;
    case 7:
        animacionTablero(posY7, rotacion7, deltaTime);
        break;
    case 8:
        animacionTablero(posY8, rotacion8, deltaTime);
        break;
    case 9:
        animacionTablero(posY9, rotacion9, deltaTime);
        break;
    case 10:
        animacionTablero(posY10, rotacion10, deltaTime);
        break;
    case 11:
        animacionTablero(posY11, rotacion11, deltaTime);
        break;
    case 12:
        animacionTablero(posY12, rotacion12, deltaTime);
        break;
    case 13:
        animacionTablero(posY13, rotacion13, deltaTime);
        break;
    case 14:
        animacionTablero(posY14, rotacion14, deltaTime);
        break;
    case 15:
        animacionTablero(posY15, rotacion15, deltaTime);
        break;
    case 16:
        animacionTablero(posY16, rotacion16, deltaTime);
        break;
    case 17:
        animacionTablero(posY17, rotacion17, deltaTime);
        break;
    case 18:
        animacionTablero(posY18, rotacion18, deltaTime);
        break;
    case 19:
        animacionTablero(posY19, rotacion19, deltaTime);
        break;
    case 20:
        animacionTablero(posY20, rotacion20, deltaTime);
        break;
    case 21:
        animacionTablero(posY21, rotacion21, deltaTime);
        break;
    case 22:
        animacionTablero(posY22, rotacion22, deltaTime);
        break;
    case 23:
        animacionTablero(posY23, rotacion23, deltaTime);
        break;
    case 24:
        animacionTablero(posY24, rotacion24, deltaTime);
        break;
    case 25:
        animacionTablero(posY25, rotacion25, deltaTime);
        break;
    case 26:
        animacionTablero(posY26, rotacion26, deltaTime);
        break;
    case 27:
        animacionTablero(posY27, rotacion27, deltaTime);
        break;
    case 28:
        animacionTablero(posY28, rotacion28, deltaTime);
        break;
    case 29:
        animacionTablero(posY29, rotacion29, deltaTime);
        break;
    case 30:
        animacionTablero(posY30, rotacion30, deltaTime);
        break;
    case 31:
        animacionTablero(posY31, rotacion31, deltaTime);
        break;
    case 32:
        animacionTablero(posY32, rotacion32, deltaTime);
        break;
    case 33:
        animacionTablero(posY33, rotacion33, deltaTime);
        break;
    case 34:
        animacionTablero(posY34, rotacion34, deltaTime);
        break;
    case 35:
        animacionTablero(posY35, rotacion35, deltaTime);
        break;
    case 36:
        animacionTablero(posY36, rotacion36, deltaTime);
        break;
    case 37:
        animacionTablero(posY37, rotacion37, deltaTime);
        break;
    case 38:
        animacionTablero(posY38, rotacion38, deltaTime);
        break;
    case 39:
        animacionTablero(posY39, rotacion39, deltaTime);
        break;
    case 40:
        animacionTablero(posY40, rotacion40, deltaTime);
        break;
    default:
        break;
    }
}*/

void Animaciones::controlAnimacionTablero(glm::vec3& posicion,
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
    float deltaTime,float Tiempo) {
    int idCasilla = obtenerIDCasilla(posicion);
    switch (idCasilla) {
    case 1:
        animacionTablero(posY1, rotacion1, deltaTime,Tiempo); //Casilla Guau contador
        break;
    case 2:
        animacionTablero(posY2, rotacion2, deltaTime, Tiempo); //Casilla Start
        break;
    case 3:
        animacionTablero(posY3, rotacion3, deltaTime, Tiempo); //Casilla Chapoteo
        break;
    case 4:
        animacionTablero(posY4, rotacion4, deltaTime, Tiempo); //Casilla Floripondio
        break;
    case 5:
        animacionTablero(posY5, rotacion5, deltaTime, Tiempo); // Casilla Brillantina
        break;
    case 6:
        animacionTablero(posY6, rotacion6, deltaTime, Tiempo); //Casilla Determindes
        break;
    case 7:
        animacionTablero(posY7, rotacion7, deltaTime, Tiempo); //Casilla Impacto
        break;
    case 8:
        animacionTablero(posY8, rotacion8, deltaTime, Tiempo);
        break;
    case 9:
        animacionTablero(posY9, rotacion9, deltaTime, Tiempo); //Casilla Esperanza 
        break;
    case 10:
        animacionTablero(posY10, rotacion10, deltaTime, Tiempo); //Casilla Yahoo 
        break;
    case 11:
        animacionTablero(posY11, rotacion11, deltaTime, Tiempo); //Mystery shack
        break;
    case 12:
        animacionTablero(posY12, rotacion12, deltaTime, Tiempo); //Casilla lento
        break;
    case 13:
        animacionTablero(posY13, rotacion13, deltaTime, Tiempo); //Casilla Castillo del terror
        break;
    case 14:
        animacionTablero(posY14, rotacion14, deltaTime, Tiempo); //Casilla Relajate
        break;
    case 15:
        animacionTablero(posY15, rotacion15, deltaTime, Tiempo); //Casilla Cuidado
        break;
    case 16:
        animacionTablero(posY16, rotacion16, deltaTime, Tiempo);
        break;
    case 17:
        animacionTablero(posY17, rotacion17, deltaTime, Tiempo);
        break;
    case 18:
        animacionTablero(posY18, rotacion18, deltaTime, Tiempo);
        break;
    case 19:
        animacionTablero(posY19, rotacion19, deltaTime, Tiempo);
        break;
    case 20:
        animacionTablero(posY20, rotacion20, deltaTime, Tiempo);
        break;
    case 21:
        animacionTablero(posY21, rotacion21, deltaTime, Tiempo);
        break;
    case 22:
        animacionTablero(posY22, rotacion22, deltaTime, Tiempo);
        break;
    case 23:
        animacionTablero(posY23, rotacion23, deltaTime, Tiempo);
        break;
    case 24:
        animacionTablero(posY24, rotacion24, deltaTime, Tiempo);
        break;
    case 25:
        animacionTablero(posY25, rotacion25, deltaTime, Tiempo);
        break;
    case 26:
        animacionTablero(posY26, rotacion26, deltaTime, Tiempo);
        break;
    case 27:
        animacionTablero(posY27, rotacion27, deltaTime, Tiempo);
        break;
    case 28:
        animacionTablero(posY28, rotacion28, deltaTime, Tiempo);
        break;
    case 29:
        animacionTablero(posY29, rotacion29, deltaTime, Tiempo);
        break;
    case 30:
        animacionTablero(posY30, rotacion30, deltaTime, Tiempo);
        break;
    case 31:
        animacionTablero(posY31, rotacion31, deltaTime, Tiempo);
        break;
    case 32:
        animacionTablero(posY32, rotacion32, deltaTime, Tiempo);
        break;
    case 33:
        animacionTablero(posY33, rotacion33, deltaTime, Tiempo);
        break;
    case 34:
        animacionTablero(posY34, rotacion34, deltaTime, Tiempo);
        break;
    case 35:
        animacionTablero(posY35, rotacion35, deltaTime, Tiempo);
        break;
    case 36:
        animacionTablero(posY36, rotacion36, deltaTime, Tiempo);
        break;
    case 37:
        animacionTablero(posY37, rotacion37, deltaTime, Tiempo);
        break;
    case 38:
        animacionTablero(posY38, rotacion38, deltaTime, Tiempo);
        break;
    case 39:
        animacionTablero(posY39, rotacion39, deltaTime, Tiempo);
        break;
    case 40:
        animacionTablero(posY40, rotacion40, deltaTime, Tiempo);
        break;
    default:
        break;
    }
}