#version 450 core
layout (location = 0) in vec3 pos;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

uniform vec4 plane;

out vec2 texCoord0_cs_in;
out vec3 normal0_cs_in;
out vec3 fragPos_cs_in;

void main(){
	//gl_Position = model*vec4(pos, 1.0);
	texCoord0_cs_in = texCoord;
	normal0_cs_in =  mat3(model)*normal;
	fragPos_cs_in = pos;
	//gl_ClipDistance[0] = dot(vec4(fragPos_cs_in, 1.0), plane);
}