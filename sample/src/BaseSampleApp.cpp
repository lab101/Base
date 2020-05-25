#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/Log.h"
#include "cinder/Surface.h"
//#include "GlobalSettings.h"
#include "../../src/AssetsCache.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class BaseSampleApp : public App {
public:
	void setup() override;
	void setupLogging();
	void keyDown(KeyEvent event) override;
	void update() override;
	void draw() override;

private:
    ci::gl::TextureRef mTexture = nullptr;
};

std::string const appName = "BaseSampleApp";


void BaseSampleApp::setup()
{

//    GS()->setup(appName);
    setupLogging();

        
    CACHE()->start();
}


void BaseSampleApp::setupLogging() {

//    log::LoggerSystem().setLoggingLevel(log::LEVEL_WARNING);
//
//    // LOGGING to screen (notifications) and disk
//    std::string const logFolder = ci::getDocumentsDirectory().string() + "/logs";
//    if (!ci::fs::exists(logFolder)) {
//        ci::fs::create_directory(logFolder);
//    }
//
//    ci::log::makeLogger<ci::log::LoggerFileRotating>(logFolder, appName + ".%Y.%m.%d.log", true);
}


void BaseSampleApp::keyDown(KeyEvent event)
{
	if (event.getChar() == 'd') {
        std::string url = "https://wp-assets-sh.imgix.net/sites/787/2018/02/mini7.jpg";

        CACHE()->getCachedTextureAsync(url, "fdsf" , [=] (gl::TextureRef event){
            mTexture = event;
        });
	}
	else if (event.getCode() == event.KEY_f) {
		setFullScreen(!isFullScreen());
	}
	else if (event.getCode() == event.KEY_SPACE) {
        std::string url = "/home/lab101/Pictures/test.png";
        CACHE()->getCachedTextureAsync(url, "cacheKey45" , [=] (gl::TextureRef event){
            mTexture = event;
        });
	}



}


void BaseSampleApp::update()
{
    CACHE()->update();
}

void BaseSampleApp::draw()
{
    gl::clear();
    if(mTexture){
        gl::draw(mTexture);
    }

    gl::drawString(to_string(app::getElapsedSeconds()), vec2(200,200));

}

CINDER_APP(BaseSampleApp, RendererGl(RendererGl::Options().msaa(2)), [](App::Settings* settings) {
	//settings->setWindowSize(3840, 1400);
})
