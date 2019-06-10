#version 330

in vec3 TexCoords;

out vec4 colour;

uniform samplerCube background;

void main()
{
	colour = texture(background, TexCoords);
}