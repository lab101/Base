#pragma once

#include <string>
#include "cinder/json.h"

class SettingBase{
	std::string mKey;
	bool isTweakable;

protected:
public:


	std::string getKey(){
		return mKey;
	}

	void setKey(std::string key){
		mKey = key;
	}

	virtual std::string getValueAsString() { return "not implemented!"; };

	virtual ci::JsonTree toJson(){ return ci::JsonTree("data", ""); };
	virtual void setFromJson(ci::JsonTree json){  };
	virtual void increaseStep(float multiplyier = 1){  };
	virtual void decreaseStep(float multiplyier = 1){  };




	// needed for tweakable settings
	// should find a better way to remove them here.
	virtual std::string getTweakableSettings(){ return ""; };
	virtual int  getSortOrder(){ return 0; };
	virtual std::string getCategory(){ return ""; };


};