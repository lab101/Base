//
// Created by lab101 on 16/09/2020.
//

#ifndef INC_3DSTATION_FILEHELPER_H
#define INC_3DSTATION_FILEHELPER_H

#include "string"

#include <time.h>
#include <chrono>
#include <ctime>
#include <chrono>
#include <iostream>
#include <fstream>

#include "cinder/app/App.h"
#include "cinder/Log.h"
#include "cinder/Filesystem.h"



inline float getLastWrittenTimeInSeconds(std::string filePath){

    std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
    auto createdTime = ci::fs::last_write_time(filePath);
    //auto aa = duration_cast<seconds>(now.time_since_epoch() -createdTime.time_since_epoch());
    auto aa = now.time_since_epoch() - createdTime.time_since_epoch();
}




inline std::vector<ci::fs::path> readDirectory(std::string directory,std::vector<std::string> extensions)
{

    std::vector<ci::fs::path> filenames;
    for (ci::fs::directory_iterator it(directory); it != ci::fs::directory_iterator(); ++it) {
        {
            if (!is_directory(*it)) {

                for(auto& extensionFilter : extensions){
                    std::string extension = it->path().extension().string();
                    ///std::cout << "extension" << it->path() << std::endl;

                    if (extensionFilter == extension) {
                        std::cout << "found file" << it->path() << std::endl;
                        filenames.push_back(it->path());
                        // break from extension loop
                        break;
                    }
                }
            }
        }
    }

    sort(filenames.begin(),filenames.end());

    return filenames;
};


inline std::vector<ci::fs::path> readDirectory(std::string directory,std::string extension){
    std::vector<std::string> extensions = {extension};
    return readDirectory(directory, extensions);
}


inline std::vector<std::string> getStringList(std::vector<ci::fs::path> files){
    std::vector<std::string> fileNames;
    for(auto& file : files){
        fileNames.push_back(file.filename().string());
    }
    return fileNames;
}

inline std::string readFile(std::string path){

//read data
    try{

        std::ifstream f(path);
        std::stringstream buf;
        buf << f.rdbuf();
        std::string data = buf.str();
        return data;
    }
    catch(...){
        CI_LOG_E("ERROR reading file: " + path);
        return "";
    }
}



#endif //INC_3DSTATION_FILEHELPER_H
