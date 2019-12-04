#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

// basic includes
#include "../blocks/Base/src/Settings/SettingController.h"
#include "../blocks/Base/src/Notifications/NotificationManager.h"
#include "../blocks/Base/src/Notifications/NotificationLogger.h"
#include "GlobalSettings.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class _TBOX_PREFIX_App
: public App 
{

	SettingController       mSettingController;

  public:
	void setup() override;
	void update() override;
	void draw() override;
	void keyDown(KeyEvent event) override;

	
	static void prepareSettings(Settings* settings){
		//settings->setConsoleWindowEnabled();
		//settings->setAlwaysOnTop();
	}
  
};

void _TBOX_PREFIX_App::setup()
{

	GS()->setup("_TBOX_PREFIX_App");
	mSettingController.setup(&(GS()->mSettingManager));

// screen setup paramaters
	float const scale = GS()->screenScale.value();

	setWindowSize(GS()->getScreenSize() * scale);
	setWindowPos(vec2(30, 30));

	setFullScreen(GS()->isFullscreen.value());
	if (!GS()->isMouseOn.value()) hideCursor();

	// LOGGING to screen (notifications) and disk
	std::string const logFolder = ci::getDocumentsDirectory().string() + "/logs";
	if (!ci::fs::exists(logFolder)){
		ci::fs::create_directory(logFolder);
	}

	ci::log::makeLogger<NotificationLogger>();
	ci::log::makeLogger<ci::log::LoggerFileRotating>(logFolder, "_TBOX_PREFIX_App.%Y.%m.%d.log", true);
   
}


void _TBOX_PREFIX_App::keyDown(KeyEvent event) {

	if (GS()->debugMode.value() && mSettingController.checkKeyDown(event)) {
		return;
	}
	else if (event.getChar() == 'd'){
		GS()->debugMode.setValue(!GS()->debugMode.value());
	}
	else if (event.getCode() == event.KEY_f){
		setFullScreen(!isFullScreen());
	}
}



void _TBOX_PREFIX_App::update()
{
   
}



void _TBOX_PREFIX_App::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
	
	
	
	
	
	
	// DEBUGGING
	if (GS()->debugMode.value()){
		//gl::ScopedGlslProg shaderScp(gl::getStockShader(gl::ShaderDef().texture().color()));

		ci::gl::color(1, 1, 1);
		mSettingController.draw();
		NotificationManagerSingleton::Instance()->draw();

	}
  
}

CINDER_APP( _TBOX_PREFIX_App, RendererGl(RendererGl::Options().msaa(4)), _TBOX_PREFIX_App::prepareSettings)
