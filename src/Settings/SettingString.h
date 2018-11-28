#pragma once

#include <string>
#include "cinder/Json.h"
#include "SettingBase.h"

// SETTING tweakable
class SettingString : public SettingBase {

	std::string mValue;

	int mSortOrder = 0;
	std::string mCategory = "default";


public:

	SettingString(){}

	SettingString(std::string key, std::string defaultValue){
		mValue = defaultValue;


		SettingBase::setKey(key);
	}

	
	int getSortOrder() override{
		return mSortOrder;
	}

	std::string getCategory() override{
		return mCategory;
	}

	void setValue(std::string value){
		mValue = value;
	}

	

	std::string& value(){
		return mValue;
	}


	// overrride / type specific stuff

	void setFromJson(ci::JsonTree value) override{
		mValue = value.getValue<std::string>();
	}


	ci::JsonTree toJson() override{
		ci::JsonTree json = ci::JsonTree(getKey(), mValue);
		return json;
	}


	std::string getValueAsString() override {
		return ci::toString(mValue);
	};

};
