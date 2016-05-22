#include "JoystickReader.h"

JoystickReader::JoystickReader(void) :
	m_event(),
	event(),
	settings(QSettings::NativeFormat, QSettings::UserScope, ORG_NAME, APP_NAME),
	device_name( settings.value("device/joystick","/dev/input/js0").toString().toStdString() )
{

}

void JoystickReader::run(){
    std::ifstream file;
    file.open(device_name);

    if(!file.good()){
        throw( std::runtime_error("opening device, do you have permission?") );
    }

    uint32_t topic_number = 0x4C525443; //not sure what should be here
    memcpy(m_event.topic, &topic_number,4);
    m_event.dev_type  = DEV_TYPE_JOYSTICK; // Joystick
    m_event.dev_model = JOYSTICK_PS3; // Playstation3
    while( file.read(reinterpret_cast<char*>(&event),sizeof(struct input_event)) ) {

        m_event.ev_type   = event.type;
        m_event.ev_code   = event.code;
        m_event.ev_value  = event.value;
        emit joystick_event(reinterpret_cast<void*>(&m_event));
    }
    file.close();
    QThread::exit();
}
