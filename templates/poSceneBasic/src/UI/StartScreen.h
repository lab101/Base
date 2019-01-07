#pragma once

#include "poScene/ImageView.h"
#include "poScene/TextView.h"

namespace lab101{

	class  StartScreen;
	typedef std::shared_ptr<StartScreen> StartScreenRef;


	class StartScreen : public po::scene::View{

		po::scene::ImageViewRef mDemoImage;
		po::scene::TextViewRef mDemoText;


	public:
		static StartScreenRef create();

		void setup();
		void update();
	};

}