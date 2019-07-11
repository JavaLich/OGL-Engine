#version 450 core
layout (location = 0) in vec3 pos;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 normal;

uniform vec3 centerPos;
uniform float size;
uniform sampler2D starSpectrum;
uniform mat4 model;
uniform mat4 proj;
uniform mat4 view;

out vec2 texCoord0;
out vec3 fragPos;

void main(){
	//gl_Position = proj*view*model*vec4(pos, 1.0);
	texCoord0 = texCoord;
	vec3 cRight = vec3(view[0][0], view[1][0], view[2][0]);
	vec3 cUp = vec3(view[0][1], view[1][1], view[2][1]);
	fragPos = centerPos + cRight * pos.x + cUp * pos.y;
	gl_Position =  proj*view * vec4(centerPos + cRight * pos.x * size + cUp * pos.y * size, 1.0);
}