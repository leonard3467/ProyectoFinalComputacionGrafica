#pragma once
#include<stdio.h>
#include<glew.h>
#include<glfw3.h>

class Window
{
public:
	Window();
	Window(GLint windowWidth, GLint windowHeight);
	int Initialise();
	GLfloat getBufferWidth() { return bufferWidth; }
	GLfloat getBufferHeight() { return bufferHeight; }
	GLfloat getXChange();
	GLfloat getYChange();
	GLboolean getBandera();
	GLfloat getmuevex() { return muevex; }
	GLint rotx, roty, rotz;
	GLint turno = 1;
	GLint CantidadEsp = 0;
	bool getShouldClose() {
		return  glfwWindowShouldClose(mainWindow);}
	bool* getsKeys() { return keys; }
	void swapBuffers() { return glfwSwapBuffers(mainWindow); }
	bool getAvanza() { return Avanza; }

	// Declaraci�n de la funci�n updateTimer
	void update(float deltaTime);
	
	~Window();
private: 
	GLFWwindow *mainWindow;
	GLint width, height;
	bool keys[1024];
	GLint bufferWidth, bufferHeight;
	void createCallbacks();
	GLfloat lastX;
	GLfloat lastY;
	GLfloat xChange;
	GLfloat yChange;
	GLfloat muevex;
	
	// Variables para el temporizador de luces
	float tiempoLuces = 0.0f;
	const float intervaloEncendido = 150.0f; // Intervalo de 150 segundos
	
	GLboolean Bandera;
	bool mouseFirstMoved, Avanza;
	static void ManejaTeclado(GLFWwindow* window, int key, int code, int action, int mode);
	static void ManejaMouse(GLFWwindow* window, double xPos, double yPos);

};

