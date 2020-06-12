#include "TouchVisualiser.h"

using namespace ci;
using namespace ci::app;
using namespace std;
using namespace gl;


void TouchVisualiser::setup(){

	mTouchpointText = gl::Texture::create(loadImage(app::loadAsset("touchpoint.png")));


	ci::app::getWindow()->getSignalMouseDown().connect(std::bind(&TouchVisualiser::mouseDown, this, std::placeholders::_1));
	ci::app::getWindow()->getSignalMouseMove().connect(std::bind(&TouchVisualiser::mouseMove, this, std::placeholders::_1));
	ci::app::getWindow()->getSignalMouseDrag().connect(std::bind(&TouchVisualiser::mouseMove, this, std::placeholders::_1));
	ci::app::getWindow()->getSignalMouseUp().connect(std::bind(&TouchVisualiser::mouseUp, this, std::placeholders::_1));


}

void TouchVisualiser::draw(){

	ci::gl::color(1, 1, 1);
	touchPointsLock.lock();

	for (auto& t : mActivePoints){
		ci::gl::draw(mTouchpointText, t.second - vec2(65, 65));
	}
	touchPointsLock.unlock();

}





void	TouchVisualiser::touchesBegan(ci::app::TouchEvent event){

}


void	TouchVisualiser::touchesMoved(ci::app::TouchEvent event){

}

void	TouchVisualiser::touchesEnded(ci::app::TouchEvent event){

}

void TouchVisualiser::mouseDown(ci::app::MouseEvent event){
	mActivePoints.insert(make_pair(-1, vec2(event.getPos().x, event.getPos().y)));
}

void TouchVisualiser::mouseUp(ci::app::MouseEvent event){
	mActivePoints.erase(-1);
}



void TouchVisualiser::mouseMove(ci::app::MouseEvent event){
	if (mActivePoints.find(-1) != mActivePoints.end()){
		mActivePoints[-1] = vec2(event.getPos().x, event.getPos().y);
	}


}
