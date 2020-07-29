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
        T v = T();

        if (doc.hasChild(path)) {
            ci::XmlTree node = doc.getChild(path);
            v.x = node.getAttributeValue<int>("x");
            v.y = node.getAttributeValue<int>("y");
        } else {
            CI_LOG_E("missing xml node " + path);
        }
        return v;
    }


    template<typename T>
    inline ci::XmlTree setValue(std::string name, T value) {

        bool isBool = std::is_same<T, bool>::value;;
        ci::XmlTree node(name, "");

        if (isBool) {
            node.setValue(value ? "true" : "false");
        } else {
            node.setValue(value);
        }

        return node;
    }

    template<typename T>
    inline ci::XmlTree setObject(std::string name, T value) {

        bool isVec3 = std::is_same<T, ci::vec3>::value;
        bool isVec2 = std::is_same<T, ci::vec2>::value;
        ci::XmlTree node(name, "");

        if (isVec2 || isVec3) {
            node.setAttribute("x", value[0]);
            node.setAttribute("y", value[1]);
            if (isVec3) node.setAttribute("z", value[2]);
        }


        return node;
    }


}