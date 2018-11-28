
#include "SettingController.h"
#include "SettingManager.h"
#include "cinder/gl/gl.h"


using namespace std;
using namespace ci;

void SettingController::setup(){
    mFont = Font("Arial", 14);
    
    activeColor = ci::Color(0,0,0);
    normalColor = ci::Color(1, 1, 1);
    
    //activeBGColor = Color(73 / 255.0f, 87.0f / 255.0f, 220.0f / 255.0f);
    activeBGColor = Color(0.9, 0.9, 0.9);
    normalBGColor = Color(73 / 255.0f, 87.0f / 255.0f, 220.0f / 255.0f);
    isSetup = true;
}

void SettingController::draw(){
    
    if(!isSetup){
        setup();
    }
    float yPos = 20;
    int mLoopIndex = 0;
    
    for (auto s : SettingManager::Instance()->getSettings()){
        
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
        int nrOfSettings = SettingManager::Instance()->getSettings().size();
        if (--mIndex < 0){
            mIndex = nrOfSettings - 1;
        }
        return true;
    }
    if (event.getCode() == event.KEY_DOWN){
        int nrOfSettings = SettingManager::Instance()->getSettings().size();
        if (++mIndex >= nrOfSettings){
            mIndex = 0;
        }
        return true;
    }
    if (event.getCode() == event.KEY_LEFT){
        auto setting = SettingManager::Instance()->getSettings().at(mIndex);
        setting->decreaseStep((event.isShiftDown() ? 10 : 1));
        
        return true;
    }
    if (event.getCode() == event.KEY_RIGHT){
        auto setting = SettingManager::Instance()->getSettings().at(mIndex);
        setting->increaseStep((event.isShiftDown() ? 10 : 1));
        
        return true;
    }
    
    if (event.getCode() == event.KEY_s){
        SettingManager::Instance()->writeSettings();
        
        return true;
    }
    
   
    
    
    
    
    
    return false;
    
    
}
