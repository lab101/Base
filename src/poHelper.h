//
//  poHelper.hpp
//  ScreenApp
//
//  Created by Kris Meeusen on 22/10/15.
//
//

#ifndef poHelper_hpp
#define poHelper_hpp

#include <stdio.h>
#include "glm/vec2.hpp"
#include "poScene/ImageView.h"

namespace lab101 {

	

	inline po::scene::ImageViewRef createImageRefByAsset(std::string assetName){
		try{

			ci::gl::TextureRef text = ci::gl::Texture::create(ci::loadImage(ci::app::getAssetPath(assetName)));
			po::scene::ImageViewRef mImage = po::scene::ImageView::create(text);
			
			return mImage;


		}
		catch (...){
			throw new ci::Exception("could not load image " + assetName);
		}

		return NULL;
	}

}



#endif /* poHelper_hpp */