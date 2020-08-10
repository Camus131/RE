#version 450 core

out vec4 FragColor;

in vec3 Pos;
in vec3 Normal;
in vec2 TexCoord;

struct Material
{
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

struct Light
{
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

uniform vec3 viewPos;
uniform Material material;
uniform Light light;

void main()
{
	vec3 normal = normalize(Normal);

	vec3 ambient = light.ambient * texture(material.diffuse, TexCoord).rgb;

	vec3 lightDir = normalize(light.position - Pos);
	float diff = max(dot(normal, lightDir), 0.0f);
	vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoord).rgb;

	vec3 viewDir = normalize(viewPos - Pos);
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
	vec3 specular = light.specular * spec * texture(material.specular, TexCoord).rgb;

	vec3 result = ambient + diffuse + specular;
	FragColor = vec4(result, 1.0);
}