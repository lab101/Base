#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/Log.h"
#include "cinder/Surface.h"
#include "cinder/Base64.h"
//#include "GlobalSettings.h"
#include "../../src/AssetLoader/AssetsCache.h"

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
    int requestCount = 0;
};

std::string const appName = "BaseSampleApp";


void BaseSampleApp::setup()
{

//    GS()->setup(appName);
    setupLogging();

        
    CACHE()->start();
    
    httplib::Client cli("amazone.lab101.be",4000);

    //auto cli = httplib::Client2("http://amazone.lab101.be:4000");
    
    cli.set_connection_timeout(0.5,0);
    auto res = cli.Get("/IMG_0933.JPG");

    
  //  auto res = cli.Get("");
    if (res && res->status == 200) {
      //  std::cout << res->body << std::endl;
        
        //Buffer b = ;
       // BufferRef bb = make_shared<Buffer>(( res->body ));
        //BufferRef bb = Buffer::create(b, b.getSize());
        //auto dd = DataSourceBuffer::create(bb);
       // Buffer ere = fromBase64( res->body );
        //DataSourceBufferRef dataSourceBuffer = DataSourceBuffer::create( ere );

        
     //   auto dataSource = loadFile( "" );
      //  auto buffer = dataSource->getBuffer();
        //DataSourceBufferRef dataSourceBuffer = DataSourceBuffer::create( bb );
        auto b =  Buffer::create( res->body.size());
        memcpy( b->getData(), res->body.data(), b->getSize() );
        
     //   auto dataSource = loa
        //auto buffer = dataSource->getBuffer();
        DataSourceBufferRef dataSourceBuffer = DataSourceBuffer::create( b );
      //  ci::DataSourceBuffer::create(res->body);
        auto image = loadImage( dataSourceBuffer );
        auto surf = Surface::create(image);
        mTexture = ci::gl::Texture::create(*surf);
        //auto image = loadImage( res->body );
        
        //auto img  = ci::loadImage();
        //auto s = loadImage(load (res->body);
     //   auto surf = Surface::create(res->body, 300, 300,3,SurfaceChannelOrder::RGB);
    }
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
	if (event.getChar() == '1') {
        std::string url = "http://amazone.lab101.be:3000/?id=54bb916d480a2d844cd72326&type=library&lang=NL";

        requestCount++;

        CACHE()->getCachedTextureAsync(url, "nasss" +to_string(ci::app::getElapsedSeconds()) , [=] (gl::TextureRef event){
            requestCount--;
            mTexture = event;
        });
	}
    else if (event.getChar() == '2') {

        std::string url = "http://amazone.lab101.be:4000/IMG_0933.JPG";
        
        requestCount++;
        
        CACHE()->getCachedTextureAsync(url, "fdfsdfs" +to_string(ci::app::getElapsedSeconds())  , [=] (gl::TextureRef event){
            requestCount--;
            mTexture = event;
        });
        
	//	setFullScreen(!isFullScreen());
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
        gl::draw(mTexture,ci::Rectf(0,0,getWindowWidth(),getWindowWidth()));
    }

    const float centerX = getWindowWidth() * 0.5;
    gl::drawSolidCircle(vec2(centerX + (sin(getElapsedSeconds()) * centerX),getWindowWidth() * 0.5),20);
    gl::drawString(to_string(app::getElapsedSeconds()), vec2(200,200));
    gl::drawString(to_string(requestCount), vec2(200,230));
    gl::drawString(to_string(CACHE()->getQueueSize()), vec2(200,260));


}

CINDER_APP(BaseSampleApp, RendererGl(RendererGl::Options().msaa(2)), [](App::Settings* settings) {
	//settings->setWindowSize(3840, 1400);
})
