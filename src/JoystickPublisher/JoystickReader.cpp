#include "JoystickReader.h"

JoystickReader::JoystickReader(void) :
	event(),
	settings(QSettings::NativeFormat, QSettings::UserScope, ORG_NAME, APP_NAME)
{
	loadSettings();
}

JoystickReader::~JoystickReader(void) {
	QThread::terminate();
}

void JoystickReader::loadSettings(void) {
	device_name = settings.value("device/joystick","/dev/input/js0").toString().toStdString();
}

void JoystickReader::cleanup(void) {
	running = false;
}

void JoystickReader::run(){

    std::ifstream file;
    file.open(device_name);

    if(!file.good()){
        throw( std::runtime_error("opening device, do you have permission?") );
    }

    while( file.read(reinterpret_cast<char*>(&event),sizeof(js_event_t)) && running ) {
        emit joystick_event(event);
    }
    file.close();
	return;
}
