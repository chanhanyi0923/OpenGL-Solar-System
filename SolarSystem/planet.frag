#version 330 core

in vec3 Position;  
in vec3 Normal;  
in vec2 TexCoord;

uniform int singleColor;  
uniform vec3 lightPos; 
uniform vec3 viewPos;
uniform vec3 lightColor;
uniform vec3 objectColor;
uniform sampler2D textureData;

void main()
{
    // Ambient
    float ambientStrength = 0.1f;
    vec3 ambient = ambientStrength * lightColor;

    // Diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - Position);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // Specular
    float specularStrength = 0.3f;
    vec3 viewDir = normalize(viewPos - Position);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;

    vec3 result;
    if (singleColor == 1) {
        result = (ambient + diffuse + specular) * objectColor;
    } else {
        result = (ambient + diffuse + specular) * vec3(texture(textureData, TexCoord));
    }

    gl_FragColor = vec4(result, 1.0f);
}
