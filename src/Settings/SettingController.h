#include "cinder/app/App.h"
#include "cinder/Font.h"
#include "SettingManager.h"

class SettingController{
    
    int mIndex=0;
    ci::Font mFont;
    
    ci::Color activeColor;
    ci::Color normalColor;
    
    ci::Color activeBGColor;
    ci::Color normalBGColor;
    
    SettingManager* mSettingManager;
    
    bool isSetup = false;
public:
    
    void setup(SettingManager* settingManger);
    void draw();
    bool checkKeyDown(ci::app::KeyEvent event);
    
    
    
};
