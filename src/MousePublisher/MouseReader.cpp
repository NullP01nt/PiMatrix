#include "MouseReader.h"

MouseReader::MouseReader():
    event(),
    settings(QSettings::NativeFormat, QSettings::UserScope, ORG_NAME, APP_NAME)
{
	loadSettings();
}

MouseReader::~MouseReader(void) {
	QThread::terminate();
}

void MouseReader::loadSettings(void) {
	device_name  = settings.value("device/mouse","/dev/input/event16").toString().toStdString();
}

void MouseReader::cleanup(void) {
	running = false;
}

void MouseReader::run(){
    std::ifstream file;
    file.open(device_name);

    if(!file.good()){
        throw( std::runtime_error("opening device, do you have permission?") );
    }

	while( file.read(reinterpret_cast<char*>(&event),sizeof(input_event_t)) && running ) {
		emit mouse_event(event);
    }
    file.close();
	return;
}
