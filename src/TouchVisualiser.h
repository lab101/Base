#pragma once
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include <map>

class TouchVisualiser{

	std::mutex touchPointsLock;
	std::map<uint32_t, ci::vec2>          mActivePoints;

	ci::gl::TextureRef          mTouchpointText;

	void	touchesBegan(ci::app::TouchEvent event);
	void	touchesMoved(ci::app::TouchEvent event);
	void	touchesEnded(ci::app::TouchEvent event);

	void mouseDown(ci::app::MouseEvent event);
	void mouseUp(ci::app::MouseEvent event);
	void mouseDrag(ci::app::MouseEvent event);
	void mouseMove(ci::app::MouseEvent event);


public:

	void setup();
	void draw();



};
