#include "Particle.h"

#include "cinder\Rand.h"

Particle::Particle(ci::Vec2f _loc)
	: mPos(_loc)
	, mDir(ci::Rand::randVec2f())
	, mVel(ci::Rand::randVec2f())
	, mTmpVel(mVel)
	, mRadius(0.f)
	, mMaxRadius(ci::Rand::randFloat(1.f,10.f))
	, mPhase(ci::Rand::randFloat(25.f))
	, mSegments(ci::Rand::randInt(3,20))
{
}


void Particle::update(const ci::Perlin& _perlin,
	                  const bool _attarcting,
	                  const ci::Vec2i& _mousePos)
{
	float elapsedTime = static_cast<float>(ci::app::getElapsedSeconds());

	if (_attarcting)
	{
		mDirToCursor = _mousePos - mPos;
		mDirToCursor.safeNormalize();
		mPos += mDirToCursor * 12.f;

		mTmpVel = 12.f * mVel;
	}
	else
	{
		float noise = _perlin.fBm(ci::Vec3f(mPos.x * 0.005f,
			                                mPos.y * 0.005f,
		  					                mPhase * 0.1f));

		float angle = noise * 25.0f;
		mDir = ci::Vec2f(cos(angle), sin(angle));
		
		if (abs(mTmpVel.x) > abs(mVel.x) && abs(mTmpVel.y) > abs(mVel.y))
		{
			mTmpVel *= 0.99f;
			mPos += mDir * mTmpVel;
		}		
		else
			mPos += mDir * mVel;
	}

	mColorVec.x = abs(cos(elapsedTime + mPhase));
	mColorVec.y = abs(sin(elapsedTime - mPhase));
	//mColorVec.z = abs(cos(ci::app::getElapsedSeconds() * mPhase));
	mColorVec.z = abs(sin(elapsedTime + mPhase) *
		              cos(elapsedTime - mPhase));

	mRadius = abs(sin(elapsedTime + mPhase) * mMaxRadius) + 1.f;
}

void Particle::draw()
{
	ci::gl::color(ci::Color(mColorVec.x, mColorVec.y, mColorVec.z));

	ci::gl::pushModelView();

	ci::gl::translate(mPos);
	ci::gl::rotate(360.f*sin(ci::app::getElapsedSeconds()));
	ci::gl::translate(-mPos);

	ci::gl::drawSolidCircle(mPos, mRadius, mSegments);

	ci::gl::popModelView();
}

ci::Vec2f Particle::getPosition() const
{
	return mPos;
}