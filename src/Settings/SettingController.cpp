
#include "SettingController.h"
#include "cinder/gl/gl.h"


using namespace std;
using namespace ci;

void SettingController::setup(SettingManager* settingManager){
    mFont = Font("Arial", 14);
    
    mSettingManager = settingManager;
    activeColor = ci::Color(0,0,0);
    normalColor = ci::Color(1, 1, 1);
    
    //activeBGColor = Color(73 / 255.0f, 87.0f / 255.0f, 220.0f / 255.0f);
    activeBGColor = Color(0.9, 0.9, 0.9);
    normalBGColor = Color(73 / 255.0f, 87.0f / 255.0f, 220.0f / 255.0f);
    isSetup = true;
}

void SettingController::draw(){
    
    if(!isSetup){
        CI_LOG_E("setup not run on SettingController");
        return;
        //setup();
    }
    float yPos = 20;
    int mLoopIndex = 0;
    
    for (auto s : mSettingManager->getSettings()){
        
        float offset = (mLoopIndex == mIndex) ? 4 : 0;
        
        ci::gl::color(mLoopIndex == mIndex ? activeBGColor : normalBGColor);
        ci::gl::drawSolidRoundedRect(Rectf(20 - offset, yPos - 8 - offset, 400 + offset, yPos + 14 + offset), 4);
        
        ci::gl::drawString(s->getKey(), vec2(40, yPos), mLoopIndex == mIndex ? activeColor : normalColor, mFont);
        ci::gl::drawString(s->getValueAsString(), vec2(280, yPos), mLoopIndex == mIndex ? activeColor : normalColor, mFont);
        
        
        
        yPos += 32;
        mLoopIndex++;
    }
    
    
}



bool SettingController::checkKeyDown(ci::app::KeyEvent event){
    
    if (event.getCode() == event.KEY_UP){
        int nrOfSettings = mSettingManager->getSettings().size();
        if (--mIndex < 0){
            mIndex = nrOfSettings - 1;
        }
        return true;
    }
    if (event.getCode() == event.KEY_DOWN){
        int nrOfSettings = mSettingManager->getSettings().size();
        if (++mIndex >= nrOfSettings){
            mIndex = 0;
        }
        return true;
    }
    if (event.getCode() == event.KEY_LEFT){
        auto setting = mSettingManager->getSettings().at(mIndex);
        setting->decreaseStep((event.isShiftDown() ? 10 : 1));

        return true;
    }
    if (event.getCode() == event.KEY_RIGHT){
        auto setting = mSettingManager->getSettings().at(mIndex);
        setting->increaseStep((event.isShiftDown() ? 10 : 1));

        return true;
    }

    if (event.getCode() == event.KEY_s){
        mSettingManager->writeSettings();

        return true;
    }

   
    
    
    
    
    
    return false;
    
    
}
