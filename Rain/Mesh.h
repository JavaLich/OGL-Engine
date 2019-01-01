#pragma once
#include <gl\glew.h>
#include <GLFW\glfw3.h>
#include <glm.hpp>
#ifndef MESH_H
#define MESH_H


#include "Shader.h"

#include <string>
#include <vector>

struct Vertex {
	glm::vec3 position;
	glm::vec2 texCoord;
	glm::vec3 normal;
};

struct Texture {
	unsigned int id;
	std::string type;
	std::string path;
};

class Mesh
{
public:
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
	Mesh();
	~Mesh();
	void setupRender(Shader shader);

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	unsigned int vao, vbo, ibo;

private:
	void setupMesh();

};

#endif // !MESH_H