#version 450 core

layout(triangles, equal_spacing, ccw) in;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

in vec2 texCoord0_es_in[];
in vec3 normal0_es_in[];
in vec3 fragPos_es_in[];

out vec2 texCoord0;
out vec3 normal0;
out vec3 fragPos;

vec2 interpolate2D(vec2 v0, vec2 v1, vec2 v2)
{
   	return vec2(gl_TessCoord.x) * v0 + vec2(gl_TessCoord.y) * v1 + vec2(gl_TessCoord.z) * v2;
}

vec3 interpolate3D(vec3 v0, vec3 v1, vec3 v2)
{
   	return vec3(gl_TessCoord.x) * v0 + vec3(gl_TessCoord.y) * v1 + vec3(gl_TessCoord.z) * v2;
}

void main(){
	texCoord0 = interpolate2D(texCoord0_es_in[0], texCoord0_es_in[1], texCoord0_es_in[2]);
	normal0 = interpolate3D(normal0_es_in[0], normal0_es_in[1], normal0_es_in[2]);
	normal0 = normalize(normal0);
	
	fragPos = interpolate3D(fragPos_es_in[0], fragPos_es_in[1], fragPos_es_in[2]);
	gl_Position = proj * view * model * vec4(fragPos, 1.0);
	fragPos = (model*vec4(fragPos, 1.0)).xyz;
}

