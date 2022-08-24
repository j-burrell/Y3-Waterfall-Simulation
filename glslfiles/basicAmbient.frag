// Fragment Shader

#version 430

out vec4 out_Color;            //colour for the pixel

uniform vec4 light_ambient;    //ambient light 
uniform vec4 material_ambient; //ambient property for material

void main(void)
{
	out_Color = light_ambient * material_ambient;
}