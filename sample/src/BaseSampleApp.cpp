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
    std::string url = "https://wp-assets-sh.imgix.net/sites/787/2018/02/mini7.jpg";
    CACHE()->getSurfaceByUrl(url, "cacheKey" , [=] (HttpSurfaceLoadEvent event){
        
        mTexture = gl::Texture::create(*event.response);
    });
        
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
		//GS()->debugMode.setValue(!GS()->debugMode.value());
	}
	else if (event.getCode() == event.KEY_f) {
		setFullScreen(!isFullScreen());
	}
	else if (event.getCode() == event.KEY_s) {
		//GS()->mSettingManager.writeSettings();
	}

}


void BaseSampleApp::update()
{
    CACHE()->update();
}

void BaseSampleApp::draw()
{
    if(mTexture){
        gl::draw(mTexture);
    }

}

CINDER_APP(BaseSampleApp, RendererGl(RendererGl::Options().msaa(2)), [](App::Settings* settings) {
	//settings->setWindowSize(3840, 1400);
})
