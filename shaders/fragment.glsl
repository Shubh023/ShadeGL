#version 330 core

out vec4 FragColor;

in vec3 current_position;

in vec3 current_normal;

in vec3 color;

in vec2 texuv;

uniform sampler2D diffuse0;

uniform sampler2D specular0;

uniform vec4 lightColor;

uniform vec3 lightPos;

uniform vec3 camPos;

uniform int lmode;

vec4 pointLight()
{
	vec3 lightVec = lightPos - current_position;
	float dist = length(lightVec);
	float a = 5.0;
	float b = 1.0;
	float intensity = 1.0f / (a * dist * dist + b * dist + 1.0f);
	float ambient = 0.25f;
	vec3 normal = normalize(current_normal);
	vec3 lightDirection = normalize(lightVec);
	float diffuse = max(dot(normal, lightDirection), 0.0f);
	float specularLight = 0.50f;
	vec3 viewDirection = normalize(camPos - current_position);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 256.0);
	float specular = specAmount * specularLight;
	return ((diffuse * intensity + ambient) * texture(diffuse0, texuv) + lightColor * texture(specular0, texuv).r * specular * intensity);
}

vec4 directionalLight()
{
	float ambient = 0.25f;
	vec3 normal = normalize(current_normal);
	vec3 lightDirection = normalize(vec3(1.0f, 1.0f, 0.0f));
	float diffuse = max(dot(normal, lightDirection), 0.0f);
	float specularLight = 0.55f;
	vec3 viewDirection = normalize(camPos - current_position);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 256.0);
	float specular = specAmount * specularLight;
	return ((diffuse + ambient) * texture(diffuse0, texuv) + lightColor * texture(specular0, texuv).r * specular);
}

vec4 spotLight()
{
	float outerCone = 0.90f;
	float innerCone = 0.95f;
	float ambient = 0.25f;
	vec3 normal = normalize(current_normal);
	vec3 lightDirection = normalize(lightPos - current_position);
	float diffuse = max(dot(normal, lightDirection), 0.0f);
	float specularLight = 0.55f;
	vec3 viewDirection = normalize(camPos - current_position);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 256.0);
	float specular = specAmount * specularLight;
	float angle = dot(vec3(0.0f, -1.0f, 0.0f), -lightDirection);
	float intensity = clamp((angle - outerCone) / (innerCone - outerCone), 0.0f, 1.0f);
	return  lightColor * ((diffuse * intensity + ambient) * texture(diffuse0, texuv) + specular * intensity * texture(specular0, texuv).r);
}


void main()
{
    // Change light mode
	if (lmode == 0)
		FragColor = pointLight();
	if (lmode == 1)
		FragColor = directionalLight();
	if (lmode == 2)
		FragColor = spotLight();
}