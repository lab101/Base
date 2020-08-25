#pragma once

#include "cinder/Xml.h"
#include "cinder/Log.h"


namespace lab101 {


    template<typename T>
    inline T getNodeAttributeValue(ci::XmlTree &node, std::string path) {
        T v = T();

        if (node.hasAttribute(path)) {
            //ci::XmlTree node = doc.getChild(path);
            v = node.getAttributeValue<T>(path);
        } else {
            CI_LOG_E("missing xml attribute " + path);
        }

        return v;
    }

    template<typename T>
    inline T getNodeValue(ci::XmlTree &doc, std::string path) {
        T v = T();
        bool isBool = std::is_same<T, bool>::value;

        if (doc.hasChild(path)) {
            ci::XmlTree node = doc.getChild(path);
            if (isBool) {
                std::string boolString = node.getValue<std::string>();
                v = boolString == "true" ? true : false;
            } else {
                v = node.getValue<T>();
            }
        } else {
            CI_LOG_E("missing xml node " + path);
        }

        return v;
    }


    template<typename T>
    inline T getNodeObject(ci::XmlTree &doc, std::string path) {
        T value = T();

        if (doc.hasChild(path)) {
            ci::XmlTree node = doc.getChild(path);
            int elements = value.length();
            std::string labels[4] = {"x","y","z","w"};
            for(int i=0;i < elements;++i){
               value[i] = node.getAttributeValue<float>(labels[i]);
            }


        } else {
            CI_LOG_E("missing xml node " + path);
        }
        return value;
    }


    template<typename T>
    inline ci::XmlTree setValue(std::string name, T value) {

        bool isBool = std::is_same<T, bool>::value;;
        ci::XmlTree node(name, "");

       // if (isBool) {
       //     node.setValue(value == 1 ? "true" : "false");
       // } else {
            node.setValue(value);
       // }

        return node;
    }

    template<typename T>
    inline ci::XmlTree setObject(std::string name, T value) {

        int elements = value.length();
        ci::XmlTree node(name, "");

        std::string labels[4] = {"x","y","z","w"};

        for(int i=0;i < elements;++i){
            node.setAttribute(labels[i], value[i]);
        }
        return node;
    }


}