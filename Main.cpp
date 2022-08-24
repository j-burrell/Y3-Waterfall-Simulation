
/*				James Burrell 100263300 3rd Year Project

						    OpenGL Waterfall	

				Press PageUp to cycle through camera angles.
*/

// --------------------------------------------------------------- Includes -----------------------------------------------------------------

#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\matrix_inverse.hpp"
#include "glm\gtc\type_ptr.hpp"
#include "gl/glew.h"
#include "gl/wglew.h"
#pragma comment(lib, "glew32.lib")
#include "GL\freeglut.h"
#include "shaders/Shader.h"   
#include "Particle/Particle.h"
#include "ParticleSystem.h"
#include <iostream>
using namespace std;

// ------------------------------------------------------------ Window Properties ------------------------------------------------------------

int screenWidth = 650, screenHeight = 650;
int screenPosX = 100, screenPosY = 100;
const char* winTitle = "OpenGL Waterfall";
bool SHOW_FPS = 0;

int view = 0;
float spin = 0.0f;
float radius = 65.0f;

// ------------------------------------------------------- OpenGL Function Definitions -------------------------------------------------------

void init();				
void reshape(int width, int height);
void display();	
void calculateFrameRate();

// ---------------------------------------------------------------- Matrices ------------------------------------------------------------------

glm::mat4 ProjectionMatrix; 
glm::mat4 ModelViewMatrix;
glm::mat4 ViewMatrix;
glm::mat3 NormalMatrix;

// ------------------------------------------------------- Light and Material Properties ------------------------------------------------------- 

CShader myShader;
float LightPos[3] = { 0.0f, 100.0f, 0.0f };
float Light_Ambient[4] = { 0.8f, 0.8f, 0.8f, 1.0f };
float Light_Diffuse[4] = { 0.9f, 0.9f, 0.9f, 1.0f };
float Light_Specular[4] = { 0.9f, 0.9f, 0.9f, 1.0f };

float Material_Ambient[4] = { 0.4f, 0.6f, 0.8f, 1.0f };
float Material_Diffuse[4] = { 0.6f, 0.6f, 0.6f, 1.0f };
float Material_Specular[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
float Material_Shininess = 100.0f;

// ---------------------------------------------------------------- Particle System ---------------------------------------------------------------------

int n = 250;
float variance = 1.0f;
ParticleSystem waterfall = ParticleSystem(n, variance, &myShader);

// ----------------------------------------------------------------------------------------------------------------------------------------------

/* Function for DEMO purposes only, not present in submitted source code.
 
   Cycles through camera angles when Page Up is pressed.
*/
void special(int key, int x, int y)
{
	switch (key) 
	{
	case GLUT_KEY_PAGE_UP:
		if (view == 0) {
			view = 1;
		}
		else if (view == 1) {
			view = 2;
		}
		else if (view == 2) {
			view = 3;
		}
		else if (view == 3) {
			view = 0;
		}
	}
}

// Creates shader, sends uniforms to shader and sets initial geometry of objects in scene.
void init()
{
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	if(!myShader.CreateShaderProgram("Basic Shader w/ Phong", "glslfiles/basicSpecular.vert", "glslfiles/basicSpecular.frag"))
	{
		cout << "failed to load shader" << endl;
	}							

	glUseProgram(myShader.GetProgramObjID());

	glUniform4fv(glGetUniformLocation(myShader.GetProgramObjID(), "LightPos"), 1, LightPos);
	glUniform4fv(glGetUniformLocation(myShader.GetProgramObjID(), "light_ambient"), 1, Light_Ambient);
	glUniform4fv(glGetUniformLocation(myShader.GetProgramObjID(), "light_diffuse"), 1, Light_Diffuse);
	glUniform4fv(glGetUniformLocation(myShader.GetProgramObjID(), "light_specular"), 1, Light_Specular);

	glUniform4fv(glGetUniformLocation(myShader.GetProgramObjID(), "material_ambient"), 1, Material_Ambient);
	glUniform4fv(glGetUniformLocation(myShader.GetProgramObjID(), "material_diffuse"), 1, Material_Diffuse);
	glUniform4fv(glGetUniformLocation(myShader.GetProgramObjID(), "material_specular"), 1, Material_Specular);
	glUniform1f(glGetUniformLocation(myShader.GetProgramObjID(), "material_shininess"), Material_Shininess);

	waterfall.populate();

	glEnable(GL_DEPTH_TEST);
}

// Sets the projection matrix and handles screensize change.
void reshape(int width, int height)
{
	screenWidth = width; 
	screenHeight = height;
	glViewport(0,0,width,height);

	ProjectionMatrix = glm::perspective(glm::radians(60.0f), (GLfloat)screenWidth/(GLfloat)screenHeight, 1.0f, 2000.0f);
	
}

// Send matrices to Shader and main render loop.
void display()									
{
	spin += 0.01;
	calculateFrameRate();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(myShader.GetProgramObjID());

	// Send projection, view, normal and modelview matrices to Shader
	glUniformMatrix4fv(glGetUniformLocation(myShader.GetProgramObjID(), "ProjectionMatrix"), 1, GL_FALSE, glm::value_ptr(ProjectionMatrix));
	
	// If -> else statements for DEMO purposes only, not present in submitted source code. (Changes ViewMatrix).
	if (view == 0)
	{
		//FrontView
		ViewMatrix = glm::rotate(glm::mat4(1.0), glm::radians(-90.0f), glm::vec3(0.0, 1.0, 0.0));
		ViewMatrix = glm::translate(ViewMatrix, glm::vec3(-65, 25, 0));
	}
	else if (view == 1)
	{
		//SideView 1
		ViewMatrix = glm::translate(glm::mat4(1.0), glm::vec3(0, 25, -65));
	}
	else if (view == 2)
	{
		//SideView 2
		ViewMatrix = glm::rotate(glm::mat4(1.0), glm::radians(-180.0f), glm::vec3(0.0, 1.0, 0.0));
		ViewMatrix = glm::translate(ViewMatrix, glm::vec3(0, 25, 65));
	}
	else
	{
		//RotatingView
		float camX = sin(spin) * radius;
		float camZ = cos(spin) * radius;
		ViewMatrix = glm::lookAt(glm::vec3(camX, -25.0, camZ), glm::vec3(0.0, -25.0, 0.0), glm::vec3(0.0f, 1.0f, 0.0f));
	}

	glUniformMatrix4fv(glGetUniformLocation(myShader.GetProgramObjID(), "ViewMatrix"), 1, GL_FALSE, glm::value_ptr(ViewMatrix));
	NormalMatrix = glm::inverseTranspose(glm::mat3(ModelViewMatrix));
	glUniformMatrix3fv(glGetUniformLocation(myShader.GetProgramObjID(), "NormalMatrix"), 1, GL_FALSE, glm::value_ptr(NormalMatrix));
	ModelViewMatrix = glm::translate(ViewMatrix,glm::vec3(0,0,0));
	glUniformMatrix4fv(glGetUniformLocation(myShader.GetProgramObjID(), "ModelViewMatrix"), 1, GL_FALSE, glm::value_ptr(ModelViewMatrix));
	
	// Object rendering
	waterfall.render();

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glUseProgram(0); 

	glutSwapBuffers();
	glutPostRedisplay();
}

/* Calculates and outputs the frame rate every second.

   The following three methods have been adapted from code found at:
   URL           -> https://stackoverflow.com/questions/5627803/how-to-calculate-fps-in-opengl
   User          -> Mzq
   Date Accessed -> 05/08/2022

*/
void calculateFrameRate()
{
	static float framesPerSecond = 0.0f;  // This will store our fps
	static float lastTime = 0.0f;         // This will hold the time from the last frame
	float currentTime = GetTickCount64() * 0.001f;
	++framesPerSecond;
	if (currentTime - lastTime > 10.0f) // Output every 5 seconds.
	{
		lastTime = currentTime;
		if (SHOW_FPS == 1) fprintf(stderr, "%d,", (int)(framesPerSecond/10));
		framesPerSecond = 0;
	}
}

// Main method that initalises window and specifies display and reshape functions.
int main(int argc, char **argv)
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(screenWidth, screenHeight);
	glutInitWindowPosition(screenPosX, screenPosY);
	glutCreateWindow(winTitle);
	glutReshapeFunc(reshape);

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		cout << " GLEW ERROR" << endl;
	}

	init();
	glutDisplayFunc(display);
	glutSpecialFunc(special);
	glutMainLoop();

	return 0;
}

