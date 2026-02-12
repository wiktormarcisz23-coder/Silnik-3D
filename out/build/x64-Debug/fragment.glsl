#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform sampler2D texture1;

uniform vec3 lightColor = vec3(1.0);
uniform vec3 ambientColor = vec3(0.2);
uniform float ambientStrength = 0.3;
uniform float specularStrength = 0.5;
uniform float shininess = 32.0;

void main()
{
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    vec3 viewDir = normalize(viewPos - FragPos);

    // Ambient
    vec3 ambient = ambientStrength * ambientColor;

    // Diffuse
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // Specular (Phong)
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    vec3 specular = specularStrength * spec * lightColor;

    // Ostateczny kolor
    vec3 result = (ambient + diffuse + specular) * texture(texture1, TexCoord).rgb;

    FragColor = vec4(result, 1.0);
}