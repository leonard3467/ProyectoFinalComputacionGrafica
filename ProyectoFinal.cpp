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
	obj5->CreateMesh(TableroVertices,TableroIndices, 32, 6);
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
	meshList.push_back(additionalFloor); // Este será `meshList[7]`

	Mesh* dado4 = new Mesh();
	dado4->CreateMesh(dado4_vertices, dado4_indices, 96, 12);
	meshList.push_back(dado4);    // Este será `meshList[8]`

	calcAverageNormals(indices, 12, vertices, 32, 8, 5);

	calcAverageNormals(vegetacionIndices, 12, vegetacionVertices, 64, 8, 5);

}


void CreateShaders()
{
	Shader* shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}
glm::vec3 position(-27.0f, 2.5f, -29.0f);

int main()
{
	mainWindow = Window(1366, 768); // 1280, 1024 or 1024, 768
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
	dado8Caras = Model();
	dado8Caras.LoadModel("Models/Dado8Caras.obj");
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
	//Declaración de primer luz puntual
	pointLights[0] = PointLight(1.0f, 1.0f, 1.0f,
		0.0f, 1.0f,
		6.0f, 1.5f, 0.0f,
		0.1f, 0.07f, 0.05f);
	pointLightCount++;

	unsigned int spotLightCount = 0;
	//linterna
	spotLights[0] = SpotLight(1.0f, 1.0f, 1.0f,
		0.0f, 2.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		5.0f);
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
	
	while (!mainWindow.getShouldClose())
	{
		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		Tiempo += now - lastTime;
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
		shaderList[0].SetSpotLights(spotLights, spotLightCount - 1);
		shaderList[0].SetPointLights(pointLights, pointLightCount - 1);



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


		glEnable(GL_BLEND);
		//------------*MODELO JERARQUICO DE BENDER-------------------*
		// --- TORZO
		model = glm::mat4(1.0);
		model = glm::translate(model, position);
		// Extraer la posición actual de la matriz de model
		animaciones.movimientoTablero(position, rotacionBender, saltoBenderY, desplazamientoBender, pasos, deltaTime, mainWindow,Tiempo, desplazamientoBenderz, rotacionBenderAux);
		model = glm::translate(model, glm::vec3(0.0f+desplazamientoBender, 0.0f, 0.0f+desplazamientoBenderz));
		model = glm::rotate(model, (rotacionBender + rotacionBenderAux-180) * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		

		//

		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}
