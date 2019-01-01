#version 450 core
layout (location = 0) in vec3 pos;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

uniform vec4 plane;

out vec2 texCoord0;
out vec3 normal0;
out vec3 fragPos;

void main(){
	gl_Position = proj*view*model*vec4(pos, 1.0);
	texCoord0 = texCoord*100.0;
	normal0 =  mat3(transpose(inverse(model))) * normal;
	fragPos = vec3(model*vec4(pos,1.0));
	gl_ClipDistance[0] = dot(vec4(fragPos, 1.0), plane);
}