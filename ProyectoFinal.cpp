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

// textura compleja
float toffsetTablerou = 0.0f;
float toffsetTablerov = 0.0f;

float toffsetCasillau = 0.0f;
float toffsetCasillav = 0.0f;

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

Skybox skybox;

//materiales
Material Material_brillante;
Material Material_opaco;


//Sphere cabeza = Sphere(0.5, 20, 20);
// aqqui pueden ir tambien algunas variables de animacione avanzada 

GLfloat deltaTime = 0.0f;
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
		/*Cálculo de S y T
		S=posición pixel / # total pixel eje x
		T= 1- posición pixel / # total pixel eje y
		*/
		// Cara 1
		 0.0f,    0.2f,   -0.2f,     0.5117f, 0.8965f,      -0.0f,    -0.447f,     -0.894f,  // Vértice superior 
		-0.1f,    0.0f,   -0.1f,     0.2988f, 0.5215f,      -0.0f,    -0.447f,     -0.894f,  // Vértice izquierdo
		 0.1f,    0.0f,   -0.1f,     0.7285f, 0.5215f,      -0.0f,    -0.447f,     -0.894f,  // Vértice derecho
		 // Cara 2
		  0.0f,    0.2f,   -0.2f,     0.9414f, 0.1484f,    -0.894f,      -0.0f,    0.447f,  // Vértice superior 
		  0.1f,    0.0f,   -0.1f,     0.7265f, 0.5253f,    -0.894f,      -0.0f,    0.447f,  // Vértice izquierdo
		  0.0f,    0.0f,   -0.3f,     0.5136f, 0.1484f,    -0.894f,      -0.0f,    0.447f,  // Vértice derecho
		  // Cara 3
		   0.0f,    0.2f,   -0.2f,     0.0839f, 0.1484f,    0.873f,     -0.218f,   0.436f,  // Vértice superior 
		   0.0f,    0.0f,   -0.3f,     0.5136f, 0.1484f,    0.873f,     -0.218f,   0.436f,  // Vértice izquierdo
		  -0.1f,    0.0f,   -0.1f,     0.2988f, 0.5215f,    0.873f,     -0.218f,   0.436f,  // Vértice derecho
		  //Cara 4
		  0.0f,    0.0f,    -0.3f,    0.5117f, 0.1484f,       0.0f,       1.0f,      0.0f, // Vértice superior
		  -0.1f,    0.0f,    -0.1f,   0.7265f, 0.5253f,       0.0f,       1.0f,      0.0f, // Vértice izquierdo
		  0.1f,    0.0f,    -0.1f,    0.2988f, 0.5253f,       0.0f,       1.0f,      0.0f, // Vértice derecho
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


int main()
{
	mainWindow = Window(1366, 768); // 1280, 1024 or 1024, 768
	mainWindow.Initialise();

	CreateObjects();
	CreateShaders();


	camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 0.3f, 0.5f);

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

	std::vector<std::string> skyboxFaces;
	////Para el ciclo de noche
	//skyboxFaces.push_back("Textures/Skybox/EspacioCicloNoche_Lf.tga");
	//skyboxFaces.push_back("Textures/Skybox/EspacioCicloNoche_Rt.tga");
	//skyboxFaces.push_back("Textures/Skybox/EspacioCicloNoche_Dn.tga");
	//skyboxFaces.push_back("Textures/Skybox/EspacioCicloNoche_Up.tga");
	//skyboxFaces.push_back("Textures/Skybox/EspacioCicloNoche_Bk.tga");
	//skyboxFaces.push_back("Textures/Skybox/EspacioCicloNoche_Ft.tga");
	
	//Para el ciclo de dia 
	skyboxFaces.push_back("Textures/Skybox/SkyboxCicloDia_Lf.tga");
	skyboxFaces.push_back("Textures/Skybox/SkyboxCicloDia_Rt.tga");
	skyboxFaces.push_back("Textures/Skybox/SkyboxCicloDia_Dn.tga");
	skyboxFaces.push_back("Textures/Skybox/SkyboxCicloDia_Up.tga");
	skyboxFaces.push_back("Textures/Skybox/SkyboxCicloDia_Bk.tga");
	skyboxFaces.push_back("Textures/Skybox/SkyboxCicloDia_Ft.tga");

	skybox = Skybox(skyboxFaces);

	Material_brillante = Material(4.0f, 256);
	Material_opaco = Material(0.3f, 4);


	//luz direccional, sólo 1 y siempre debe de existir
	mainLight = DirectionalLight(1.0f, 1.0f, 1.0f,
		0.3f, 0.3f,
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
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 1000.0f);
	// aqui las variables que puedas poner de animacion se modifican ar asu ocrida incial 
	////Loop mientras no se cierra la ventana
	
	// si no mal recuerdo son de 1024 x 1024   dependera de cuantos recuadros aprovechemos pero vemos ahorita 
	toffsetTablerou = 0.0;
	toffsetTablerov = 0.0;
	
	while (!mainWindow.getShouldClose())
	{
		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		deltaTime += (now - lastTime) / limitFPS;
		lastTime = now;
		animaciones.animacionDado8Caras(
			&rotDadox, &rotDadoy, &rotDadoz,
			&rotDadoxOffset, &rotDadoyOffset, &rotDadozOffset,
			&movDado, &movOffset,
			mainWindow, &deltaTime
		);

		//Recibir eventos del usuario
		glfwPollEvents();
		camera.keyControl(mainWindow.getsKeys(), deltaTime);
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

		// Clear the window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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


		shaderList[0].SetSpotLights(spotLights, spotLightCount);
		//EN ESTOS MOMENTOS ESTA DESACTIVADA LA LUZ
		if (mainWindow.getBandera() == GL_TRUE) {
			shaderList[0].SetPointLights(pointLights, pointLightCount);
		}
		else if (mainWindow.getBandera() == GL_FALSE) {
			shaderList[0].SetPointLights(pointLights, pointLightCount - 1);
		}


		glm::mat4 model(1.0);
		glm::mat4 modelaux(1.0);
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
			model = glm::translate(model, glm::vec3(-19.25f+(i * 5.5f), -1.0f, 29.5f));
			model = glm::scale(model, glm::vec3(2.75f, 1.0f, 5.5f));
			model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
			glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			color = glm::vec3(1.0f, 1.0f, 1.0f);
			glUniform3fv(uniformColor, 1, glm::value_ptr(color));
			Casilla1.UseTexture();
			Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
			meshList[5]->RenderMesh();
			toffsetCasillau += 0.125;
			toffsetCasillav = 0.0;

		}
		// Linea de abajo
		toffsetCasillau = 0.0;
		toffsetCasillav =-0.3125;
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
			Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
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
			model = glm::translate(model, glm::vec3(-21.6f+ (i * 4.8f), -1.0f, -27.5f));
			model = glm::scale(model, glm::vec3(2.4f, 1.0f, 5.5f));

			glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			color = glm::vec3(1.0f, 1.0f, 1.0f);
			glUniform3fv(uniformColor, 1, glm::value_ptr(color));
			Casilla2.UseTexture();
			Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
			meshList[5]->RenderMesh();
			toffsetCasillau += 0.125;

		}
		toffsetCasillau = 2 * 0.125;
		toffsetCasillav = -0.3125;
		for (int i = 0; i < 10; i++)
		{
			if (toffsetCasillau > 7 * 0.125) {
				toffsetCasillau = 0.0;
				toffsetCasillav = 2*-0.3125;
			}
			toffset = glm::vec2(toffsetCasillau, toffsetCasillav);
			model = glm::mat4(1.0);
			model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
			model = glm::translate(model, glm::vec3(-21.6f + (i * 4.8f), -1.0f, 27.5f));
			model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
			model = glm::scale(model, glm::vec3(2.4f, 1.0f, 5.5f));

			glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			color = glm::vec3(1.0f, 1.0f, 1.0f);
			glUniform3fv(uniformColor, 1, glm::value_ptr(color));
			Casilla2.UseTexture();
			Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
			meshList[5]->RenderMesh();
			toffsetCasillau += 0.125;

		}
		// esquinas de el tablero, con esto obtenemos las 40 casillas
		toffsetCasillau = 0.0;
		toffsetCasillav = 0.0;
		for (int i = 0; i < 4; i++)
		{
			if (toffsetCasillau >  0.5) {
				toffsetCasillau = 0.0;
				toffsetCasillav = -0.5;
			}
			toffset = glm::vec2(toffsetCasillau, toffsetCasillav);
			model = glm::mat4(1.0);
			if (i==0) {
				model = glm::translate(model, glm::vec3(-27.5f, -1.0f, 29.5f));
				model = glm::rotate(model,-180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
			}
			else if (i == 1) {
				model = glm::translate(model, glm::vec3(27.5f, -1.0f, 29.5f));
				model = glm::rotate(model, -180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
			}
			else if (i == 2) {
				model = glm::translate(model, glm::vec3(27.5f, -1.0f, -29.5f));
			}else {
				model = glm::translate(model, glm::vec3(-27.5f, -1.0f, -29.5f));
			}
			glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			color = glm::vec3(1.0f, 1.0f, 1.0f);
			glUniform3fv(uniformColor, 1, glm::value_ptr(color));
			Casilla3.UseTexture();
			Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
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
		dado8Caras.RenderModel();
		//------ Dado 4 caras ---------
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 8.0f, 0.0f));
		model = glm::scale(model, glm::vec3(40.0f, 40.0f, 40.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		color = glm::vec3(1.0f, 1.0f, 1.0f); // Asignar color blanco a la textura
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		dado_4_Caras.UseTexture();
		meshList[8]->RenderMesh();

		glDisable(GL_BLEND);
		

		//

		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}
