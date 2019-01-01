#version 450 core
in vec4 clipSpace;
in vec2 texCoord0;
in vec3 camPos;
in vec3 toCameraVector;
in vec3 fragPos;

out vec4 FragColor;

uniform sampler2D reflectionTexture;
uniform sampler2D refractionTexture;
uniform sampler2D dudvMap;
uniform sampler2D normalMap;
uniform sampler2D depthMap;

uniform vec3 lightColor;
uniform vec3 lightDir;

uniform float moveFactor;

uniform float near;
uniform float far;

float waveStrength = 0.05;
int shininess = 20;
float reflectivity = 0.6;

void main(){
	vec2 ndc = (clipSpace.xy/clipSpace.w)/2.0 + 0.5;
	vec2 refractTexCoords = ndc;
	vec2 reflectTexCoords = vec2(ndc.x, -ndc.y);
	
	float depth = texture(depthMap, refractTexCoords).r;
	float floorDistance = 2.0 * near * far / (far+near-(2.0*depth-1.0)*(far-near));
	
	depth = gl_FragCoord.z;
	float waterDistance = 2.0 * near * far / (far+near-(2.0*depth-1.0)*(far-near));;
	float waterDepth = floorDistance - waterDistance;
	
	
	vec2 dTexCoords = texture(dudvMap, vec2(texCoord0.x+moveFactor, texCoord0.y)).rg*0.1;
	dTexCoords = texCoord0 + vec2(dTexCoords.x, dTexCoords.y+moveFactor);
	vec2 totalDistortion = ((texture(dudvMap, dTexCoords).rg*2.0)-1.0)*waveStrength*clamp(waterDepth/20.0, 0.0, 1.0);
	
	refractTexCoords += totalDistortion;
	refractTexCoords = clamp(refractTexCoords, 0.001, 0.999);
	
	reflectTexCoords += totalDistortion;
	reflectTexCoords.x = clamp(reflectTexCoords.x, 0.001, 0.999);
	reflectTexCoords.y = clamp(reflectTexCoords.y, -0.999, -0.001);
	
	vec4 reflectColor = texture(reflectionTexture, reflectTexCoords);
	vec4 refractColor = texture(refractionTexture, refractTexCoords);
	
	vec4 normalMapColor = texture(normalMap, dTexCoords);
	vec3 normal = vec3((normalMapColor.r*2.0)-1.0, normalMapColor.b*3.0, (normalMapColor.g*2.0)-1.0);
	normal = normalize(normal);
	
	vec3 viewVec = normalize(toCameraVector);
	float fresnel = dot(viewVec, vec3(normal));
	fresnel = clamp(fresnel, 0.0, 1.0);
	
	vec3 lightDir0 = normalize(-lightDir);
	vec3 reflectDir = reflect(-lightDir0, normal);	
    float spec = pow(max(dot(normalize(camPos-fragPos), reflectDir), 0.0), shininess);
	vec3 specular = lightColor * spec * reflectivity*clamp(waterDepth/5.0, 0.0, 1.0);
	
	FragColor = mix(reflectColor, refractColor, fresnel);
	FragColor = mix(FragColor, vec4(0.0, 0.3, 0.5, 1.0), 0.2)+vec4(specular, 0.0);
	FragColor.a = clamp(waterDepth/5.0, 0.0, 1.0);
}
