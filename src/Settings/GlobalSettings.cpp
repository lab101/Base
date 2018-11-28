//
//  GlobalSettings.cpp
//  Created by Kris Meeusen on 01/02/16.
//
//

#include <stdio.h>
#include "GlobalSettings.h"
#include "cinder/Utilities.h"

using namespace std;
using namespace ci;



GlobalSettings::GlobalSettings(){

	// debug mode on or off
	debugMode = Setting<bool>("debug", true);
	addSetting(&debugMode);
 
	// hide mouse cursor
	isMouseOn = Setting<bool>("isMouseOn", true);
	addSetting(&isMouseOn);

	// fullscreen
	isFullscreen = Setting<bool>("isFullscreen", false);
	addSetting(&isFullscreen);

	// scaling of the whole scene
	// used for development of highress apps
    screenScale = Setting<float>("screenScale",1.0).setSteps(0.001f);
    screenScale.setMax(2.0f);
    screenScale.setMin(.1f);
    addSetting(&screenScale);
	
	// screen width
    screenWidth = Setting<int>("screenwidth", 1080);
    addSetting(&screenWidth);

	// screen height
	screenHeight = Setting<int>("screenHeight", 1920);
	addSetting(&screenHeight);

	// reset the app after x seconds.
	resetScreenTime = Setting<int>("goToScreensaverTime", 60);
	addSetting(&resetScreenTime);

}



ci::vec2 GlobalSettings::getScreenSize(){
    return ci::vec2(screenWidth.value(), screenHeight.value());
}




