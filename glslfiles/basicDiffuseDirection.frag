// Fragment Shader

#version 430

out vec4 out_Color;            //colour for the pixel

uniform vec4 light_ambient;    //ambient light 
uniform vec4 light_diffuse;    //diffuse property for the light

uniform vec4 material_ambient; //ambient property for material
uniform vec4 material_diffuse; //diffuse property for the material

in vec3 ex_LightDir;  //light direction arriving from the vertex
in  vec3 ex_Normal;  //normal arriving from the vertex

void main(void)
{
	vec4 color = light_ambient * material_ambient;

	vec3 n, L;
	float NdotL;
	
	n = normalize(ex_Normal);
	L = normalize(ex_LightDir);

	NdotL = max(dot(n, L),0.0);

	if(NdotL > 0.0)
	{
		color += (light_diffuse * material_diffuse * NdotL);
	}

	out_Color = color;
}