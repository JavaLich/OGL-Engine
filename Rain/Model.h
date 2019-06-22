#include <gl\glew.h>
#include <GLFW\glfw3.h>
#ifndef MODEL_H
#define MODEL_H
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "stb_image.h"

#include <string>
#include <vector>
#include <iostream>

#include "Mesh.h"





class Model
{
public:
	Model(char* path);
	~Model();
	std::vector<Mesh> meshes;
	glm::vec3 length;
private:
	std::vector<Texture> loadedTextures;
	std::string directory;
	void loadModel(char* path);
	void loadModel(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
	void loadModel(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
	void processNode(aiNode *node, const aiScene *scene);
	Mesh processMesh(aiMesh *mesh, const aiScene* scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
	GLuint getTextureFromFile(const char* path, const std::string &directory, bool gamma = false);
	
	glm::vec3 min;
	glm::vec3 max;
};
#endif // !MODEL_H