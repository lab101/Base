#pragma once
#include "Singleton.h"
#include "cinder/app/App.h"
#include "cinder/Font.h"
#include "cinder/ImageIo.h"
#include "cinder/gl/gl.h"
#include <thread>
#include <mutex>



class HttpSurfaceLoadEvent {
    
public:
    HttpSurfaceLoadEvent() : isHandled(false), isLoaded(false) {
    };
    
    ~HttpSurfaceLoadEvent() {};
    
    bool isHandled;
    bool isLoaded;
    uint loadId;
    std::string cacheKey;
    bool isCached;
    
    std::function<void(HttpSurfaceLoadEvent&)> callback;
    
    std::string url;
    ci::SurfaceRef response;
};

class AssetCache
{

    std::map<std::string,ci::gl::TextureRef> textures;
    
    // threading stuff
    std::thread httpWorkerThread;
    std::deque<HttpSurfaceLoadEvent> httpWorkQueue;
    std::vector<HttpSurfaceLoadEvent> eventsToDispatch;
    std::mutex eventsMutex;
    std::mutex workQueueMutex;
    bool isThreadRunning;
    std::thread workerThread;
    
    std::string mCachePath;



public:
	AssetCache(){
        isThreadRunning = false;
        
        // create cache folder
       mCachePath = ci::app::getAssetPath("").string() + "cache";
        if (!ci::fs::exists(mCachePath)) {
            ci::fs::create_directories(mCachePath);
        }
    };

	ci::gl::TextureRef getTextureByAssetPath(std::string fullPath){
	    std::cout << "*--- " << ci::app::getAssetPath(fullPath);
	    return getTextureByFullPath(ci::app::getAssetPath(fullPath).string());
	}

	// caching textures
	ci::gl::TextureRef getTextureByFullPath(std::string fullPath)
	{
        auto it = textures.find(fullPath);
        if(it != textures.end()){
            return it->second;
        }else{
            ci::gl::TextureRef texture = ci::gl::Texture::create(ci::loadImage(fullPath));
            textures[fullPath] = texture;
      		return texture;
        }
	}
    
    
    void getSurfaceByUrl(std::string url, std::string cacheKey, std::function<void(HttpSurfaceLoadEvent)> callback){
        
        if(!isThreadRunning) start();
        
        HttpSurfaceLoadEvent e;
        
        if(cacheKey != ""){
            std::string cachePath = mCachePath + "/" + cacheKey + ".png";
            if(ci::fs::exists(cachePath)){
                try{
                    e.response = ci::Surface::create(ci::loadImage(cachePath));
                    e.callback = callback;
                    e.isLoaded = true;
                    eventsMutex.lock();
                    eventsToDispatch.push_back(e);
                    eventsMutex.unlock();
                    return;

                }catch(...){
                    
                };
            }
            
            e.cacheKey = cacheKey;
            e.isCached = true;
        }
        
        workQueueMutex.lock();
        httpWorkQueue.push_back(e);
        httpWorkQueue.back().url = url;
        httpWorkQueue.back().callback = callback;
        
        
        
        workQueueMutex.unlock();

    }
    
    void getSurfaceByUrl(std::string url, std::function<void(HttpSurfaceLoadEvent)> callback){
        getSurfaceByUrl(url, "", callback);
    }


    void start() {
        if(!isThreadRunning){
            isThreadRunning = true;
            workerThread = std::thread(std::bind(&AssetCache::worker, this));
        }
    }
    
    void stop() {
        isThreadRunning = false;
    }

    void worker()
    {
        bool isWorkQueueEmpty;
        HttpSurfaceLoadEvent httpLoadEvent;
        
        while (isThreadRunning) {
            
            workQueueMutex.lock();
            isWorkQueueEmpty = httpWorkQueue.empty();
            workQueueMutex.unlock();
            
            if (!isWorkQueueEmpty) {
                workQueueMutex.lock();
                httpLoadEvent = httpWorkQueue.front();
                httpWorkQueue.pop_front();
                workQueueMutex.unlock();
                
                // could be the case that the item is already removed
                if(!httpLoadEvent.isHandled){
                    doWork(httpLoadEvent);
                    
                    eventsMutex.lock();
                    eventsToDispatch.push_back(httpLoadEvent);
                    eventsMutex.unlock();
                }
                
                
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(20));
        }
    }
    
    
    void doWork(HttpSurfaceLoadEvent& httpLoadEvent) {
        try {
            
            httpLoadEvent.response = ci::Surface::create(loadImage(loadUrl(httpLoadEvent.url, ci::UrlOptions().timeout(1.0f).ignoreCache())));
            httpLoadEvent.isLoaded = true;
            if(httpLoadEvent.isCached){
                std::string savePath = mCachePath + "/" + httpLoadEvent.cacheKey + ".png";
                ci::writeImage(savePath, *httpLoadEvent.response);
            }
        }
        catch (...) {
            //httpLoadEvent.st
            // todo error handeling
        }
    }


    void update() {
        eventsMutex.lock();
        
        for (HttpSurfaceLoadEvent& e : eventsToDispatch) {
            if (!e.isHandled) {
                if (e.callback){
                  e.callback(e);
                }
                e.isHandled = true;
            }
        }
        
        eventsToDispatch.erase(remove_if(eventsToDispatch.begin(), eventsToDispatch.end(), [](HttpSurfaceLoadEvent e) { return e.isHandled; }), eventsToDispatch.end());
        eventsMutex.unlock();
    }


    
    // caching fonts.
	ci::Font getFont(std::string name,int size)
	{
		std::string fontName = name + std::to_string(size);
		
		for (auto p : fonts)
		{
			if (p.first == fontName)
			{
				return p.second;
			}
		}

		ci::Font font = ci::Font(ci::app::loadAsset(name), size);
		fonts.push_back(std::make_pair(fontName, font));
		return font;

	}
	std::vector<std::pair<std::string, ci::Font  >> fonts;
    

};



typedef Singleton< AssetCache>  AssetCacheSingleton;

inline  AssetCache* CACHE() {
	return  AssetCacheSingleton::Instance();
}
