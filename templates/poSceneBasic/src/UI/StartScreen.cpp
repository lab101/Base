#include "StartScreen.h"

#include "poScene/TextView.h"

#include "../blocks/Base/src/Settings/GlobalSettings.h"
#include "../blocks/Base/src/poHelper.h"


using namespace lab101;
using namespace po::scene;
using namespace ci;



static StartScreenRef create();

StartScreenRef StartScreen::create()
{
	StartScreenRef ref(new StartScreen());
	ref->setup();
	return ref;
}


void StartScreen::setup(){

	// DEMO 
	ci::TextBox ciTextBox = ci::TextBox();
	ciTextBox.setPremultiplied(true);
	ciTextBox.size(ivec2(1200, 540));
	ciTextBox.color(GS()->highlighColor);
	ciTextBox.text("STARTSCREEN");

	ciTextBox.alignment(ci::TextBox::Alignment::CENTER);
	ciTextBox.font(Font("Arial", 30));

	po::scene::TextViewRef mDemoText = po::scene::TextView::create(ciTextBox);
	mDemoText->setAlignment(po::scene::Alignment::CENTER_CENTER);
	mDemoText->setPosition(450, 800);
	addSubview(mDemoText);


	mDemoImage = lab101::createImageRefByAsset("UI/a.jpg");
	mDemoImage->setPosition(vec2(400, 220));
	mDemoImage->setAlignment(po::scene::Alignment::CENTER_LEFT);
	addSubview(mDemoImage);
}


void StartScreen::update(){


}
