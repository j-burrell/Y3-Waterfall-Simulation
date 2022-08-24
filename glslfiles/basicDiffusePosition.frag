// Fragment Shader

#version 430

out vec4 out_Color;            //colour for the pixel

uniform vec4 light_ambient;    //ambient light 
uniform vec4 light_diffuse;    //diffuse property for the light

uniform vec4 material_ambient; //ambient property for material
uniform vec4 material_diffuse; //diffuse property for the material

in vec3 ex_LightPos;  //light direction arriving from the vertex
in vec3 ex_Normal;  //normal arriving from the vertex
in vec3 ex_PositionEye;

void main(void)
{
	vec4 color = light_ambient * material_ambient;

	vec3 n, L;
	float NdotL;
	
	n = normalize(ex_Normal);
	L = normalize(ex_LightPos - ex_PositionEye);

	NdotL = max(dot(n, L),0.0);

	color += (light_diffuse * material_diffuse * NdotL);
	

	out_Color = color;
}