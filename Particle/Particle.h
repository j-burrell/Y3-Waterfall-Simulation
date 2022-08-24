#ifndef PARTICLE_CLASS_H
#define PARTICLE_CLASS_H
#include "../GL/glew.h"

class CShader;

class Particle
{
private:

	unsigned int m_vaoID;		    // vertex array object
	unsigned int m_vboID[3];		// two VBOs - used for colours, vertex and normals data
	GLuint ibo;                     // identifier for the triangle indices

	int numOfVerts;
	int numOfTris;

	float* verts;
	float* norms;
	unsigned int* tInds;

	float cx,cy,cz; //centre of the Particle
	float r;		//radius of the Particle

	float a;		//path varying coefficients
	float b;
	float c;
	float z;

public:
	Particle();

	void constructGeometry(CShader* myShader, int level);
	void render(CShader* shader, int lvl);

	void setRadius(float rad);
	void setStartPos(float x, float y, float z);
	void setVar(float a, float b, float c, float z);
	float calcY(float x);
	bool checkY();
	void fall();

};
#endif