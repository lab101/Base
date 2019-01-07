#pragma once

#include "../Singleton.h"
#include "cinder/app/App.h"

#include "SettingManager.h"
#include "SettingBase.h"
#include "SettingString.h"

class GlobalSettings{


public:

	GlobalSettings();

    ci::Color       highlighColor;
    
	Setting<bool>   debugMode;
	Setting<bool>   isFullscreen;
	Setting<bool>   isMouseOn;

    Setting<int> screenWidth;
	Setting<int> screenHeight;
	
	Setting<int> resetScreenTime;
	Setting<float> screenScale;
    ci::vec2 getScreenSize();

};


typedef Singleton<GlobalSettings> GlobalSettingsSingleton;

inline GlobalSettings* GS(){
	return GlobalSettingsSingleton::Instance();
}
