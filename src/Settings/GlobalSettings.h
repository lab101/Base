#pragma once


#include "../Singleton.h"
#include "cinder/app/App.h"
#include "cinder/Font.h"
#include "cinder/gl/Texture.h"
#include "cinder/gl/TextureFont.h"
#include "cinder/Font.h"

#include "SettingManager.h"
#include "SettingBase.h"
#include "SettingString.h"

class GlobalSettings{


public:


    ci::Color       highlighColor;
    
	Setting<bool>   debugMode;
//	Setting<bool>   isKeyboardLocked;
	Setting<bool>   isFullscreen;
	Setting<bool>   isMouseOn;

	SettingString   dbServiceBaseUrl;
	SettingString   productType;

    GlobalSettings();
    
    //Setting<std::string> meshFolder;
    Setting<int> screenWidth;
	Setting<int> screenHeight;
    Setting<int> scanYourBadgeYPos;
	Setting<int> phidgetSerialNr;
	
	Setting<int> resetScreenTime;

	Setting<int> particleSkipCount;

    Setting<float> screenScale;

	//Setting<float> logoOffset;


	std::vector<std::string> availableStations;
  
    

    ci::vec2 getScreenSize();

};



typedef Singleton<GlobalSettings> GlobalSettingsSingleton;

inline GlobalSettings* GS(){
	return GlobalSettingsSingleton::Instance();
}
