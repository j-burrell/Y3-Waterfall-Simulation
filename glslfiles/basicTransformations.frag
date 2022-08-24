// Fragment Shader

#version 150

out vec4 out_Color; //colour for the pixel

in vec3 ex_Normal;  //normal arriving from the vertex shader

void main(void)
{
	//render all pixels blue.
	out_Color = vec4(0.0,0.0,1.0,1.0);
}