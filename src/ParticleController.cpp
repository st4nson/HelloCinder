#include "ParticleController.h"
#include "cinder\Rand.h"

ParticleController::ParticleController()
	: mIsAttracting(false)
{
}

void ParticleController::update(const ci::Perlin& _perlin, const ci::Vec2i& _mousePos)
{
	for (auto &particle : mParticles)
		particle.update(_perlin, mIsAttracting, _mousePos);

	mParticles.remove_if([](const Particle& particle)
	{
		const int offset = 5;
		bool x1 = particle.getPosition().x < 0.f - offset;
		bool x2 = particle.getPosition().x > ci::app::getWindowWidth() + offset;
		bool y1 = particle.getPosition().y < 0.f - offset;
		bool y2 = particle.getPosition().y > ci::app::getWindowHeight() + offset;

		return (x1 || x2 || y1 || y2);
	});
}

void ParticleController::draw()
{
	for (auto &particle : mParticles)
		particle.draw();
}

void ParticleController::addParticles(int _amt)
{
	for (int i = 0; i < _amt; i++)
	{
		auto x = ci::Rand::randFloat(static_cast<float>(ci::app::getWindowWidth()));
		auto y = ci::Rand::randFloat(static_cast<float>(ci::app::getWindowHeight()));

		mParticles.push_back(Particle(ci::Vec2f(x, y)));
	}	
}

void ParticleController::addParticles(int _amt, const ci::Vec2i& _mousePos)
{
	for (int i = 0; i < _amt; i++)
		mParticles.push_back(Particle(ci::Vec2f(static_cast<float>(_mousePos.x),
		                                        static_cast<float>(_mousePos.y))));
}

void ParticleController::removeParticles(int _amt)
{
	for (int i = 0; i < _amt; i++)
	{
		mParticles.pop_back();
		if (mParticles.empty()) break;
	}
}
