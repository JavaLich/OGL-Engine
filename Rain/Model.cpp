#include "Model.h"


Model::Model(char * path)
{
	meshes = std::vector<Mesh>();
	loadModel(path);
}

Model::~Model()
{
}

void Model::loadModel(char * path)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		std::cout << "Assimp error: " << importer.GetErrorString() << std::endl;
		return;
	}
	std::string pathString = path;
	directory = pathString.substr(0, pathString.find_last_of('/'));
	
	processNode(scene->mRootNode, scene);
	length = glm::vec3(max.x - min.x, max.y - min.y, max.z - min.z);
}

void Model::loadModel(std::vector<Vertex> vertices, std::vector<unsigned int> indices)
{
	min.x = vertices[0].position.x;
	min.y = vertices[0].position.y;
	min.z = vertices[0].position.z;
	max.x = vertices[0].position.x;
	max.y = vertices[0].position.y;
	max.z = vertices[0].position.z;
	for (Vertex vertex : vertices) {
		if (min.x > vertex.position.x)min.x = vertex.position.x;
		if (max.x < vertex.position.x)max.x = vertex.position.x;
		if (min.y > vertex.position.y)min.y = vertex.position.y;
		if (max.y < vertex.position.y)max.y = vertex.position.y;
		if (min.z > vertex.position.z)min.z = vertex.position.z;
		if (max.z < vertex.position.z)max.z = vertex.position.z;
	}
	meshes.push_back(Mesh(vertices, indices));
	length = glm::vec3(max.x - min.x, max.y - min.y, max.z - min.z);
}

void Model::processNode(aiNode * node, const aiScene * scene)
{
	min.x = scene->mMeshes[0]->mVertices[0].x;
	min.y = scene->mMeshes[0]->mVertices[0].y;
	min.z = scene->mMeshes[0]->mVertices[0].z;

	max.x = scene->mMeshes[0]->mVertices[0].x;
	max.y = scene->mMeshes[0]->mVertices[0].y;
	max.z = scene->mMeshes[0]->mVertices[0].z;
	for (unsigned int i = 0; i < node->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(processMesh(mesh, scene));
	}

	for (unsigned int i = 0; i < node->mNumChildren; i++) {
		processNode(node->mChildren[i], scene);
	}
}


Mesh Model::processMesh(aiMesh * mesh, const aiScene * scene)
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
		Vertex vertex;
		glm::vec3 vector;
		vector.x = mesh->mVertices[i].x;
		if (vector.x < min.x)min.x = vector.x;
		else if (vector.x > max.x)max.x = vector.x;
		vector.y = mesh->mVertices[i].y;
		if (vector.y < min.y)min.y = vector.y;
		else if (vector.y > max.y)max.y = vector.y;
		vector.z = mesh->mVertices[i].z;
		if (vector.z < min.z)min.z = vector.z;
		else if (vector.z > max.z)max.z = vector.z;
		vertex.position = vector;
		vector.x = mesh->mNormals[i].x;
		vector.y = mesh->mNormals[i].y;
		vector.z = mesh->mNormals[i].z;
		vertex.normal = vector;
		if (mesh->mTextureCoords[0]) {
			glm::vec2 vec;
			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			vertex.texCoord = vec;
		}
		else vertex.texCoord = glm::vec2(0.0f, 0.0f);
		vertices.push_back(vertex);
	}
	for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++) {
			indices.push_back(face.mIndices[j]);
		}
	}
	if (mesh->mMaterialIndex >= 0) {
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	}
	return Mesh(vertices, indices, textures);
}

std::vector<Texture> Model::loadMaterialTextures(aiMaterial * mat, aiTextureType type, std::string typeName)
{
	std::vector<Texture> textures;
	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
		aiString str;
		mat->GetTexture(type, i, &str);
		bool skip = false;
		for (unsigned int j = 0; j < loadedTextures.size(); j++) {
			if (std::strcmp(loadedTextures[j].path.data(), str.C_Str()) == 0) {
				textures.push_back(loadedTextures[j]);
				skip = true;
				break;
			}
		}
		if (!skip) {
			Texture texture;
			texture.id = getTextureFromFile((std::string(str.C_Str())).c_str(), directory);
			texture.type = typeName;
			texture.path = str.C_Str();
			textures.push_back(texture);
		}
	}
	return textures;
}

GLuint Model::getTextureFromFile(const char * path, const std::string & directory, bool gamma)
{
	std::string filename = std::string(path);
	filename = directory + '/' + filename;

	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}
