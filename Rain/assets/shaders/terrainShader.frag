#version 450 core

in vec2 texCoord0;
in vec3 normal0;
in vec3 fragPos;

out vec4 FragColor;

struct DirLight {
	vec3 direction;
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
uniform DirLight dirLight;

struct PointLight {    
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;  

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};  
#define NR_POINT_LIGHTS 4  
uniform PointLight pointLights[NR_POINT_LIGHTS];

struct Material{
	sampler2D texture_diffuse1;
	sampler2D texture_diffuse2;
};
uniform Material material;

uniform vec3 cameraPos;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir){
	vec3 lightDir = normalize(-light.direction);

    float diff = max(dot(normal, lightDir), 0.0);

    vec3 ambient  = light.ambient  * vec3(texture(material.texture_diffuse2, texCoord0));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.texture_diffuse2, texCoord0));
    return (ambient + diffuse);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);

    float diff = max(dot(normal, lightDir), 0.0);
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + 
  			     light.quadratic * (distance * distance));    

    vec3 ambient  = light.ambient  * vec3(texture(material.texture_diffuse2, texCoord0));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.texture_diffuse2, texCoord0));
 
    ambient  *= attenuation;
    diffuse  *= attenuation;

    return (ambient + diffuse);
} 

void main(){
	vec3 norm = normalize(normal0);
    vec3 viewDir = normalize(cameraPos - fragPos);

    vec3 result = CalcDirLight(dirLight, norm, viewDir);
	
    for(int i = 0; i < NR_POINT_LIGHTS; i++)
        result += CalcPointLight(pointLights[i], norm, fragPos, viewDir);    
 
	FragColor = vec4(result, 1.0);
}
