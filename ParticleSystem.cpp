#include "ParticleSystem.h"
#include "shaders\Shader.h"
#include<cmath>
#include<iostream>
#include <random>
#include <time.h>
using namespace std;

// Seeding
default_random_engine eng{ static_cast<long unsigned int>(time(0)) };

ParticleSystem::ParticleSystem(int num, float var, CShader* shader)
{
	level = 5;
	sizeParticles = 0.5f;

	numParticles = num;
	variance = var;
	particleShader = shader;
}

// Fills particle system with particles.
void ParticleSystem::populate() 
{
	for (int i = 0; i < numParticles; i++) {

		float distribution = 15.0 * (numParticles * 0.01);

		float a = genRandCoefficient(variance);
		float b = generateRand(variance);
		float c = generateRand(variance);
		float z = generateRandZ(variance);

		Particle p;

		p.setVar(a, b, c, z);
		p.setStartPos//Set start point as random values.
		(-b-i/distribution,
			c, 
			z*(i/distribution)
		); 

		p.setRadius(sizeParticles);
		particles.push_back(p);

	}
}

//Spawns a particle at top of curve
void ParticleSystem::spawn() 
{
	float a = genRandCoefficient(variance);
	float b = generateRand(variance);
	float c = generateRand(variance);
	float z = generateRand(variance);

	Particle p;

	p.setVar(a, b, c, z);
	p.setStartPos(-b, c, z); //Set start point as random values.
	p.setRadius(sizeParticles);

	particles.push_back(p);
}

//Render all the particles in the vector
void ParticleSystem::render()
{

	for (int i = 0; i < particles.size(); i++) 
	{
		
		particles[i].fall();
		particles[i].render(particleShader, level);
		
		if (particles[i].checkY()) 
		{
			remove(i);
			spawn();
			
		}

	}
	//particles.shrink_to_fit();

}

//Remove the particle at index i and spawn one.
void ParticleSystem::remove(int i)
{
	//Removes particle at index 0 + i 
	particles.erase(particles.begin() + i);
}

/* Returns a random float between -variance and +variance. 

   The following three methods have been adapted from code found at:
   URL           -> https://stackoverflow.com/questions/686353/random-float-number-generation
   User          -> Andres DM
   Date Accessed -> 01/08/2022

*/
float ParticleSystem::generateRand(float variance)
{

	// Generate a float between -var and +var
	uniform_real_distribution<float> dis(-variance, variance); 
	
	return dis(eng);
}

// Returns a random float between -variance * spread and +variance * spread.
float ParticleSystem::generateRandZ(float variance)
{
	float spread = 1.0f;
	uniform_real_distribution<float> dis(-variance*spread, variance*spread);

	return dis(eng);
}

// Returns a random float between 1.5 and +variance.
float ParticleSystem::genRandCoefficient(float variance) 
{

	uniform_real_distribution<float> dis(1.5, variance);

	return dis(eng);
}

