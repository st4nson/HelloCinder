#pragma once

#include "cinder\app\AppBasic.h"
#include "cinder\Perlin.h"

class Particle
{
public:
	Particle(ci::Vec2f _loc);

	void update(const ci::Perlin& _perlin,
		        const bool _attarcting,
		        const ci::Vec2i& _mousePos);

	void draw();

	ci::Vec2f getPosition() const;

private:
	ci::Vec2f mPos;
	ci::Vec2f mDir;
	ci::Vec2f mDirToCursor;
	ci::Vec2f mVel;
	ci::Vec2f mTmpVel;
	float     mRadius;
	float	  mMaxRadius;
	float	  mPhase;
	int		  mSegments;
	ci::Vec3f mColorVec;
};

