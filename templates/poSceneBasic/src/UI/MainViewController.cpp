#include "MainViewController.h"
#include "../blocks/Base/src/Settings/GlobalSettings.h"


using namespace po::scene;

using namespace ci;
using namespace ci::app;
using namespace std;


MainViewControllerRef MainViewController::create()
{
	MainViewControllerRef ref = std::make_shared<MainViewController>();
	ref->setup();
	return ref;
}


void MainViewController::setup(){

	currentAppstate = START;
	mStartScreen = lab101::StartScreen::create();
	
	getView()->addSubview(mStartScreen);


}

void MainViewController::update(){

	if (ci::app::getElapsedSeconds() - lastInteraction > GS()->resetScreenTime.value() && currentAppstate != START){
		setState(START);
	}
}




bool MainViewController::setState(AppState newState){

	if (newState == currentAppstate) return false;
	lastInteraction = ci::app::getElapsedSeconds();

	if (newState == START){
		mStartScreen->setVisible(true);
	}

	return true;
}