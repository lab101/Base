#pragma once

#include "poScene/ViewController.h"


// add all screens here
#include "StartScreen.h"


class MainViewController;
typedef std::shared_ptr<MainViewController> MainViewControllerRef;

enum AppState { START, OVERVIEW, DETAIL };


class MainViewController : public po::scene::ViewController
{

	AppState currentAppstate;

	// screens
	lab101::StartScreenRef mStartScreen;
	
	void setup();
	void update();
	bool setState(AppState newState);

public:
	// used to active screensaver or other inactivity feedback.
	float lastInteraction;

	static MainViewControllerRef create();
};
