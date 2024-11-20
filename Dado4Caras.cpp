//Textura dado 4 caras
Texture dadoTexture;

void CrearDado4Caras()
{
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
		 0.0f,    0.2f,   -0.2f,     0.5117f, 0.8965f,      0.0f,    0.447f,     0.894f,  // Vértice superior 
		-0.1f,    0.0f,   -0.1f,     0.2988f, 0.5215f,      0.0f,    0.447f,     0.894f,  // Vértice izquierdo
		 0.1f,    0.0f,   -0.1f,     0.7285f, 0.5215f,      0.0f,    0.447f,     0.894f,  // Vértice derecho
		// Cara 2
		 0.0f,    0.2f,   -0.2f,     0.9414f, 0.1484f,    0.894f,      0.0f,    -0.447f,  // Vértice superior 
		 0.1f,    0.0f,   -0.1f,     0.7265f, 0.5253f,    0.894f,      0.0f,    -0.447f,  // Vértice izquierdo
		 0.0f,    0.0f,   -0.3f,     0.5136f, 0.1484f,    0.894f,      0.0f,    -0.447f,  // Vértice derecho
		// Cara 3
		 0.0f,    0.2f,   -0.2f,     0.0839f, 0.1484f,   -0.873f,     0.218f,   -0.436f,  // Vértice superior 
		 0.0f,    0.0f,   -0.3f,     0.5136f, 0.1484f,   -0.873f,     0.218f,   -0.436f,  // Vértice izquierdo
		-0.1f,    0.0f,   -0.1f,     0.2988f, 0.5215f,   -0.873f,     0.218f,   -0.436f,  // Vértice derecho
		//Cara 4
		0.0f,    0.0f,    -0.3f,    0.5117f, 0.1484f,       0.0f,       1.0f,      0.0f, // Vértice superior
		-0.1f,    0.0f,    -0.1f,   0.7265f, 0.5253f,       0.0f,       1.0f,      0.0f, // Vértice izquierdo
		0.1f,    0.0f,    -0.1f,    0.2988f, 0.5253f,       0.0f,       1.0f,      0.0f, // Vértice derecho
	};

	Mesh* dado4 = new Mesh();
	dado4->CreateMesh(dado4_vertices, dado4_indices, 96, 12);
	meshList.push_back(dado4);
}

//Llamado de función en nuestro main
CrearDado4Caras();

//Texturizado de dado en nuestro main
dadoTexture = Texture("Textures/Dado_4caras.tga");
dadoTexture.LoadTextureA();

// Renderizado de dado dentro de nuestro while
model = glm::mat4(1.0);
//model = glm::translate(model, glm::vec3(0.0f, 5.0f, 0.0f));
glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
color = glm::vec3(1.0f, 1.0f, 1.0f); // Asignar color blanco a la textura
glEnable(GL_BLEND);
glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
dadoTexture.UseTexture(); 
meshList[6]->RenderMesh(); 
glDisable(GL_BLEND);