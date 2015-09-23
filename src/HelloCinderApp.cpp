#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"

#include "cinder/Perlin.h"

#include "ParticleController.h"

using namespace ci;
using namespace ci::app;

class HelloCinderApp : public AppBasic {
  public:
	void prepareSettings(Settings *settings);
	void setup();
	void mouseDown( MouseEvent event );
	void mouseUp( MouseEvent event );
	void mouseMove(MouseEvent event);
	void mouseDrag(MouseEvent event);
	void update();
	void draw();

  private:
	  ci::Perlin mPerlin;

	  ParticleController mParticleController;

	  Vec2i mMousePosition;
};

void HelloCinderApp::prepareSettings(Settings *settings)
{
	settings->setFrameRate(60.f);
	settings->setWindowSize(1024, 768);
}

void HelloCinderApp::setup()
{
	mPerlin = Perlin();
	mParticleController.addParticles(100);
}

void HelloCinderApp::mouseDown( MouseEvent event )
{
	if (event.isLeft())
		mParticleController.addParticles(50, event.getPos());
	else if (event.isRight())
		mParticleController.mIsAttracting = true;
}

void HelloCinderApp::mouseUp(MouseEvent event)
{
	if (event.isRight())
		mParticleController.mIsAttracting = false;
}

void HelloCinderApp::mouseMove(MouseEvent event)
{
	mMousePosition = event.getPos();

	//ci::app::console() << mMousePosition << std::endl;
}

void HelloCinderApp::mouseDrag(MouseEvent event)
{
	mouseMove(event);
}

void HelloCinderApp::update()
{
	mParticleController.update(mPerlin, mMousePosition);
}

void HelloCinderApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) ); 
	mParticleController.draw();
}

CINDER_APP_BASIC( HelloCinderApp, RendererGl)
