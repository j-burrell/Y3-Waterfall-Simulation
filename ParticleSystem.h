#ifndef PARTICLE_SYSTEM_H
#define PARTICLE_SYSTEM_H

#include <iostream>
#include <vector>
#include <list>
#include"Particle/Particle.h"
using namespace std;

class CShader;

class ParticleSystem
{
private:

	vector<Particle> particles;
	int numParticles;
	int level;
	float variance;
	float sizeParticles;

	CShader* particleShader;

public:

	ParticleSystem(int numParticles, float variance, CShader* shader);
	void populate();
	void render();
	void spawn();
	void remove(int i);
	float generateRand(float variance);
	float generateRandZ(float variance);
	float genRandCoefficient(float variance);

};
#endif
