#version 450 core
layout (location = 0) in vec3 pos;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

uniform vec3 cameraPos;
uniform vec3 lightPos;

out vec4 clipSpace;
out vec2 texCoord0;
out vec3 camPos;
out vec3 toCameraVector;
out vec3 fragPos;
out vec3 fromLightVector;

const float tiling = .05;
void main(){
	vec4 worldPos = model*vec4(pos, 1.0);
	clipSpace = proj*view*worldPos;
	gl_Position = clipSpace;
	texCoord0 = vec2(pos.x/2.0+0.5, pos.z/2.0+0.5)*tiling;
	camPos=cameraPos;
	toCameraVector = cameraPos.xyz-worldPos.xyz;
	fragPos = worldPos.xyz;
}