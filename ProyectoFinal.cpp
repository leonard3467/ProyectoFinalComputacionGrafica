#define STB_IMAGE_IMPLEMENTATION
// regalas actuiales presionar espacio para tirar dados 
#include "Animaciones.h"
#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>
#include <math.h>
#include <glew.h>
#include <glfw3.h>
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
//Biblioteca para nuestro sonido
#include <irrKlang.h>
using namespace irrklang;
//para probar el importer
//#include<assimp/Importer.hpp>

#include "Window.h"
#include "Mesh.h"
#include "Shader_light.h"
#include "Camera.h"
#include "Texture.h"
#include "Sphere.h"
#include"Model.h"
#include "Skybox.h"

//para iluminación
#include "CommonValues.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Material.h"
const float toRadians = 3.14159265f / 180.0f;

//variables para animación
float movDado;
float movOffset;
float rotDadox;
float rotDadoxOffset;
float rotDadoy;
float rotDadoyOffset;
float rotDadoz;
float rotDadozOffset;
// dado 4 caras
float movDado4;
float mov4Offset;
float rotDado4x;
float rotDado4xOffset;
float rotDado4y;
float rotDado4yOffset;
float rotDado4z;
float rotDado4zOffset;

// textura compleja
float toffsetTablerou = 0.0f;
float toffsetTablerov = 0.0f;

float toffsetCasillau = 0.0f;
float toffsetCasillav = 0.0f;
// movimiento por el tablero bender 
float rotacionBender = 0.0f;        // Inicializar rotación de Bender
float rotacionBenderAux = 0.0f;
float saltoBenderY = 0.0f;          // Altura del salto en el eje Y
float desplazamientoBender = 0.0f;  // Desplazamiento inicial
float desplazamientoBenderz = 0.0f;
int pasos = 0;                      // Contador de pasos

//Movimiento tablero dipper
float rotacionDipper = 0.0f;        // Inicializar rotación de Bender
float rotacionDipperAux = 0.0f;
float saltoDipperY = 0.0f;          // Altura del salto en el eje Y
float desplazamientoDipper = 0.0f;  // Desplazamiento inicial
float desplazamientoDipperz = 0.0f;
//int pasosDipper=0;


Window mainWindow;
Animaciones animaciones; //intancia de control de animaciones 
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

Camera camera;


Texture TableroCentroTexture;
Texture pisoTexture;
Texture Casilla1;
Texture Casilla2;
Texture Casilla3;
Texture Lamp;
Texture dado_8_Caras;
Texture dado_4_Caras;


Model dado8Caras;
Model Banqueta;
Model poste_luz;
//--------------------Modelos Gravity Falls
Model bill;
Model cabra;
Model cerdo;
Model dipper;
Model soos;
Model flor_azul;
//Model gnomo;
//Model gnomo;
Model mabel;
Model stan;
Model wendy;
Model mystery_shack;
Model mansion;
Model bulldog;
Model arcade;
Model billNuevo;
//Dipper (Personaje principal)
Model cabezaDipper;
Model torsoDipper;
Model antebrazoDipper_der;
Model antebrazoDipper_izq;
Model brazoDipper_der;
Model brazoDipper_izq;
Model musloDipper_der;
Model musloDipper_izq;
Model piernaDipper_der;
Model piernaDipper_izq;

//------------------------------- Modelos Mario Bross
Model CastilloBow;
Model Carro1;
Model Carro2;
Model Cheep;
Model FlorFuego;
Model Fortaleza;
Model Goomba;
Model IceFlower;
Model Koopa;
Model Mario;
Model Monstruito;
Model PeachCastle;
Model Planta_Carnivora;
Model Toad;
Model Yoshi;
Model Oruga;

//AYUDA------
//Modelo de bicicleta
Model llantaTrasera;
Model llantaDelantera;
Model bicicleta;
// AHORA SI RECOMIENDO QUE USEN A BENDER JAJAJA
// 
//para bender:
Model BenderCabeza;
Model BenderTorzo;

Model BenderBrazoIzqInf;
Model BenderBrazoIzqSup;

Model BenderBrazoDerInf;
Model BenderBrazoDerSup;

Model BenderPiernaIzqInf;
Model BenderPiernaIzqSup;

Model BenderPiernaDerInf;
Model BenderPiernaDerSup;
//Dado


Skybox skybox;

//materiales
Material Material_brillante;
Material Material_opaco;


//Sphere cabeza = Sphere(0.5, 20, 20);
// aqqui pueden ir tambien algunas variables de animacione avanzada 

GLfloat deltaTime = 0.0f;
GLfloat Tiempo = 0.0f;
GLfloat lastTime = 0.0f;
static double limitFPS = 1.0 / 60.0;

// luz direccional
DirectionalLight mainLight;
//para declarar varias luces de tipo pointlight
PointLight pointLights[MAX_POINT_LIGHTS];
SpotLight spotLights[MAX_SPOT_LIGHTS];

// Vertex Shader
static const char* vShader = "shaders/shader_light.vert";

// Fragment Shader
static const char* fShader = "shaders/shader_light.frag";


//variables para keyframes
float reproduciranimacion, habilitaranimacion, guardoFrame, reinicioFrame, ciclo, ciclo2, contador = 0;

//función para teclado de keyframes 
void inputKeyframes(bool* keys);


//función de calculo de normales por promedio de vértices 
void calcAverageNormals(unsigned int* indices, unsigned int indiceCount, GLfloat* vertices, unsigned int verticeCount,
	unsigned int vLength, unsigned int normalOffset)
{
	for (size_t i = 0; i < indiceCount; i += 3)
	{
		unsigned int in0 = indices[i] * vLength;
		unsigned int in1 = indices[i + 1] * vLength;
		unsigned int in2 = indices[i + 2] * vLength;
		glm::vec3 v1(vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], vertices[in1 + 2] - vertices[in0 + 2]);
		glm::vec3 v2(vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0 + 2]);
		glm::vec3 normal = glm::cross(v1, v2);
		normal = glm::normalize(normal);

		in0 += normalOffset; in1 += normalOffset; in2 += normalOffset;
		vertices[in0] += normal.x; vertices[in0 + 1] += normal.y; vertices[in0 + 2] += normal.z;
		vertices[in1] += normal.x; vertices[in1 + 1] += normal.y; vertices[in1 + 2] += normal.z;
		vertices[in2] += normal.x; vertices[in2 + 1] += normal.y; vertices[in2 + 2] += normal.z;
	}

	for (size_t i = 0; i < verticeCount / vLength; i++)
	{
		unsigned int nOffset = i * vLength + normalOffset;
		glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
		vec = glm::normalize(vec);
		vertices[nOffset] = vec.x; vertices[nOffset + 1] = vec.y; vertices[nOffset + 2] = vec.z;
	}
}

// va ayudar 
void CreateObjects()
{
	unsigned int indices[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	GLfloat vertices[] = {
		//	x      y      z			u	  v			nx	  ny    nz
			-1.0f, -1.0f, -0.6f,	0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, -1.0f, 1.0f,		0.5f, 0.0f,		0.0f, 0.0f, 0.0f,
			1.0f, -1.0f, -0.6f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,		0.5f, 1.0f,		0.0f, 0.0f, 0.0f
	};

	unsigned int floorIndices[] = {
		0, 2, 1,
		1, 2, 3
	};

	GLfloat floorVertices[] = {
		// Posición              // Coordenadas de textura    // Normal
		-35.0f, 0.0f, -35.0f,    0.0f, 0.0f,                 0.0f, -1.0f, 0.0f,  // Vértice 0
		35.0f, 0.0f, -35.0f,     1.0f, 0.0f,                 0.0f, -1.0f, 0.0f,  // Vértice 1
		-35.0f, 0.0f, 35.0f,     0.0f, 1.0f,                 0.0f, -1.0f, 0.0f,  // Vértice 2
		35.0f, 0.0f, 35.0f,      1.0f, 1.0f,                 0.0f, -1.0f, 0.0f   // Vértice 3
	};

	unsigned int vegetacionIndices[] = {
	   0, 1, 2,
	   0, 2, 3,
	   4,5,6,
	   4,6,7
	};

	GLfloat vegetacionVertices[] = {
		// RECORDEMOS QUE HAYD DOS PLANSO DEBEMO DE MODIFICAR LAS VALORES DE SUS NORMALES 
		// SE AGREGAN NORMALES A DONDE MIRA EL DADO
		-0.5f, -0.5f, 0.0f,		0.0f, 0.0f,		0.0f, 0.0f, -1.03f,
		0.5f, -0.5f, 0.0f,		1.0f, 0.0f,		0.0f, 0.0f, -1.03f,
		0.5f, 0.5f, 0.0f,		1.0f, 1.0f,		0.0f, 0.0f, -1.0f,
		-0.5f, 0.5f, 0.0f,		0.0f, 1.0f,		0.0f, 0.0f, -1.0f,

		0.0f, -0.5f, -0.5f,		0.0f, 0.0f,		-1.0f, 0.0f, 0.0f,
		0.0f, -0.5f, 0.5f,		1.0f, 0.0f,		-1.0f, 0.0f, 0.0f,
		0.0f, 0.5f, 0.5f,		1.0f, 1.0f,		-1.0f, 0.0f, 0.0f,
		0.0f, 0.5f, -0.5f,		0.0f, 1.0f,		-1.0f, 0.0f, 0.0f,


	};
	unsigned int TableroIndices[] = {
		0, 2, 1,
		1, 2, 3
	};

	GLfloat TableroVertices[] = {
		// Posición              // Coordenadas de textura    // Normal
		-22.0f, 0.0f, -24.0f,    0.0f, 0.0f,                 0.0f, -1.0f, 0.0f,  // Vértice 0
		22.0f, 0.0f, -24.0f,     1.0f, 0.0f,                 0.0f, -1.0f, 0.0f,  // Vértice 1
		-22.0f, 0.0f, 24.0f,     0.0f, 1.0f,                 0.0f, -1.0f, 0.0f,  // Vértice 2
		22.0f, 0.0f, 24.0f,      1.0f, 1.0f,                 0.0f, -1.0f, 0.0f   // Vértice 3
	};
	unsigned int CasillasIndices[] = {
	   0, 1, 2,
	   0, 2, 3,
	};

	GLfloat CasillasVertices[] = {
		// definimos 3 columnas y vamos de 1 en uno para cada vertice
		// hayq ue considerar que para las orillas de las casillas 
		//la plantilla va de 2048x2048 
		// cada casilla es de 256 x 640
		//                       U     V 

		-1.0f, 0.0f,  1.0f,		 0.0f, 0.6875f,		0.0f, -1.0f, 0.0f,
		 1.0f, 0.0f,  1.0f,		.125f, 0.6875f,		0.0f, -1.0f, 0.0f,
		 1.0f, 0.0f, -1.0f,		.125f, 1.0f,		0.0f, -1.0f, 0.0f,
		-1.0f, 0.0f, -1.0f,		 0.0f, 1.0f,	    0.0f, -1.0f, 0.0f,

	};
	unsigned int Casillas2Indices[] = {
	   0, 1, 2,
	   0, 2, 3,
	};

	GLfloat Casillas2Vertices[] = {
		// definimos 3 columnas y vamos de 1 en uno para cada vertice
		// hayq ue considerar que para las orillas de las casillas 
		//la plantilla va de 2048x2048 
		// cada casilla es de 256 x 640
		//                       U     V 

		-5.5f, 0.0f,  5.5f,		 0.0f, 0.5f,		0.0f, -1.0f, 0.0f,
		 5.5f, 0.0f,  5.5f,		 0.5f, 0.5f,		0.0f, -1.0f, 0.0f,
		 5.5f, 0.0f, -5.5f,		 0.5f, 1.0f,		0.0f, -1.0f, 0.0f,
		-5.5f, 0.0f, -5.5f,		 0.0f, 1.0f,	    0.0f, -1.0f, 0.0f,

	};
	// **Nuevo Plano Adicional**
	unsigned int additionalFloorIndices[] = {
		0, 2, 1,
		1, 2, 3
	};

	GLfloat additionalFloorVertices[] = {
		// Posición             // Coordenadas de textura     // Normal
		-10.0f, 0.0f, -10.0f,   0.0f, 0.0f,                  0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, -10.0f,    10.0f, 0.0f,                  0.0f, -1.0f, 0.0f,
		-10.0f, 0.0f, 10.0f,    0.0f, 10.0f,                  0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, 10.0f,     10.0f, 10.0f,                  0.0f, -1.0f, 0.0f
	};
	unsigned int dado4_indices[] = {
		//Cada cara tiene 3 vértices
		0, 1, 2,    // Cara 1
		3, 4, 5,    // Cara 2
		6, 7, 8,    // Cara 3
		9, 10, 11     // Cara 4
	};

	GLfloat dado4_vertices[] = {
		// x       y       z             S       T          NX          NY       NZ
		// Cara 1
		-5.0f,   -5.0f,   -2.89f,     0.5117f, 0.8965f,		0.0f,      1.0f,      0.0f,
		5.0f,    -5.0f,   -2.89f,     0.2988f, 0.5215f,     0.0f,      1.0f,      0.0f,
		0.0f,    -5.0f,    5.77f,     0.7285f, 0.5215f,     0.0f,      1.0f,      0.0f,

		// Cara 2
		-5.0f,   -5.0f,   -2.89f,     0.9414f, 0.1484f,    0.848f,	  -0.262f,	 -0.49f,
		0.0f,    -5.0f,    5.77f,     0.7265f, 0.5253f,    0.848f,	  -0.262f,	 -0.49f,
		0.0f,     3.16f,   0.0f,      0.5136f, 0.1484f,    0.848f,	  -0.262f,	 -0.49f,

		// Cara 3
		-5.0f,   -5.0f,   -2.89f,     0.0839f, 0.1484f,    0.0f,	  -0.333f,   0.941f,
		0.0f,     3.16f,   0.0f,      0.5136f, 0.1484f,    0.0f,	  -0.333f,   0.941f,
		5.0f,    -5.0f,   -2.89f,     0.2988f, 0.5215f,    0.0f,	  -0.333f,   0.941f,

		// Cara 4
		0.0f,     3.16f,   0.0f,      0.5117f, 0.1484f,    -0.818f,	   -0.334f,	 -0.473f,
		0.0f,    -5.0f,    5.77f,     0.7265f, 0.5253f,    -0.818f,	   -0.334f,	 -0.473f,
		5.0f,    -5.0f,   -2.89f,     0.2988f, 0.5253f,    -0.818f,	   -0.334f,	 -0.473f,
	};


	Mesh* obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj1);

	Mesh* obj2 = new Mesh();
	obj2->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj2);

	Mesh* obj3 = new Mesh();
	obj3->CreateMesh(floorVertices, floorIndices, 32, 6);
	meshList.push_back(obj3);

	Mesh* obj4 = new Mesh();
	obj4->CreateMesh(vegetacionVertices, vegetacionIndices, 64, 12);
	meshList.push_back(obj4);

	Mesh* obj5 = new Mesh();
	obj5->CreateMesh(TableroVertices, TableroIndices, 32, 6);
	meshList.push_back(obj5);

	Mesh* obj6 = new Mesh();
	obj6->CreateMesh(CasillasVertices, CasillasIndices, 32, 6);
	meshList.push_back(obj6);

	Mesh* obj7 = new Mesh();
	obj7->CreateMesh(Casillas2Vertices, Casillas2Indices, 32, 6);
	meshList.push_back(obj7);

	// Agregar el nuevo plano a la lista de mallas
	Mesh* additionalFloor = new Mesh();
	additionalFloor->CreateMesh(additionalFloorVertices, additionalFloorIndices, 32, 6);
	meshList.push_back(additionalFloor); // Este será meshList[7]

	Mesh* dado4 = new Mesh();
	dado4->CreateMesh(dado4_vertices, dado4_indices, 96, 12);
	meshList.push_back(dado4);    // Este será meshList[8]

	calcAverageNormals(indices, 12, vertices, 32, 8, 5);

	calcAverageNormals(vegetacionIndices, 12, vegetacionVertices, 64, 8, 5);

}


void CreateShaders()
{
	Shader* shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}


//KEYFRAMES
bool animacion = false; //Reproducir animación



//NEW// Keyframes
float posXbill = -40.0, posYbill = 10.0, posZbill = 0.0;
float	movBill_x = 0.0f, movBill_y = 0.0f;
float giroBill = 0;

#define MAX_FRAMES 100  //Numero max de frames que podemos guardar
int i_max_steps = 90; //Interpolaciones
int i_curr_steps = 10; // A partir de que frame vamos a empezar a guardar
typedef struct _frame
{
	//Variables para GUARDAR Key Frames
	float movBill_x;		//Variable para PosicionX
	float movBill_y;		//Variable para PosicionY
	float movBill_xInc;		//Variable para IncrementoX
	float movBill_yInc;		//Variable para IncrementoY
	float giroBill;
	float giroBillInc;
}FRAME;

FRAME KeyFrame[MAX_FRAMES];
int FrameIndex = 10;			//introducir datos (igual a i_curr_steps)
bool play = false;
int playIndex = 0;

bool guardados = false; // Verifica si los primeros 7 keyframes ya fueron guardados

void guardarKeyframes()
{
	std::ofstream file("keyframes.txt");
	if (!file) {
		printf("Error al abrir el archivo\n");
		return;
	}

	file << "Primeros  Keyframes:\n";
	for (int i = 0; i < FrameIndex; i++) { // Guardamos los primeros 7
		file << "Keyframe [" << i << "]:\n";
		file << "movBill_x: " << KeyFrame[i].movBill_x << "\n";
		file << "movBill_y: " << KeyFrame[i].movBill_y << "\n";
		file << "giroBill: " << KeyFrame[i].giroBill << "\n";
		file << "------------------\n";
	}
	file.close();
	printf("Los primeros 7 Keyframes han sido guardados \n");

	guardados = true; // Marca como guardado
}
void saveKeyframe(int frameIndex)
{
	std::ofstream file("keyframes.txt", std::ios::app); 
	if (!file) {
		printf("Error al abrir el archivo \n");
		return;
	}

	file << "Keyframe [" << frameIndex << "]:\n";
	file << "movBill_x: " << KeyFrame[frameIndex].movBill_x << "\n";
	file << "movBill_y: " << KeyFrame[frameIndex].movBill_y << "\n";
	file << "giroBill: " << KeyFrame[frameIndex].giroBill << "\n";
	file << "------------------\n";
	file.close();

	printf("Keyframe [%d] guardado\n", frameIndex);
}

//Tecla L
void saveFrame(void) //tecla L
{

	printf("frameindex %d\n", FrameIndex);


	KeyFrame[FrameIndex].movBill_x = movBill_x;
	KeyFrame[FrameIndex].movBill_y = movBill_y;
	KeyFrame[FrameIndex].giroBill;//completar
	//no volatil, agregar una forma de escribir a un archivo para guardar los frames
	FrameIndex++;
}

void resetElements(void) //Tecla 0
{

	movBill_x = KeyFrame[0].movBill_x;
	movBill_y = KeyFrame[0].movBill_y;
	giroBill = KeyFrame[0].giroBill;
}

void interpolation(void)
{
	KeyFrame[playIndex].movBill_xInc = (KeyFrame[playIndex + 1].movBill_x - KeyFrame[playIndex].movBill_x) / i_max_steps;
	KeyFrame[playIndex].movBill_yInc = (KeyFrame[playIndex + 1].movBill_y - KeyFrame[playIndex].movBill_y) / i_max_steps;
	KeyFrame[playIndex].giroBillInc = (KeyFrame[playIndex + 1].giroBill - KeyFrame[playIndex].giroBill) / i_max_steps;

}


void animate(void)
{
	//Movimiento del objeto con barra espaciadora
	if (play)
	{
		if (i_curr_steps >= i_max_steps) //fin de animación entre frames?
		{
			playIndex++;
			printf("playindex : %d\n", playIndex);
			if (playIndex > FrameIndex - 2)	//Fin de toda la animación con último frame?
			{
				printf("Frame index= %d\n", FrameIndex);
				printf("termino la animacion\n");
				playIndex = 0;
				play = false;
			}
			else //Interpolación del próximo cuadro
			{

				i_curr_steps = 0; //Resetea contador
				//Interpolar
				interpolation();
			}
		}
		else
		{
			//Dibujar Animación
			movBill_x += KeyFrame[playIndex].movBill_xInc;
			movBill_y += KeyFrame[playIndex].movBill_yInc;
			giroBill += KeyFrame[playIndex].giroBillInc;
			i_curr_steps++;
		}

	}
}



//Posición inicial Bender
glm::vec3 position(-27.0f, 2.5f, -29.0f);
//Auxiliar posicion de Dipper
glm::vec3 positionDipper(-27.0f, 3.5f, -29.0f);
//Posicion del turno actual 
glm::vec3 TurnoActual(0.0f, 0.0f, 0.0f);

int main()
{
	//mainWindow = Window(1366, 768); // 1280, 1024 or 1024, 768
	Window mainWindow(1366, 768); // Declaración e inicialización
	mainWindow.Initialise();
	// nuestra camara incial sera la isometrica
	glm::vec3 posicionCamara = glm::vec3(-40.0f, 40.0f, 40.0f); // Posición en altura y diagonal
	glm::vec3 objetivo = glm::vec3(20.0f, 1.0f, 1.0f);          // Mira hacia el centro del tablero
	glm::vec3 upVector = glm::vec3(0.0f, 1.0f, 0.0f);          // Define "arriba" en el eje Y
	// Aplica 45 grados de rotación en el eje X y el eje Z
	float yaw = -45.0f;   // Rotación horizontal
	float pitch = -35.264f; // Rotación vertical (aproximación isométrica)
	camera = Camera(posicionCamara, upVector, yaw, pitch, 0.0f, 0.0f);
	glm::mat4 view = glm::lookAt(posicionCamara, objetivo, upVector);

	CreateObjects();
	CreateShaders();


	TableroCentroTexture = Texture("Textures/TableroCentro.tga");
	TableroCentroTexture.LoadTextureA();
	pisoTexture = Texture("Textures/pasto.tga");
	pisoTexture.LoadTextureA();
	Casilla1 = Texture("Textures/Casillas1.tga");
	Casilla1.LoadTextureA();
	Casilla2 = Texture("Textures/Casillas2.tga");
	Casilla2.LoadTextureA();
	Casilla3 = Texture("Textures/Casillas3.tga");
	Casilla3.LoadTextureA();
	dado_8_Caras = Texture("Textures/Dado8carasFinal.tga");
	dado_8_Caras.LoadTextureA();
	dado_4_Caras = Texture("Textures/Dado_4caras.tga");
	dado_4_Caras.LoadTextureA();

	Banqueta = Model();
	Banqueta.LoadModel("Models/Banqueta.obj");
	poste_luz = Model();
	poste_luz.LoadModel("Models/uploads_files_2971904_Street.Lighting.4.obj");
	dado8Caras = Model();
	dado8Caras.LoadModel("Models/Dado8Caras.obj");

	//---------------- Música
	// Crea el motor de sonido
	/*
	ISoundEngine* engine = createIrrKlangDevice();
	if (!engine) {
		std::cout << "Error al inicializar irrKlang" << std::endl;
		return 0;
	}
	// Configura el volumen global del sonido (entre 0.0 y 1.0)
	engine->setSoundVolume(0.8f); 
	// Reproduce un archivo de sonido
	engine->play2D("media/audio_principal.ogg", true);
	//Para hacer que nuestro sonido se repita en bucle y hasta que se cierre la ventana
	while (true) {

	}
	//Verificando que se reproduzca el audio
	if (engine->isCurrentlyPlaying("media/audio_principal.ogg")) {
		std::cout << "El audio está reproduciéndose correctamente" << std::endl;
	}
	else {
		std::cout << "El audio no está reproduciéndose" << std::endl;
	}
	// Libera recursos
	engine->drop();*/


	//----- BENDER-----
	BenderCabeza = Model();
	BenderCabeza.LoadModel("Models/Bender_Cabeza.obj");
	BenderTorzo = Model();
	BenderTorzo.LoadModel("Models/Bender_torzo.obj");
	//Brazo Der
	BenderBrazoDerInf = Model();
	BenderBrazoDerInf.LoadModel("Models/Bender_BrazoDerechoInf.obj");

	BenderBrazoDerSup = Model();
	BenderBrazoDerSup.LoadModel("Models/Bender_BrazoDerechoSup.obj");
	//Brazo Izq
	BenderBrazoIzqInf = Model();
	BenderBrazoIzqInf.LoadModel("Models/Bender_BrazoIzqInf.obj");

	BenderBrazoIzqSup = Model();
	BenderBrazoIzqSup.LoadModel("Models/Bender_BrazoIzqSup.obj");
	//Pierna Der
	BenderPiernaDerInf = Model();
	BenderPiernaDerInf.LoadModel("Models/Bender_PiernaDerechoInf.obj");

	BenderPiernaDerSup = Model();
	BenderPiernaDerSup.LoadModel("Models/Bender_PiernaDerechoSup.obj");
	//Pierna Izq
	BenderPiernaIzqInf = Model();
	BenderPiernaIzqInf.LoadModel("Models/Bender_PiernaIzqInf.obj");

	BenderPiernaIzqSup = Model();
	BenderPiernaIzqSup.LoadModel("Models/Bender_PiernaIzqSup.obj");
	//----------------------------------Modelos Gravity Falls
	bill = Model();
	bill.LoadModel("Models/bill.obj");
	cabra = Model();
	cabra.LoadModel("Models/cabra.obj");
	cerdo = Model();
	cerdo.LoadModel("Models/cerdo.obj");
	dipper = Model();
	dipper.LoadModel("Models/dipper.obj");
	soos = Model();
	soos.LoadModel("Models/soos.obj");
	flor_azul = Model();
	flor_azul.LoadModel("Models/flor_azul.obj");
	//gnomo = Model();
	//gnomo.LoadModel("Models/gnomo.obj");
	mabel = Model();
	mabel.LoadModel("Models/mabel.obj");
	stan = Model();
	stan.LoadModel("Models/stan.obj");
	wendy = Model();
	wendy.LoadModel("Models/wendy.obj");
	mystery_shack = Model();
	mystery_shack.LoadModel("Models/mystery_shack.obj");
	mansion = Model();
	mansion.LoadModel("Models/mansion.obj");
	bulldog = Model();
	bulldog.LoadModel("Models/bulldog.obj");
	arcade = Model();
	arcade.LoadModel("Models/arcade.obj");
	//Dipper
	cabezaDipper = Model();
	cabezaDipper.LoadModel("Models/cabezaDipper.obj");
	torsoDipper = Model();
	torsoDipper.LoadModel("Models/torsoDipper.obj");
	antebrazoDipper_der = Model();
	antebrazoDipper_der.LoadModel("Models/antebrazoDipper_der.obj");
	antebrazoDipper_izq = Model();
	antebrazoDipper_izq.LoadModel("Models/antebrazoDipper_izq.obj");
	brazoDipper_der = Model();
	brazoDipper_der.LoadModel("Models/brazoDipper_der.obj");
	brazoDipper_izq = Model();
	brazoDipper_izq.LoadModel("Models/brazoDipper_izq.obj");
	musloDipper_der = Model();
	musloDipper_der.LoadModel("Models/musloDipper_der.obj");
	musloDipper_izq = Model();
	musloDipper_izq.LoadModel("Models/musloDipper_izq.obj");
	piernaDipper_der = Model();
	piernaDipper_der.LoadModel("Models/piernaDipper_der.obj");
	piernaDipper_izq = Model();
	piernaDipper_izq.LoadModel("Models/piernaDipper_izq.obj");
	billNuevo = Model();
	billNuevo.LoadModel("Models/billNormal.obj");
	//-------------------------- Modelos Mario Bross
	CastilloBow = Model();
	CastilloBow.LoadModel("Models/CastilloBow.obj");
	Carro1 = Model();
	Carro1.LoadModel("Models/Carro1.obj");
	Carro2 = Model();
	Carro2.LoadModel("Models/Carro2.obj");
	Cheep = Model();
	Cheep.LoadModel("Models/Cheep.obj");
	FlorFuego = Model();
	FlorFuego.LoadModel("Models/FlorFuego.obj");
	Fortaleza = Model();
	Fortaleza.LoadModel("Models/Fortaleza.obj");
	Goomba = Model();
	Goomba.LoadModel("Models/Goomba.obj");
	IceFlower = Model();
	IceFlower.LoadModel("Models/IceFlower.obj");
	Koopa = Model();
	Koopa.LoadModel("Models/Koopa.obj");
	Mario = Model();
	Mario.LoadModel("Models/Mario.obj");
	Monstruito = Model();
	Monstruito.LoadModel("Models/Monstruito.obj");
	PeachCastle = Model();
	PeachCastle.LoadModel("Models/PeachCastle.obj");
	Planta_Carnivora = Model();
	Planta_Carnivora.LoadModel("Models/Planta_Carnivora.obj");
	Toad = Model();
	Toad.LoadModel("Models/Toad.obj");
	Yoshi = Model();
	Yoshi.LoadModel("Models/Yoshi.obj");
	Oruga = Model();
	Oruga.LoadModel("Models/Oruga.obj");

	//-----------------------------------------Bicicleta
	llantaTrasera = Model();
	llantaTrasera.LoadModel("Models/llanta_trasera.obj");
	llantaDelantera = Model();
	llantaDelantera.LoadModel("Models/llanta_delantera.obj");
	bicicleta = Model();
	bicicleta.LoadModel("Models/bicicleta.obj");

	std::vector<std::string> skyboxFaces;
	////Para el ciclo de noche
	skyboxFaces.push_back("Textures/Skybox/EspacioCicloNoche_Lf.tga");
	skyboxFaces.push_back("Textures/Skybox/EspacioCicloNoche_Rt.tga");
	skyboxFaces.push_back("Textures/Skybox/EspacioCicloNoche_Dn.tga");
	skyboxFaces.push_back("Textures/Skybox/EspacioCicloNoche_Up.tga");
	skyboxFaces.push_back("Textures/Skybox/EspacioCicloNoche_Bk.tga");
	skyboxFaces.push_back("Textures/Skybox/EspacioCicloNoche_Ft.tga");

	//Para el ciclo de dia 
	/*skyboxFaces.push_back("Textures/Skybox/SkyboxCicloDia_Lf.tga");
	skyboxFaces.push_back("Textures/Skybox/SkyboxCicloDia_Rt.tga");
	skyboxFaces.push_back("Textures/Skybox/SkyboxCicloDia_Dn.tga");
	skyboxFaces.push_back("Textures/Skybox/SkyboxCicloDia_Up.tga");
	skyboxFaces.push_back("Textures/Skybox/SkyboxCicloDia_Bk.tga");
	skyboxFaces.push_back("Textures/Skybox/SkyboxCicloDia_Ft.tga");*/

	skybox = Skybox(skyboxFaces);

	Material_brillante = Material(4.0f, 256);
	Material_opaco = Material(0.3f, 4);


	//luz direccional, sólo 1 y siempre debe de existir
	mainLight = DirectionalLight(1.0f, 1.0f, 1.0f,
		0.75f, 0.8f,
		0.0f, 0.0f, -1.0f);

	//contador de luces puntuales
	unsigned int pointLightCount = 0;
	//------Luces puntuales
	// Primera luz puntual 
	pointLights[0] = PointLight(1.0f, 0.0f, 1.0f, // Color de la luz
		3.0f, 1.5f,   // Intensidades de ambiente y difusa 
		35.5f, 8.5f, 38.0f,   // Posición de la luz
		0.3f, 0.05f, 0.02f); // Coeficientes de atenuación ajustados
	pointLightCount++;

	// Segunda luz puntual 
	pointLights[1] = PointLight(0.0f, 0.0f, 1.0f,  // Color de la luz
		3.0f, 1.5f,                               // Intensidades de ambiente y difusa 
		-35.5f, 8.5f, -38.0f,                        // Posición de la luz
		0.3f, 0.05f, 0.02f);                      // Coeficientes de atenuación ajustados
	pointLightCount++;


	unsigned int spotLightCount = 0;
	//Luz Spotlight
	spotLights[0] = SpotLight(0.0f, 1.0f, 0.0f,
		0.0f, 2.0f,
		-35.5f, 8.5f, 38.0f,
		0.0f, -1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		5.0f);
	spotLightCount++;
	// Segunda luz spotlight
	spotLights[1] = SpotLight(1.0f, 0.0f, 0.0f, // Color de la luz
		2.0f, 5.5f,                            // Intensidades de ambiente y difusa
		35.5f, 8.5f, -38.0f,                    // Posición de la luz
		0.0f, 1.0f, 0.0f,                     // Dirección de la luz
		1.0f, 0.1f, 0.0f,                      // Coeficientes de atenuación
		20.0f);                                // Ángulo del borde (mayor valor para un cono más abierto)
	spotLightCount++;
	// Tercera luz spotlight
	spotLights[2] = SpotLight(0.0f, 1.0f, 1.0f, // Color de la luz
		2.0f, 5.5f,                            // Intensidades de ambiente y difusa
		-35.5f, 8.5f, 38.0f,                    // Posición de la luz
		0.0f, 1.0f, 0.0f,                     // Dirección de la luz
		1.0f, 0.1f, 0.0f,                      // Coeficientes de atenuación
		20.0f);                                // Ángulo del borde (mayor valor para un cono más abierto)
	spotLightCount++;




	//se crean mas luces puntuales y spotlight 

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0, uniformTextureOffset = 0;
	GLuint uniformColor = 0;
	////----------------------------- CAMARA ISOMETRICA -------------------
	float aspectRatio = (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight();
	float viewSize = 50.0f; // Tamaño que permitirá ver todo el tablero	
	glm::mat4 projection = glm::ortho(-viewSize * aspectRatio, viewSize * aspectRatio, -viewSize, viewSize, 1.0f, 1500.0f);

	int lastModoCamara = camera.getModoCamara();


	toffsetTablerou = 0.0;
	toffsetTablerov = 0.0;
	// aqui se inicia todo
		//B----------------------AYUDA
	//float posicionZ = -25.0f;  // Posición inicial en el eje Z (Inicio en casilla Gravity Falls)
	float posicionX = -20.9104f;
	//float posicionY = 3.0f; //BICI
	float posicionZ = -28.0086f;
	float posicionY = 3.0f;
	float velocidad = 4.0f;    // Velocidad de avance en Z
	//float zObjetivo = 28.0f;   // Punto donde nos detenemos en z (BICI)
	float radioRueda = 0.5f;    // Radio de las ruedas
	float rotacionRueda = 0.0f; // Ángulo acumulado de rotación de las ruedas
	float rotacionY = 0.0f;    // Ángulo acumulado de rotación sobre el eje Y
	float velocidadRotacion = 45.0f;  // Velocidad de rotación en grados por segundo
	//float posicionX = -28.0f;  // Posición inicial en X (BICI)
	float xObjetivo = 28.0f;   // Punto donde nos detenemos en x
	float zObjetivoNegativo = -28.0f;  // Punto donde nos detenemos en -z
	float xObjetivoNegativo = -28.0f;  // Punto donde nos detenemos en -x
	//Todos los límites son con respecto a como mi modelo sigue dentro del tablero
	int estado = 0;  // Control de fases: 0: Avanzar en Z positivo, 1: Girar a X, 2: Avanzar en X, 3: Girar a Z negativo, 4: Avanzar en Z negativo, 5: Gira a X negativo, 6: Avanza en X negativo y 7: Gira a Z positivo

	float posYObjeto1 = -5.0f, posYObjeto2 = -5.0f, posYObjeto3 = -5.0f, posYObjeto4 = -5.0f, posYObjeto5 = -5.0f, posYObjeto6 = -5.0f, posYObjeto7 = -5.0f, posYObjeto8 = -5.0f, posYObjeto9 = -5.0f, posYObjeto10 = -5.0f, posYObjeto11 = -5.0f, posYObjeto12 = -5.0f, posYObjeto13 = -5.0f, posYObjeto14 = -5.0f, posYObjeto15 = -5.0f, posYObjeto16 = -5.0f, posYObjeto17 = -5.0f, posYObjeto18 = -5.0f, posYObjeto19 = -5.0f, posYObjeto20 = -5.0f, posYObjeto21 = -5.0f, posYObjeto22 = -5.0f, posYObjeto23 = -5.0f, posYObjeto24 = -5.0f, posYObjeto25 = -5.0f, posYObjeto26 = -5.0f, posYObjeto27 = -5.0f, posYObjeto28 = -5.0f, posYObjeto29 = -5.0f, posYObjeto30 = -5.0f, posYObjeto31 = -5.0f, posYObjeto32 = -5.0f, posYObjeto33 = -5.0f, posYObjeto34 = -5.0f, posYObjeto35 = -5.0f, posYObjeto36 = -5.0f, posYObjeto37 = -5.0f, posYObjeto38 = -5.0f, posYObjeto39 = -5.0f, posYObjeto40 = -5.0f;
	float rotacionObjeto1 = 0.0f, rotacionObjeto2 = 0.0f, rotacionObjeto3 = 0.0f, rotacionObjeto4 = 0.0f, rotacionObjeto5 = 0.0f, rotacionObjeto6 = 0.0f, rotacionObjeto7 = 0.0f, rotacionObjeto8 = 0.0f, rotacionObjeto9 = 0.0f, rotacionObjeto10 = 0.0f, rotacionObjeto11 = 0.0f, rotacionObjeto12 = 0.0f, rotacionObjeto13 = 0.0f, rotacionObjeto14 = 0.0f, rotacionObjeto15 = 0.0f, rotacionObjeto16 = 0.0f, rotacionObjeto17 = 0.0f, rotacionObjeto18 = 0.0f, rotacionObjeto19 = 0.0f, rotacionObjeto20 = 0.0f, rotacionObjeto21 = 0.0f, rotacionObjeto22 = 0.0f, rotacionObjeto23 = 0.0f, rotacionObjeto24 = 0.0f, rotacionObjeto25 = 0.0f, rotacionObjeto26 = 0.0f, rotacionObjeto27 = 0.0f, rotacionObjeto28 = 0.0f, rotacionObjeto29 = 0.0f, rotacionObjeto30 = 0.0f, rotacionObjeto31 = 0.0f, rotacionObjeto32 = 0.0f, rotacionObjeto33 = 0.0f, rotacionObjeto34 = 0.0f, rotacionObjeto35 = 0.0f, rotacionObjeto36 = 0.0f, rotacionObjeto37 = 0.0f, rotacionObjeto38 = 0.0f, rotacionObjeto39 = 0.0f, rotacionObjeto40 = 0.0f;


	glm::vec3 posBill = glm::vec3(-40.0f, 10.0f, 0.0f);
	//---------KeyFrames

	KeyFrame[0].movBill_x = 0.0f;
	KeyFrame[0].movBill_y = 0.0f;
	KeyFrame[0].giroBill = 0.0f;

	//Izquierda
	KeyFrame[1].movBill_x = -2.5f;
	KeyFrame[1].movBill_y = 2.5f;
	KeyFrame[1].giroBill = 360.0f;
	KeyFrame[2].movBill_x = -5.0f;
	KeyFrame[2].movBill_y = 5.0f;
	KeyFrame[2].giroBill = -360.0f;

	//Arriba
	KeyFrame[3].movBill_x =-2.5f;
	KeyFrame[3].movBill_y = 7.5f;
	KeyFrame[3].giroBill = 360.0f;
	KeyFrame[4].movBill_x = 0.0f;
	KeyFrame[4].movBill_y = 10.0f;
	KeyFrame[4].giroBill = -360.0f;

	//Derecha
	KeyFrame[5].movBill_x = 2.5f;
	KeyFrame[5].movBill_y = 7.5f;
	KeyFrame[5].giroBill = 360.0f;
	KeyFrame[6].movBill_x = 5.0f;
	KeyFrame[6].movBill_y = 5.0f;
	KeyFrame[6].giroBill = -360.0f;

	//Abajo
	KeyFrame[7].movBill_x = 2.5f;
	KeyFrame[7].movBill_y = 2.5f;
	KeyFrame[7].giroBill = 360.0f;
	KeyFrame[8].movBill_x = 0.0f;
	KeyFrame[8].movBill_y = 0.0f;
	KeyFrame[8].giroBill = -360.0f;


	printf("\nTeclas para uso de Keyframes:\n1.-Presionar Z para reproducir animacion.\n2.-Presionar 0 para volver a habilitar reproduccion de la animacion\n");
	//printf("3.-Presiona L para guardar frame\n4.-Presiona P para habilitar guardar nuevo frame\n5.-Presiona 1 para mover en X\n6.-Presiona 2 para habilitar mover en X");

	while (!mainWindow.getShouldClose())
	{
		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		Tiempo += now - lastTime;
		//printf("tiempo actual :  %f \n", Tiempo);
		deltaTime += (now - lastTime) / limitFPS;
		lastTime = now;
		animaciones.animacionDado8Caras(
			&rotDadox, &rotDadoy, &rotDadoz,
			&rotDadoxOffset, &rotDadoyOffset, &rotDadozOffset,
			&movDado, &movOffset,
			mainWindow, &deltaTime
		);
		animaciones.animacionDado4Caras(
			&rotDado4x, &rotDado4y, &rotDado4z,
			&rotDado4xOffset, &rotDado4yOffset, &rotDado4zOffset,
			&movDado4, &mov4Offset,
			mainWindow, &deltaTime
		);


		


		//Recibir eventos del usuario
		glfwPollEvents();
		camera.keyControl(mainWindow.getsKeys(), deltaTime);
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());
		// Control de camaras

		//-------Para Keyframes
		inputKeyframes(mainWindow.getsKeys());
		animate();

			// Configura la cámara y la proyección según el modo
			// Comprobar si el modo de cámara ha cambiado
		if (camera.getModoCamara() != lastModoCamara) {
			lastModoCamara = camera.getModoCamara();  // Actualizar el último modo

			if (camera.getModoCamara() == 1) {
				// Modo 1: Vista isométrica
				viewSize = 50.0f;
				projection = glm::ortho(-viewSize * aspectRatio, viewSize * aspectRatio, -viewSize, viewSize, 1.0f, 1500.0f);

				// Actualizar posición y orientación sin crear una nueva instancia
				camera.setPosition(glm::vec3(-40.0f, 40.0f, 40.0f));
				camera.setOrientation(-45.0f, -35.264f);  // Yaw y Pitch
				camera.setMovementSpeed(0.0f);
				camera.setTurnSpeed(0.0f);
			}
			else if (camera.getModoCamara() == 2) {
				// Modo 2: Vista aérea
				viewSize = 75.0f;
				projection = glm::ortho(-viewSize * aspectRatio, viewSize * aspectRatio, -viewSize, viewSize, 0.1f, 1000.0f);

				// Actualizar posición y orientación sin crear una nueva instancia
				camera.setPosition(glm::vec3(0.0f, 40.0f, 0.0f));
				camera.setOrientation(-90.0f, -90.0f);  // Yaw y Pitch
				camera.setMovementSpeed(0.5f);
				camera.setTurnSpeed(0.0f);  // Desactivar rotación de la cámara en modo aéreo
			}
			else if (camera.getModoCamara() == 3) {
				// Modo 3: Vista en perspectiva predeterminada
				projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 1000.0f);

				// Actualizar posición y orientación sin crear una nueva instancia
				camera.setPosition(glm::vec3(5.0f, 15.0f, -5.0f));
				camera.setOrientation(-60.0f, 0.0f);  // Yaw y Pitch
				camera.setMovementSpeed(0.3f);
				camera.setTurnSpeed(0.5f);
			}
		}

		// Clear the window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//glm::mat4 skyboxProjection = glm::perspective(90.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 3000.0f);
		skybox.DrawSkybox(camera.calculateViewMatrix(), projection);
		shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();
		uniformView = shaderList[0].GetViewLocation();
		uniformEyePosition = shaderList[0].GetEyePositionLocation();
		uniformColor = shaderList[0].getColorLocation();
		uniformTextureOffset = shaderList[0].getOffsetLocation();

		//información en el shader de intensidad especular y brillo
		uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
		uniformShininess = shaderList[0].GetShininessLocation();

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		glUniform3f(uniformEyePosition, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

		// luz ligada a la cámara de tipo flash
		//sirve para que en tiempo de ejecución (dentro del while) se cambien propiedades de la luz
		glm::vec3 lowerLight = camera.getCameraPosition();
		lowerLight.y -= 0.3f;
		spotLights[0].SetFlash(lowerLight, camera.getCameraDirection());

		//información al shader de fuentes de iluminación
		shaderList[0].SetDirectionalLight(&mainLight);
		//shaderList[0].SetSpotLights(spotLights, spotLightCount - 1);
		shaderList[0].SetSpotLights(spotLights, spotLightCount);
		shaderList[0].SetPointLights(pointLights, pointLightCount);


		// Actualiza el temporizador de luces en cada fotograma
		mainWindow.update(deltaTime);

		// Activación de luces basada en el estado de Bandera
		if (mainWindow.getBandera() == GL_TRUE) {
			shaderList[0].SetPointLights(pointLights, pointLightCount);
			shaderList[0].SetSpotLights(spotLights, spotLightCount);
		}
		else {
			shaderList[0].SetPointLights(pointLights, pointLightCount - 2);
			shaderList[0].SetSpotLights(spotLights, spotLightCount - 2);
		}



		glm::mat4 model(1.0);
		glm::mat4 modelaux(1.0);
		glm::mat4 modelaux2(1.0);
		glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);
		glm::vec2 toffset = glm::vec2(0.0f, 0.0f);

		////Tablero centro actual de 24 en x por 22 en z 

		//  Centro del tablero
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		TableroCentroTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[4]->RenderMesh();

		// Casillas
		// primero linea
		toffsetCasillau = 0.0;
		toffsetCasillav = 0.0;
		for (int i = 0; i < 8; i++)
		{
			toffset = glm::vec2(toffsetCasillau, toffsetCasillav);
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(-19.25f + (i * 5.5f), -1.0f, 29.5f));
			model = glm::scale(model, glm::vec3(2.75f, 1.0f, 5.5f));
			model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
			glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			color = glm::vec3(1.0f, 1.0f, 1.0f);
			glUniform3fv(uniformColor, 1, glm::value_ptr(color));
			Casilla1.UseTexture();
			Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
			meshList[5]->RenderMesh();
			toffsetCasillau += 0.125;
			toffsetCasillav = 0.0;

		}
		// Linea de abajo
		toffsetCasillau = 0.0;
		toffsetCasillav = -0.3125;
		for (int i = 0; i < 8; i++)
		{
			toffset = glm::vec2(toffsetCasillau, toffsetCasillav);
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(-19.25f + (i * 5.5f), -1.0f, -29.5f));
			model = glm::scale(model, glm::vec3(2.75f, 1.0f, 5.5f));
			model = glm::rotate(model, 360 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
			glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			color = glm::vec3(1.0f, 1.0f, 1.0f);
			glUniform3fv(uniformColor, 1, glm::value_ptr(color));
			Casilla1.UseTexture();
			Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
			meshList[5]->RenderMesh();
			toffsetCasillau += 0.125;
			toffsetCasillav = -0.3125;

		}
		toffsetCasillau = 0.0;
		toffsetCasillav = 0.0;
		for (int i = 0; i < 10; i++)
		{
			if (toffsetCasillau > 7 * 0.125) {
				toffsetCasillau = 0.0;
				toffsetCasillav = -0.3125;
			}
			toffset = glm::vec2(toffsetCasillau, toffsetCasillav);
			model = glm::mat4(1.0);
			model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
			model = glm::translate(model, glm::vec3(-21.6f + (i * 4.8f), -1.0f, -27.5f));
			model = glm::scale(model, glm::vec3(2.4f, 1.0f, 5.5f));

			glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			color = glm::vec3(1.0f, 1.0f, 1.0f);
			glUniform3fv(uniformColor, 1, glm::value_ptr(color));
			Casilla2.UseTexture();
			Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
			meshList[5]->RenderMesh();
			toffsetCasillau += 0.125;

		}
		toffsetCasillau = 2 * 0.125;
		toffsetCasillav = -0.3125;
		for (int i = 0; i < 10; i++)
		{
			if (toffsetCasillau > 7 * 0.125) {
				toffsetCasillau = 0.0;
				toffsetCasillav = 2 * -0.3125;
			}
			toffset = glm::vec2(toffsetCasillau, toffsetCasillav);
			model = glm::mat4(1.0);
			model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
			model = glm::translate(model, glm::vec3(-21.6f + (i * 4.8f), -1.0f, 27.5f));
			model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0, 0.0f));
			model = glm::scale(model, glm::vec3(2.4f, 1.0f, 5.5f));

			glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			color = glm::vec3(1.0f, 1.0f, 1.0f);
			glUniform3fv(uniformColor, 1, glm::value_ptr(color));
			Casilla2.UseTexture();
			Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
			meshList[5]->RenderMesh();
			toffsetCasillau += 0.125;

		}
		// esquinas de el tablero, con esto obtenemos las 40 casillas
		toffsetCasillau = 0.0;
		toffsetCasillav = 0.0;
		for (int i = 0; i < 4; i++)
		{
			if (toffsetCasillau > 0.5) {
				toffsetCasillau = 0.0;
				toffsetCasillav = -0.5;
			}
			toffset = glm::vec2(toffsetCasillau, toffsetCasillav);
			model = glm::mat4(1.0);
			if (i == 0) {
				model = glm::translate(model, glm::vec3(-27.5f, -1.0f, 29.5f));
				model = glm::rotate(model, -180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
			}
			else if (i == 1) {
				model = glm::translate(model, glm::vec3(27.5f, -1.0f, 29.5f));
				model = glm::rotate(model, -180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
			}
			else if (i == 2) {
				model = glm::translate(model, glm::vec3(27.5f, -1.0f, -29.5f));
			}
			else {
				model = glm::translate(model, glm::vec3(-27.5f, -1.0f, -29.5f));
			}
			glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			color = glm::vec3(1.0f, 1.0f, 1.0f);
			glUniform3fv(uniformColor, 1, glm::value_ptr(color));
			Casilla3.UseTexture();
			Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
			meshList[6]->RenderMesh();
			toffsetCasillau += 0.5;
		}

		toffset = glm::vec2(0.0, 0.0);
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		// Renderizado del plano adicional (Pasto)
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -1.01f, 0.0f));
		model = glm::scale(model, glm::vec3(20.0f, 1.0f, 20.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		pisoTexture.UseTexture();
		meshList[7]->RenderMesh();

		//Banqueta alrededor del tablero, junto con pista
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-36.3f, -1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(3.3f, 3.5f, 3.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Banqueta.RenderModel();

		//------------- Escenografía
		//Mystery Shack
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-140.0f, -0.5f, -60.0f));
		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		mystery_shack.RenderModel();
		//Castillo Bowser
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-140.0f, -0.5f, 40.0f));
		model = glm::scale(model, glm::vec3(30.0f, 30.0f, 30.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		CastilloBow.RenderModel();
		//Castillo Peach
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(110.0f, 20.5f, 0.0f));
		model = glm::scale(model, glm::vec3(1.5f, 2.5f, 2.5f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		PeachCastle.RenderModel();
		//Arcade
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-30.0f, 0.0f, -130.0f));
		model = glm::scale(model, glm::vec3(2.5f, 2.5f, 2.5f));
		//model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		arcade.RenderModel();
		//Mansion Noroeste
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(30.0f, 28.0f, 130.0f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		mansion.RenderModel();
		//Fortaleza en cada esquina
		//Primera esquina
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-160.0f, -1.0f, 160.0f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		model = glm::rotate(model, glm::radians(135.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Fortaleza.RenderModel();
		//Segunda esquina
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(160.0f, -1.0f, 160.0f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		model = glm::rotate(model, glm::radians(-135.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Fortaleza.RenderModel();
		//Tercera esquina
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(160.0f, -1.0f, -160.0f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		model = glm::rotate(model, glm::radians(-45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Fortaleza.RenderModel();
		//Cuarta esquina
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-160.0f, -1.0f, -160.0f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Fortaleza.RenderModel();


		//-------------Postes de luz
		//Poste casilla start
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-35.5f, 2.5f, -38.0f));
		model = glm::scale(model, glm::vec3(5.5f, 5.5f, 5.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		poste_luz.RenderModel();
		//Poste casilla Mystery shack
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(35.5f, 2.5f, -38.0f));
		model = glm::scale(model, glm::vec3(5.5f, 5.5f, 5.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		poste_luz.RenderModel();
		//Poste casilla 
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(35.5f, 2.5f, 38.0f));
		model = glm::scale(model, glm::vec3(5.5f, 5.5f, 5.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		poste_luz.RenderModel();
		//Poste casilla Insert Coin
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-35.5f, 2.5f, 38.0f));
		model = glm::scale(model, glm::vec3(5.5f, 5.5f, 5.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		poste_luz.RenderModel();

		//------ Dado 8 caras ---------
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 12.0f + movDado, 10.0f));
		model = glm::rotate(model, rotDadox * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, rotDadoy * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, rotDadoz * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(.7f, .7f, .7f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		dado8Caras.RenderModel();
		//------ Dado 4 caras ---------
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.5f, 14.0f + movDado4, -8.0f));
		model = glm::rotate(model, rotDado4x * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, rotDado4y * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, rotDado4z * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		color = glm::vec3(1.0f, 1.0f, 1.0f); // Asignar color blanco a la textura
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		dado_4_Caras.UseTexture();
		meshList[8]->RenderMesh();

		if (mainWindow.turno == 1) {
			TurnoActual = positionDipper;
		}
		else if (mainWindow.turno == 2) {
			TurnoActual = position;
		}

		glEnable(GL_BLEND);
		//------------*MODELO JERARQUICO DE BENDER-------------------*
		// --- TORZO
		model = glm::mat4(1.0);
		model = glm::translate(model, position);
		// Extraer la posición actual de la matriz de model
		animaciones.movimientoTableroBender(position, rotacionBender, saltoBenderY, desplazamientoBender, pasos, deltaTime, mainWindow, Tiempo, desplazamientoBenderz, rotacionBenderAux);
		model = glm::translate(model, glm::vec3(0.0f + desplazamientoBender, 0.0f, 0.0f + desplazamientoBenderz));
		model = glm::rotate(model, (rotacionBender + rotacionBenderAux - 180) * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		/*std::cout << "Posición actual del modelo: "
			<< "X: " << position.x << ", "
			<< "Y: " << position.y << ", "
			<< "Z: " << position.z << std::endl;*/
		modelaux = model;
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		BenderTorzo.RenderModel();


		// Imprimir la posición

		//-- Cabeza
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 2.7f, 0.0f));
		model = glm::rotate(model, mainWindow.rotx * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		BenderCabeza.RenderModel();
		//-- Brazo Derecho 
		model = modelaux;
		model = glm::translate(model, glm::vec3(.9f, 0.7f, 0.0f));
		model = glm::rotate(model, mainWindow.rotx * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		modelaux2 = model;
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		BenderBrazoDerSup.RenderModel();
		// Parte Inferior
		model = modelaux2;
		model = glm::translate(model, glm::vec3(.515f, -0.9f, 0.0f));
		//model = glm::rotate(model, mainWindow.rotx * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		BenderBrazoDerInf.RenderModel();
		// Brazo Izquierdo
		model = modelaux;
		model = glm::translate(model, glm::vec3(-.9f, 0.7f, 0.0f));
		model = glm::rotate(model, mainWindow.rotx * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		modelaux2 = model;
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		BenderBrazoIzqSup.RenderModel();
		// Parte Inferior
		model = modelaux2;
		model = glm::translate(model, glm::vec3(-.615f, -0.9f, 0.0f));
		//model = glm::rotate(model, mainWindow.rotx * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		BenderBrazoDerInf.RenderModel();
		// Pierna Derecha
		model = modelaux;
		model = glm::translate(model, glm::vec3(-.5f, -.9f, 0.0f));
		model = glm::rotate(model, mainWindow.rotx * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		modelaux2 = model;
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		BenderPiernaDerSup.RenderModel();
		// Parte Inferior
		model = modelaux2;
		model = glm::translate(model, glm::vec3(-0.04, -1.05f, 0.13f));
		//model = glm::rotate(model, mainWindow.rotx * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		BenderPiernaDerInf.RenderModel();
		// Pierna  Izquierdo
		model = modelaux;
		model = glm::translate(model, glm::vec3(.5f, -.9f, 0.0f));
		model = glm::rotate(model, mainWindow.rotx * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		modelaux2 = model;
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		BenderPiernaIzqSup.RenderModel();
		// Parte Inferior
		model = modelaux2;
		model = glm::translate(model, glm::vec3(0.12, -1.05f, 0.2f));
		//model = glm::rotate(model, mainWindow.rotx * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		BenderPiernaIzqInf.RenderModel();
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDisable(GL_BLEND);

		//------------*MODELO JERARQUICO DE DIPPER -------------------*
		// --- TORSO
		model = glm::mat4(1.0);
		model = glm::translate(model, positionDipper);
		//model = glm::translate(model, glm::vec3(-0.3f + desplazamientoBender, 0.5f, 0.0f + desplazamientoBenderz));
		animaciones.movimientoTableroDipper(positionDipper, rotacionDipper, saltoDipperY, desplazamientoDipper, pasos, deltaTime, mainWindow, Tiempo, desplazamientoDipperz, rotacionDipperAux);
		model = glm::translate(model, glm::vec3(0.0f + desplazamientoDipper, 0.0f, 0.0f + desplazamientoDipperz));
		model = glm::rotate(model, (rotacionDipper + rotacionDipperAux - 180) * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		/*std::cout << "Posición actual del modelo: "
			<< "X: " << position.x << ", "
			<< "Y: " << position.y << ", "
			<< "Z: " << position.z << std::endl;*/
		modelaux = model;
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		torsoDipper.RenderModel();


		// Imprimir la posición

		//-- Cabeza
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.05f, 0.48f, 0.13f));
		model = glm::rotate(model, mainWindow.rotx * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		cabezaDipper.RenderModel();
		//-- Brazo Derecho 
		model = modelaux;
		model = glm::translate(model, glm::vec3(-0.35f, 0.28f, 0.1f));
		model = glm::rotate(model, mainWindow.rotx * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		modelaux2 = model;
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		brazoDipper_der.RenderModel();
		// -- Antebrazo Derecho
		model = modelaux2;
		model = glm::translate(model, glm::vec3(-0.02f, -0.57f, 0.05f));
		//model = glm::rotate(model, mainWindow.rotx * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		antebrazoDipper_der.RenderModel();
		// Brazo Izquierdo
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.36f, 0.28f, 0.1f));
		model = glm::rotate(model, mainWindow.rotx * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		modelaux2 = model;
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		brazoDipper_izq.RenderModel();
		// Antebrazo izquierdo
		model = modelaux2;
		model = glm::translate(model, glm::vec3(0.01f, -0.59f, 0.02f));
		//model = glm::rotate(model, mainWindow.rotx * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		antebrazoDipper_izq.RenderModel();
		// Muslo Derecha
		model = modelaux;
		model = glm::translate(model, glm::vec3(-0.1f, -0.52f, 0.05f));
		model = glm::rotate(model, mainWindow.rotx * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		modelaux2 = model;
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		musloDipper_der.RenderModel();
		// Pierna Derecha
		model = modelaux2;
		model = glm::translate(model, glm::vec3(-0.027f, -0.3f, 0.031f));
		//model = glm::rotate(model, mainWindow.rotx * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		piernaDipper_der.RenderModel();
		// Muslo  Izquierdo contador
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.21f, -0.5f, 0.05f));
		model = glm::rotate(model, mainWindow.rotx * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		modelaux2 = model;
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		musloDipper_izq.RenderModel();
		// Pierna Izquierda
		model = modelaux2;
		model = glm::translate(model, glm::vec3(-0.022f, -0.32f, 0.07f));
		//model = glm::rotate(model, mainWindow.rotx * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		piernaDipper_izq.RenderModel();
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDisable(GL_BLEND);

		// Aqui inicia el sufrir unu
				//------------------------ OBJETOS TABLERO
		//Llamada a controlAnimacionTablero con las coordenadas de la bicicleta y todos los objetos de nuestro tablero (Ajustar traslacion y escala si es necesario para su objeto)

		//Llamada a función con posicion del personaje para activar animación de tablero
		animaciones.controlAnimacionTablero(TurnoActual, posYObjeto1, rotacionObjeto1, posYObjeto2, rotacionObjeto2, posYObjeto3, rotacionObjeto3, posYObjeto4, rotacionObjeto4, posYObjeto5, rotacionObjeto5, posYObjeto6, rotacionObjeto6, posYObjeto7, rotacionObjeto7, posYObjeto8, rotacionObjeto8, posYObjeto9, rotacionObjeto9, posYObjeto10, rotacionObjeto10, posYObjeto11, rotacionObjeto11, posYObjeto12, rotacionObjeto12, posYObjeto13, rotacionObjeto13, posYObjeto14, rotacionObjeto14, posYObjeto15, rotacionObjeto15, posYObjeto16, rotacionObjeto16, posYObjeto17, rotacionObjeto17, posYObjeto18, rotacionObjeto18, posYObjeto19, rotacionObjeto19, posYObjeto20, rotacionObjeto20, posYObjeto21, rotacionObjeto21, posYObjeto22, rotacionObjeto22, posYObjeto23, rotacionObjeto23, posYObjeto24, rotacionObjeto24, posYObjeto25, rotacionObjeto25, posYObjeto26, rotacionObjeto26, posYObjeto27, rotacionObjeto27, posYObjeto28, rotacionObjeto28, posYObjeto29, rotacionObjeto29, posYObjeto30, rotacionObjeto30, posYObjeto31, rotacionObjeto31, posYObjeto32, rotacionObjeto32, posYObjeto33, rotacionObjeto33, posYObjeto34, rotacionObjeto34, posYObjeto35, rotacionObjeto35, posYObjeto36, rotacionObjeto36, posYObjeto37, rotacionObjeto37, posYObjeto38, rotacionObjeto38, posYObjeto39, rotacionObjeto39, posYObjeto40, rotacionObjeto40, deltaTime, Tiempo);
		//Casilla Start
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-37.0f, posYObjeto2, -30.0f));
		//model = glm::translate(model, glm::vec3(-35.0f, posYObjeto1, 7.0f)); //Bill
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		model = glm::rotate(model, glm::radians(rotacionObjeto2), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		bill.RenderModel();
		//Reestablece
		model = glm::mat4(1.0);
		//Casilla Guau
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		//model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-37.0f, posYObjeto1, -22.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		model = glm::rotate(model, glm::radians(rotacionObjeto1), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		cabra.RenderModel();
		//Reestablece
		model = glm::mat4(1.0);
		//Casilla Sigue Avanzando
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		//model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-37.0f, posYObjeto40, -17.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		model = glm::rotate(model, glm::radians(rotacionObjeto40), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		Oruga.RenderModel();
		//Reestablece
		model = glm::mat4(1.0);
		//Casilla Espacio Naturaleza (4)
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		//model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-37.0f, posYObjeto39, -12.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		model = glm::rotate(model, glm::radians(rotacionObjeto39), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		dipper.RenderModel();
		//Reestablece
		model = glm::mat4(1.0);
		//Casilla Soos (5)
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		//model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-37.0f, posYObjeto38, -7.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		model = glm::rotate(model, glm::radians(rotacionObjeto38), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		soos.RenderModel();
		//Reestablece
		model = glm::mat4(1.0);
		//Casilla Gran Castillo (6)
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		//model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-37.0f, posYObjeto37, -2.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
		model = glm::rotate(model, glm::radians(rotacionObjeto37), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		PeachCastle.RenderModel();
		//Reestablece
		model = glm::mat4(1.0);
		//Casilla Elefanbria (7)
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		//model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-37.0f, posYObjeto36, 3.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::rotate(model, glm::radians(rotacionObjeto36), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		mabel.RenderModel();
		//Reestablece
		model = glm::mat4(1.0);
		//Casilla Nueva luz (8)
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-37.0f, posYObjeto35, 7.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		model = glm::rotate(model, glm::radians(rotacionObjeto35), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		bill.RenderModel();
		//Reestablece
		model = glm::mat4(1.0);
		//Casilla Kinopio (9)
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-37.0f, posYObjeto34, 12.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		model = glm::rotate(model, glm::radians(rotacionObjeto34), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		Toad.RenderModel();
		//Reestablece
		model = glm::mat4(1.0);
		//Casilla Oink (10)
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		//model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-37.0f, posYObjeto33, 17.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		model = glm::rotate(model, glm::radians(rotacionObjeto33), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		cerdo.RenderModel();
		//Reestablece
		model = glm::mat4(1.0);
		//Casilla Puerto diversion (11)
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		model = glm::translate(model, glm::vec3(-37.0f, posYObjeto32, 22.0f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		model = glm::rotate(model, glm::radians(rotacionObjeto32), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		wendy.RenderModel();
		//Reestablece
		model = glm::mat4(1.0);
		//Casilla Insert Coin (12)
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		model = glm::translate(model, glm::vec3(-37.0f, posYObjeto31, 30.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		model = glm::rotate(model, glm::radians(rotacionObjeto31), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		arcade.RenderModel();
		//Reestablece
		model = glm::mat4(1.0);
		//Casilla Mordelon (13)
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		//model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-19.5f, posYObjeto30, 38.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::rotate(model, glm::radians(rotacionObjeto30), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		mabel.RenderModel();
		//Reestablece
		model = glm::mat4(1.0);
		//Casilla Te tengo (14)
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		model = glm::translate(model, glm::vec3(-14.0f, posYObjeto29, 38.0f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		model = glm::rotate(model, glm::radians(rotacionObjeto29), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		FlorFuego.RenderModel();
		//Reestablece
		model = glm::mat4(1.0);
		//Casilla Destronador (15)
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		model = glm::translate(model, glm::vec3(-8.5f, posYObjeto28, 38.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		model = glm::rotate(model, glm::radians(rotacionObjeto28), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		Koopa.RenderModel();
		//Reestablece
		model = glm::mat4(1.0);
		//Casilla trebol de 7 (16)
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		model = glm::translate(model, glm::vec3(-3.0f, posYObjeto27, 38.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		model = glm::rotate(model, glm::radians(rotacionObjeto27), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		Koopa.RenderModel();
		//Reestablece
		model = glm::mat4(1.0);
		//Casilla Estafado (17)
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(2.5f, posYObjeto26, 38.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		model = glm::rotate(model, glm::radians(rotacionObjeto26), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		stan.RenderModel();
		//Reestablece
		model = glm::mat4(1.0);
		//Casilla Mazmorra (18)
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		//model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(8.0f, posYObjeto25, 38.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, glm::radians(rotacionObjeto25), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		Fortaleza.RenderModel();
		//Reestablece
		model = glm::mat4(1.0);
		//Casilla Devorado (19)
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		//model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(13.5f, posYObjeto24, 38.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		model = glm::rotate(model, glm::radians(rotacionObjeto24), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		cabra.RenderModel();
		//Reestablece
		model = glm::mat4(1.0);
		//Casilla Gnomo (20)
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		//model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(18.5f, posYObjeto23, 38.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		model = glm::rotate(model, glm::radians(rotacionObjeto23), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		cerdo.RenderModel();
		//Reestablece
		model = glm::mat4(1.0);
		//Casilla trbunal (esquina) (21)
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		model = glm::translate(model, glm::vec3(24.5f, posYObjeto22, 38.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		model = glm::rotate(model, glm::radians(rotacionObjeto22), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		soos.RenderModel();
		//Reestablece
		model = glm::mat4(1.0);
		//Casilla Saltarin (22)
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		//model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(36.5f, posYObjeto21, 21.5f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::rotate(model, glm::radians(rotacionObjeto21), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		Yoshi.RenderModel();
		//Reestablece
		model = glm::mat4(1.0);
		//Casilla Cabra (23)
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		//model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(36.5f, posYObjeto20, 16.5f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		model = glm::rotate(model, glm::radians(rotacionObjeto20), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		cabra.RenderModel();
		//Reestablece
		model = glm::mat4(1.0);
		//Casilla a comer (24)
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		model = glm::translate(model, glm::vec3(36.5f, posYObjeto19, 11.5f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		model = glm::rotate(model, glm::radians(rotacionObjeto19), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		Planta_Carnivora.RenderModel();
		//Reestablece
		model = glm::mat4(1.0);
		//Casilla Mr Langosta (25)
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		//model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(36.5f, posYObjeto18, 6.5f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		model = glm::rotate(model, glm::radians(rotacionObjeto18), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		dipper.RenderModel();
		//Reestablece
		model = glm::mat4(1.0);
		//Casilla Mansion Noroeste (26)
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		model = glm::translate(model, glm::vec3(36.5f, posYObjeto17, 1.5f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		model = glm::rotate(model, glm::radians(rotacionObjeto17), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		mansion.RenderModel();
		//Reestablece
		model = glm::mat4(1.0);
		//Casilla Furia(27)
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(36.5f, posYObjeto16, -4.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		model = glm::rotate(model, glm::radians(rotacionObjeto16), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		Goomba.RenderModel();
		//Reestablece
		model = glm::mat4(1.0);
		//Casilla Cuidado (28)
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		model = glm::translate(model, glm::vec3(36.5f, posYObjeto15, -7.5f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
		model = glm::rotate(model, glm::radians(rotacionObjeto15), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		flor_azul.RenderModel();
		//Reestablece
		model = glm::mat4(1.0);
		//Casilla Relajate (29)
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		model = glm::translate(model, glm::vec3(36.5f, posYObjeto14, -11.5f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		model = glm::rotate(model, glm::radians(rotacionObjeto14), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		wendy.RenderModel();
		//Reestablece
		model = glm::mat4(1.0);
		//Casilla Castillo del terror (30)
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		//model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(36.5f, posYObjeto13, -16.5f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		model = glm::rotate(model, glm::radians(rotacionObjeto13), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		CastilloBow.RenderModel();
		//Reestablece
		model = glm::mat4(1.0);
		//Casilla Lento (31)
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		//model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(36.5f, posYObjeto12, -21.5f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		model = glm::rotate(model, glm::radians(rotacionObjeto12), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		soos.RenderModel();
		//Reestablece
		model = glm::mat4(1.0);
		//Casilla Mystery Shack (32)
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		model = glm::translate(model, glm::vec3(36.5f, posYObjeto11, -28.5f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		model = glm::rotate(model, glm::radians(rotacionObjeto11), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		mystery_shack.RenderModel();
		//Reestablece
		model = glm::mat4(1.0);
		//Casilla Yahoo (33)
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(19.5f, posYObjeto10, -39.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		model = glm::rotate(model, glm::radians(rotacionObjeto10), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		Mario.RenderModel();
		//Reestablece
		model = glm::mat4(1.0);
		//Casilla Esperanza (34)
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		//model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(14.0f, posYObjeto9, -39.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
		model = glm::rotate(model, glm::radians(rotacionObjeto9), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		flor_azul.RenderModel();
		//Reestablece
		model = glm::mat4(1.0);
		//Casilla Bulldog (35)
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		//model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(8.f, posYObjeto8, -39.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		model = glm::rotate(model, glm::radians(rotacionObjeto8), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		bulldog.RenderModel();
		//Reestablece
		model = glm::mat4(1.0);
		//Casilla Impacto (36)
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		//model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(4.0f, posYObjeto7, -39.0f));
		model = glm::scale(model, glm::vec3(2.5f, 2.5f, 2.5f));
		model = glm::rotate(model, glm::radians(rotacionObjeto7), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		IceFlower.RenderModel();
		//Reestablece
		model = glm::mat4(1.0);
		//Casilla Determined (37)
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		model = glm::translate(model, glm::vec3(-1.0f, posYObjeto6, -39.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::rotate(model, glm::radians(rotacionObjeto6), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		FlorFuego.RenderModel();
		//Reestablece
		model = glm::mat4(1.0);
		//Casilla Brillantina (38)
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		model = glm::translate(model, glm::vec3(-8.0f, posYObjeto5, -39.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::rotate(model, glm::radians(rotacionObjeto5), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		mabel.RenderModel();
		//Reestablece
		model = glm::mat4(1.0);
		//Casilla Floripondio (39)
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		//model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-13.0f, posYObjeto4, -39.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
		model = glm::rotate(model, glm::radians(rotacionObjeto4), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		flor_azul.RenderModel();
		//Reestablece
		model = glm::mat4(1.0);
		//Casilla Chapoteo (40)
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		model = glm::translate(model, glm::vec3(-19.5f, posYObjeto3, -39.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		model = glm::rotate(model, glm::radians(rotacionObjeto3), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		Cheep.RenderModel();

		//--------------Keyframe de bill
		model = glm::mat4(1.0);
		posBill = glm::vec3(posXbill + movBill_x, posYbill + movBill_y, posZbill);
		model = glm::translate(model, posBill);
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		model = glm::rotate(model, giroBill * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		//model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		billNuevo.RenderModel();


		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}

void inputKeyframes(bool* keys)
{
	if (keys[GLFW_KEY_Z])
	{
		if (reproduciranimacion < 1)
		{
			if (play == false && (FrameIndex > 1))
			{
				resetElements();
				//First Interpolation				
				interpolation();
				play = true;
				playIndex = 0;
				i_curr_steps = 0;
				reproduciranimacion++;
				printf("\n presiona 0 para habilitar reproducir de nuevo la animación'\n");
				habilitaranimacion = 0;

			}
			else
			{
				play = false;

			}
		}
	}
	if (keys[GLFW_KEY_0])
	{
		if (habilitaranimacion < 1 && reproduciranimacion>0)
		{
			printf("Ya puedes reproducir de nuevo la animación con la tecla de barra espaciadora'\n");
			reproduciranimacion = 0;

		}
	}

	

}