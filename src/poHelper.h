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
#include "AssetsCache.h"

namespace lab101 {

	

	inline ci::ivec2 getWindowSize(){
		return ci::ivec2(1680, 1050);
	}

	inline ci::vec2 getWindowCenter(){
		return  ci::vec2(getWindowSize().x * 0.5, getWindowSize().y * 0.5);
	}

	inline po::scene::ImageViewRef createImageRefByAsset(std::string assetName){
		try{

			ci::gl::TextureRef text = CACHE()->getTexture(assetName);
			if (text == nullptr){
					text = ci::gl::Texture::create(ci::loadImage(ci::app::getAssetPath(assetName)));
					CACHE()->textures.push_back(std::make_pair(assetName, text));
			}

			po::scene::ImageViewRef mImage = po::scene::ImageView::create(text);
			
			return mImage;


		}
		catch (...){
			throw new ci::Exception("could not load image " + assetName);
		}

		return NULL;
	}


	//    inline void setTextOnTexbox(po::scene::TextBoxRef textBox,std::string newText){
	//        ci::TextBox box =  textBox->getCiTextBoxCopy();
	//        box.setText(newText);
	//        textBox->setCiTextBox(box);
	//
	//    }

}



#endif /* poHelper_hpp */