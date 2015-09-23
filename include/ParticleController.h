#pragma once

#include <list>
#include "Particle.h"

class ParticleController
{
public:
	ParticleController();
	
	void update(const ci::Perlin& _perlin,
		        const ci::Vec2i& _mousePos);
	void draw();
	void addParticles(int _amt);
	void addParticles(int _amt, const ci::Vec2i& _mousePos);
	void removeParticles(int _amt);

//private:

	std::list<Particle> mParticles;
	bool mIsAttracting;
};

