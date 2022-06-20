
//
//  StatsManager.hpp
//
//  Created by Kris Meeusen on 15/09/2017.
//
//

#pragma once

#include "Singleton.h"
#include <iostream>
#include <fstream>

class StatsManager{
    
    
    std::ofstream statsFile;
    std::string getDateString();
    
public:
    void log(std::string type, std::string action, std::string data1 = "", std::string data2 = "");
    StatsManager();
    ~StatsManager();
};


typedef Singleton<StatsManager> StatsManagerSingleton;

inline StatsManager* STATS(){
    return StatsManagerSingleton::Instance();
}

