//
//  GlobalSettings.cpp
//  InnovationWall
//
//  Created by Kris Meeusen on 01/02/16.
//
//

#include <stdio.h>
#include "GlobalSettings.h"

#include "cinder/Utilities.h"

using namespace std;
using namespace ci;



void GlobalSettings::setup(std::string appName) {

	mSettingManager.setAppName(appName);
	mSettingManager.readSettings();

	debugMode = Setting<bool>("debug", true);
	mSettingManager.addSetting(&debugMode);
    
	isMouseOn = Setting<bool>("isMouseOn", true);
	mSettingManager.addSetting(&isMouseOn);

	isFullscreen = Setting<bool>("isFullscreen", false);
	mSettingManager.addSetting(&isFullscreen);


    screenScale = Setting<float>("screenScale",1.0).setSteps(0.001f);
    screenScale.setMax(2.0f);
    screenScale.setMin(.1f);
	mSettingManager.addSetting(&screenScale);


    screenWidth = Setting<int>("screenwidth", 1080);
	mSettingManager.addSetting(&screenWidth);

	screenHeight = Setting<int>("screenHeight", 1080);
	mSettingManager.addSetting(&screenHeight);

	resetScreenTime = Setting<int>("resetSCreenTime", 60);
	mSettingManager.addSetting(&resetScreenTime);
   
}



GlobalSettings::GlobalSettings() {
}

ci::vec2 GlobalSettings::getScreenSize(){
    return ci::vec2(screenWidth.value(), screenHeight.value());
}




