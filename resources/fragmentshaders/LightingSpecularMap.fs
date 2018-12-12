#version 330 core
out vec4 FragColor;

struct Material 
{
	vec3 ambient;
	vec3 diffuse;
	sampler2D diffuseMat;
	vec3 specular;
	sampler2D specularMat;
	float shininess;
};

struct PointLight
{
	vec3 position;
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	
	float constant;
	float linear;
	float quadratic;
	
};

struct DirectionalLight
{
	vec3 direction;
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

};

struct SpotLight
{
	vec3 position;
	vec3 direction;
	float cutoff;
	float outercutoff;
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	
	float constant;
	float linear;
	float quadratic;
};

vec3 CalculateDirectionalLight(DirectionalLight _light, vec3 _normal, vec3 _viewDir);
vec3 CalculatePointLight(PointLight _light, vec3 _normal, vec3 _fragPos, vec3 _viewDir);
vec3 CalculateSpotLight(SpotLight _light, vec3 _normal, vec3 _fragPos, vec3 _viewDir);

in vec2 TexCoord;
in vec3 FragPos;
in vec3 Normal;

uniform vec3 viewPos;
uniform Material material;

uniform DirectionalLight dirlight;

#define NR_POINT_LIGHTS 4
uniform PointLight pointlights[NR_POINT_LIGHTS];

#define NR_SPOT_LIGHTS 4
uniform SpotLight spotlights[NR_SPOT_LIGHTS];

void main()
{
	//processing information
	vec3 norm = normalize(Normal);
	vec3 viewDir = normalize(viewPos - FragPos);
	
	vec3 result = CalculateDirectionalLight(dirlight, norm, viewDir);
	
	for (int i = 0; i < NR_POINT_LIGHTS; i++)
	{
		result += CalculatePointLight(pointlights[i], norm, FragPos, viewDir);
	}
	
	for (int i = 0; i < NR_SPOT_LIGHTS; i++)
	{
		result += CalculateSpotLight(spotlights[i], norm, FragPos, viewDir);
	}
	
	FragColor = vec4(result, 1.0);
	
}

vec3 CalculateDirectionalLight(DirectionalLight _light, vec3 _normal, vec3 _viewDir)
{
	vec3 lightDir = normalize(-_light.direction);
	
	float diff = max(dot(_normal, lightDir), 0.0);
	
	vec3 reflectDir = reflect(-lightDir, _normal);
	float spec = pow(max(dot(_viewDir, reflectDir), 0.0), material.shininess);
	
	vec3 ambient = vec3(texture2D(material.diffuseMat, TexCoord).xyz * material.ambient.xyz) * _light.ambient;
	vec3 diffuse = vec3(texture2D(material.diffuseMat, TexCoord).xyz * material.diffuse.xyz) * diff * _light.diffuse;
	vec3 specular = vec3(texture2D(material.specularMat, TexCoord).xyz * material.specular.xyz) * spec * _light.specular;
	
	return (ambient + diffuse + specular);
}

vec3 CalculatePointLight(PointLight _light, vec3 _normal, vec3 _fragPos, vec3 _viewDir)
{
	vec3 lightDir = normalize(_light.position - _fragPos);
	float diff = max(dot(_normal, lightDir), 0.0);
	
	vec3 reflectDir = reflect(-lightDir, _normal);
	float spec = pow(max(dot(_viewDir, reflectDir), 0.0), material.shininess);
	
	float distance = length(_light.position - _fragPos);
	float attenuation = 1.0 / (_light.constant + _light.linear * distance + _light.quadratic * (distance * distance));
	
	vec3 ambient = vec3(texture2D(material.diffuseMat, TexCoord).xyz) * _light.ambient;
	vec3 diffuse = vec3(texture2D(material.diffuseMat, TexCoord).xyz) * diff * _light.diffuse;
	vec3 specular = vec3(texture2D(material.specularMat, TexCoord).xyz) * spec * _light.specular;
	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;
	
	return (ambient + diffuse + specular);
	
}

vec3 CalculateSpotLight(SpotLight _light, vec3 _normal, vec3 _fragPos, vec3 _viewDir)
{
	vec3 lightDir = normalize(_light.position - _fragPos);
	float diff = max(dot(_normal, lightDir), 0.0);
	
	vec3 reflectDir = reflect(-lightDir, _normal);
	float spec = pow(max(dot(_viewDir, reflectDir), 0.0), material.shininess);
	
	float distance = length(_light.position - _fragPos);
	float attenuation = 1.0 / (_light.constant + _light.linear * distance + _light.quadratic * (distance * distance));
	
	
	float theta = dot(lightDir, normalize(-_light.direction);
	float epsilon = _light.cutoff - _light.outercutoff;
	float intensity = clamp((theta - _light.outercutoff) / epsilon, 0.0, 1.0);
	
	vec3 ambient = vec3(texture2D(material.diffuseMat, TexCoord).xyz) * _light.ambient;
	vec3 diffuse = vec3(texture2D(material.diffuseMat, TexCoord).xyz) * diff * _light.diffuse;
	vec3 specular = vec3(texture2D(material.specularMat, TexCoord).xyz) * spec * _light.specular;
	
	if(intensity < 0.0)
	{
		ambient *= attenuation * intensity;
		diffuse *= attenuation * intensity;
		specular *= attenuation * intensity;
	}
	
	return (ambient + diffuse + specular);
}


