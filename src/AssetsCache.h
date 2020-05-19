#pragma once
#include "Singleton.h"
#include "cinder/app/App.h"
#include "cinder/Font.h"
#include "cinder/ImageIo.h"

class AssetCache
{

public:
	AssetCache(){};

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

	std::map<std::string,ci::gl::TextureRef> textures;





    
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
