//
//  StatsManager.cpp
//
//  Created by Kris Meeusen on 15/09/2017.
//
//

#include "StatsManager.h"
//#include "Lab101Utils.h"
#include "cinder/Log.h"
#include "cinder/app/App.h"
#include "cinder/Utilities.h"


#include <chrono>  // chrono::system_clock
#include <ctime>   // localtime


using namespace std;
using namespace ci;


inline std::string StatsManager::getDateString(){
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);
    
    std::stringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), "%Y;%m;%d;%H;%M;%S");
    return ss.str();
}


void StatsManager::log(std::string type, std::string action, std::string data1, string data2){

    CI_LOG_I("STATS: " << type << ";" << action << ";" << data1 << ";" << data2);

    if (statsFile.is_open()) {
        
        statsFile << getDateString() << ";" << type << ";" << action << ";" << data1 << ";" << data2 << std::endl;
    }
}


StatsManager::StatsManager(){
    std::string path = ci::app::getAssetPath("").string();
  //  std::string path = ci::getDocumentsDirectory().string();

    statsFile.open (path +  "/stats.csv", ios::out | ios::app);
    
}

StatsManager::~StatsManager(){
    statsFile.close();
}
