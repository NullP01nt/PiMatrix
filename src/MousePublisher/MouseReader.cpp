#include "MouseReader.h"

MouseReader::MouseReader():
//    m_event(),
    event(),
    settings(QSettings::NativeFormat, QSettings::UserScope, ORG_NAME, APP_NAME)
{
	loadSettings();
}

MouseReader::~MouseReader(void) {

}

void MouseReader::loadSettings(void) {
	device_name  = settings.value("device/mouse","/dev/input/event16").toString().toStdString();
}

#include <iostream>

void MouseReader::run(){
    std::ifstream file;
    file.open(device_name);

	std::cout << device_name << std::endl;

    if(!file.good()){
        throw( std::runtime_error("opening device, do you have permission?") );
    }
//    uint32_t topic_number = 0x4C525443; //not sure what should be here
//    memcpy(m_event.topic, &topic_number,4);
//    m_event.dev_type  = DEV_TYPE_MOUSE; // MOUSE
//    m_event.dev_model = MOUSE_GENERIC; // Generic
    while( file.read(reinterpret_cast<char*>(&event),sizeof(input_event_t)) ) {
		emit mouse_event(event);
//        m_event.ev_type   = event.type;
//        m_event.ev_code   = event.code;
//        m_event.ev_value  = event.value;
//        emit mouse_received(m_event);
    }
    file.close();
    QThread::exit();
}
