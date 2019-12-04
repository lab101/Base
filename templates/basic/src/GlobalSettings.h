#pragma once

#include "cinder/app/App.h"

#include "../blocks/Base/src/Singleton.h"

#include "../blocks/Base/src/Settings/SettingManager.h"
#include "../blocks/Base/src/Settings/SettingBase.h"
#include "../blocks/Base/src/Settings/SettingString.h"


class GlobalSettings{


public:

	SettingManager mSettingManager;

    
	Setting<bool>   debugMode;
	Setting<bool>   isFullscreen;
	Setting<bool>   isMouseOn;


    GlobalSettings();
    
    //Setting<std::string> meshFolder;
    Setting<int> screenWidth;
	Setting<int> screenHeight;
	Setting<int> resetScreenTime;
	Setting<float> screenScale;
  
	void setup(std::string appName);

    ci::vec2 getScreenSize();

};



typedef Singleton<GlobalSettings> GlobalSettingsSingleton;

inline GlobalSettings* GS(){
	return GlobalSettingsSingleton::Instance();
}
