//
// Created by lab101 on 05/10/2021.
//

#pragma once





// VEC2

class SettingVec2 : public SettingBase{

public:
    ci::vec2 mValue;


    SettingVec2(std::string key, ci::vec2 defaultValue){
        SettingVec2(key,defaultValue.x,defaultValue.y);
    }

    SettingVec2(std::string key, float x, float y){
        mValue.x = x;
        mValue.y = y;
        SettingBase::setKey(key);
    }


    void setFromJson(ci::JsonTree value){

        if(value.getNumChildren() == 2){
            mValue.x = value.getChild("x").getValue<float>();
            mValue.y = value.getChild("y").getValue<float>();
        }
    }


    ci::JsonTree toJson(){
        ci::JsonTree data = ci::JsonTree::makeArray(getKey());
        data.addChild(ci::JsonTree("x",mValue.x));
        data.addChild(ci::JsonTree("y",mValue.y));
        return data;
    }

};




// VEC3
//
//class SettingVec3 : public SettingBase{
//
//public:
//    ci::vec3 mValue;
//
//    SettingVec3(){}
//
//    SettingVec3(std::string key, ci::vec3 defaultValue){
//        mValue = defaultValue;
//        SettingBase::setKey(key);
//        addSetting(this);
//
//    }
//
//
//    void setFromJson(ci::JsonTree value) override{
//
//        if(value.getNumChildren() == 3){
//            mValue.x = value.getChild("x").getValue<float>();
//            mValue.y = value.getChild("y").getValue<float>();
//            mValue.z = value.getChild("z").getValue<float>();
//        }
//    }
//
//
//    ci::JsonTree toJson() override{
//        ci::JsonTree data = ci::JsonTree::makeArray(getKey());
//        data.addChild(ci::JsonTree("x",mValue.x));
//        data.addChild(ci::JsonTree("y",mValue.y));
//        data.addChild(ci::JsonTree("z",mValue.z));
//        return data;
//    }
//};





// Vector points

class SettingVec2Vector : public SettingBase{

public:
    std::vector<ci::vec2> mValue;

    SettingVec2Vector(){}

    SettingVec2Vector(std::string key){
        setKey(key);
    }

    SettingVec2Vector(std::string key, std::vector<ci::vec2> defaultValue){
        mValue = defaultValue;
        SettingBase::setKey(key);
    }


    void setFromJson(ci::JsonTree value) override{

        for(auto v : value.getChildren()){
            glm::vec2 p (v.getChild("x").getValue<float>(),v.getChild("y").getValue<float>());
            mValue.push_back(p);
        }
    }


    ci::JsonTree toJson() override{
        ci::JsonTree data = ci::JsonTree::makeArray(getKey());

        int pointNr =0;
        for(auto m : mValue){


            // leading zero string
            std::stringstream stream;
            stream.setf(std::ios_base::fixed, std::ios_base::floatfield);
            //stream.precision(10);
            stream << std::setw(5);
            stream << std::setfill('0');
            stream << ++pointNr;


            auto o = ci::JsonTree::makeObject(stream.str());

            o.addChild(ci::JsonTree("x",m.x));
            o.addChild(ci::JsonTree("y",m.y));

            data.addChild(o);
        }
        return data;
    }
};



// Vector floats

class SettingFloatVector : public SettingBase{

public:
    std::vector<float> mValue;

    SettingFloatVector(){}

    SettingFloatVector(std::string key){
        setKey(key);
    }

    SettingFloatVector(std::string key, std::vector<float> defaultValue){
        mValue = defaultValue;
        SettingBase::setKey(key);
    }


    void setFromJson(ci::JsonTree value) override{

        for(auto v : value.getChildren()){
            mValue.push_back(v.getChild("value").getValue<float>());
        }
    }


    ci::JsonTree toJson() override{
        ci::JsonTree data = ci::JsonTree::makeArray(getKey());

        int pointNr =0;
        for(auto m : mValue){


            // leading zero string
            std::stringstream stream;
            stream.setf(std::ios_base::fixed, std::ios_base::floatfield);
            stream << std::setw(5);
            stream << std::setfill('0');
            stream << ++pointNr;

            auto o = ci::JsonTree::makeObject(stream.str());

            o.addChild(ci::JsonTree("value",m));

            data.addChild(o);
        }
        return data;
    }
};


