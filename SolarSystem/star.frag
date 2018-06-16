#version 330 core

in vec2 TexCoord;

uniform int singleColor;
uniform vec3 objectColor;
uniform sampler2D textureData;

void main()
{
    if (singleColor == 1) {
        gl_FragColor = vec4(objectColor, 1.0f);
    } else {
        gl_FragColor = texture(textureData, TexCoord);
    }
}
