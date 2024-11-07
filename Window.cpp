#include "Window.h"

Window::Window()
{
	width = 800;
	height = 600;
	for (size_t i = 0; i < 1024; i++)
	{
		keys[i] = 0;
	}
}
Window::Window(GLint windowWidth, GLint windowHeight)
{
	width = windowWidth;
	height = windowHeight;
	muevex = 2.0f;
	Bandera = GL_TRUE;
	Avanza = false;
	rotx = 0;
	roty = 0;
	rotz = 0;



	for (size_t i = 0; i < 1024; i++)
	{
		keys[i] = 0;
	}
}
int Window::Initialise()
{
	//Inicialización de GLFW
	if (!glfwInit())
	{
		printf("Falló inicializar GLFW");
		glfwTerminate();
		return 1;
	}
	//Asignando variables de GLFW y propiedades de ventana
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//para solo usar el core profile de OpenGL y no tener retrocompatibilidad
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	//CREAR VENTANA
	mainWindow = glfwCreateWindow(width, height, "Ciudad Virtual con Tablero de Juego Interactivo", NULL, NULL);

	if (!mainWindow)
	{
		printf("Fallo en crearse la ventana con GLFW");
		glfwTerminate();
		return 1;
	}
	//Obtener tamaño de Buffer
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	//asignar el contexto
	glfwMakeContextCurrent(mainWindow);

	//MANEJAR TECLADO y MOUSE
	createCallbacks();


	//permitir nuevas extensiones
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		printf("Falló inicialización de GLEW");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	glEnable(GL_DEPTH_TEST); //HABILITAR BUFFER DE PROFUNDIDAD
							 // Asignar valores de la ventana y coordenadas
							 
							 //Asignar Viewport
	glViewport(0, 0, bufferWidth, bufferHeight);
	//Callback para detectar que se está usando la ventana
	glfwSetWindowUserPointer(mainWindow, this);
}

void Window::createCallbacks()
{
	glfwSetKeyCallback(mainWindow, ManejaTeclado);
	glfwSetCursorPosCallback(mainWindow, ManejaMouse);
}
GLfloat Window::getXChange()
{
	GLfloat theChange = xChange;
	xChange = 0.0f;
	return theChange;
}

GLfloat Window::getYChange()
{
	GLfloat theChange = yChange;
	yChange = 0.0f;
	return theChange;
}

GLboolean Window::getBandera()
{
	return Bandera;
}


void Window::update(float deltaTime)
{
	// Incrementa el temporizador
	tiempoLuces += deltaTime;

	// Verifica si han pasado 150 segundos
	if (tiempoLuces >= intervaloEncendido) {
		// Alterna el estado de Bandera para encender/apagar las luces
		if (Bandera == GL_FALSE) {
			printf("Faro prendido automáticamente\n");
			Bandera = GL_TRUE;
		}
		else {
			printf("Faro apagado automáticamente\n");
			Bandera = GL_FALSE;
		}

		// Reinicia el temporizador después de alcanzar el intervalo
		tiempoLuces = 0.0f;
	}
}

void Window::ManejaTeclado(GLFWwindow* window, int key, int code, int action, int mode)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	if (key == GLFW_KEY_Y)
	{
		theWindow->muevex += 1.0;
	}
	if (key == GLFW_KEY_U)
	{
		theWindow->muevex -= 1.0;
	}
	if (key == GLFW_KEY_F && action == GLFW_RELEASE) // para poder manejar la accion de que solo se puslo una ves la tecla queda asi uwu
	{
		if (theWindow->Bandera == GL_FALSE) {
			printf("Faro Prendido  \n");
			theWindow->Bandera = GL_TRUE;
		}
		else {
			printf("Faro apagado \n");
			theWindow->Bandera = GL_FALSE;
		}


	}

	if (key == GLFW_KEY_B ) // Detecta solo un pulso de la tecla Espacio
	{
		theWindow->rotx += 1;
		printf("rotacion X con angulo de %d \n", theWindow->rotx);
	}
	if (key == GLFW_KEY_N ) // Detecta solo un pulso de la tecla Espacio
	{
		theWindow->roty += 1;
		printf("rotacion Y con angulo de %d \n", theWindow->roty);
	}
	if (key == GLFW_KEY_M ) // Detecta solo un pulso de la tecla Espacio
	{
		theWindow->rotz += 1;
		printf("rotacion Z con angulo de %d \n", theWindow->rotz);
	}
	if (key == GLFW_KEY_H ) // Detecta solo un pulso de la tecla Espacio
	{
		theWindow->rotx -= 1;
		printf("rotacion X con angulo de %d \n", theWindow->rotx);
	}
	if (key == GLFW_KEY_J ) // Detecta solo un pulso de la tecla Espacio
	{
		theWindow->roty -= 1;
		printf("roty con angulo de %d \n", theWindow->roty);
	}
	if (key == GLFW_KEY_K ) // Detecta solo un pulso de la tecla Espacio
	{
		theWindow->rotz -= 1;
		printf("rotz con angulo de %d \n", theWindow->rotz);
	}
	if (key == GLFW_KEY_SPACE && action == GLFW_RELEASE) // Detecta solo un pulso de la tecla Espacio
	{
		theWindow->Avanza = !theWindow->Avanza;
		printf("¿Dado cae? %s \n", theWindow->Avanza ? "En efecto" : "Nel");

		printf("\nCantidadEsp =: %d \n", theWindow->CantidadEsp);
		// Cambia de turno en cada segunda pulsación
		if (theWindow->CantidadEsp == 0) {
			theWindow->CantidadEsp = 1; // Marca la primera pulsación
		}
		else {
			// Segunda pulsación: cambia el turno
			theWindow->turno += 1; // Incrementa el turno
			if (theWindow->turno > 2) { // Resetea el turno si excede 2
				theWindow->turno = 1;
			}
			theWindow->CantidadEsp = 0;
		}

		
		
		
	}


	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			theWindow->keys[key] = true;
			//printf("se presiono la tecla %d'\n", key);
		}
		else if (action == GLFW_RELEASE)
		{
			theWindow->keys[key] = false;
			//printf("se solto la tecla %d'\n", key);
		}
	}
}

void Window::ManejaMouse(GLFWwindow* window, double xPos, double yPos)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (theWindow->mouseFirstMoved)
	{
		theWindow->lastX = xPos;
		theWindow->lastY = yPos;
		theWindow->mouseFirstMoved = false;
	}

	theWindow->xChange = xPos - theWindow->lastX;
	theWindow->yChange = theWindow->lastY - yPos;

	theWindow->lastX = xPos;
	theWindow->lastY = yPos;
}


Window::~Window()
{
	glfwDestroyWindow(mainWindow);
	glfwTerminate();

}
