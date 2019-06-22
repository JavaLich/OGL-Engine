#version 450 core
layout(vertices = 3) out;

uniform vec3 cameraPos;
uniform mat4 model;

in vec2 texCoord0_cs_in[];
in vec3 normal0_cs_in[];
in vec3 fragPos_cs_in[];

out vec2 texCoord0_es_in[];
out vec3 normal0_es_in[];
out vec3 fragPos_es_in[];

float getTessLevel(float distance, float distance1){
	return 1.0;
}

void main(){
	texCoord0_es_in[gl_InvocationID] = texCoord0_cs_in[gl_InvocationID];
	normal0_es_in[gl_InvocationID] = normal0_cs_in[gl_InvocationID];
	fragPos_es_in[gl_InvocationID] = fragPos_cs_in[gl_InvocationID];
	
	vec3 p = (model * vec4(fragPos_es_in[gl_InvocationID], 1.0)).xyz;
	
	float eyeToVertexDistance0 = distance(cameraPos, p);
	float eyeToVertexDistance1 = distance(cameraPos, p);
	float eyeToVertexDistance2 = distance(cameraPos, p);
	
	gl_TessLevelOuter[0] = getTessLevel(eyeToVertexDistance1, eyeToVertexDistance2);
	gl_TessLevelOuter[1] = getTessLevel(eyeToVertexDistance2, eyeToVertexDistance0);
	gl_TessLevelOuter[2] = getTessLevel(eyeToVertexDistance0, eyeToVertexDistance1);
	gl_TessLevelInner[0] = gl_TessLevelOuter[2];
}


