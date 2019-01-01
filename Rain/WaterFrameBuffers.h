#pragma once
#include <gl\glew.h>
#include <GLFW\glfw3.h>
#include <glm.hpp>
class Game;
class WaterFrameBuffers
{
public:
	WaterFrameBuffers();
	~WaterFrameBuffers();

	void bindReflectionBuffer();
	void bindRefractionBuffer();
	void unbindCurrentFrameBuffer();
	GLuint getReflectionTexture();
	GLuint getRefractionTexture();
	GLuint getRefractionDepthTexture();

private:
	static const int REFLECTION_WIDTH = 200;
	static const int REFLECTION_HEIGHT = 150;
	static const int REFRACTION_WIDTH = 800;
	static const int REFRACTION_HEIGHT = 600;

	GLuint reflectionFrameBuffer;
	GLuint reflectionTexture;
	GLuint reflectionDepthBuffer;

	GLuint refractionFrameBuffer;
	GLuint refractionTexture;
	GLuint refractionDepthTexture;

	void initialiseReflectionFrameBuffer();
	void initialiseRefractionFrameBuffer();
	void bindFrameBuffer(GLuint fb, int width, int height);
	GLuint createFrameBuffer();
	GLuint createTextureAttachment(int width, int height);
	GLuint createDepthTextureAttachment(int width, int height);
	GLuint createDepthBufferAttachment(int width, int height);

};

