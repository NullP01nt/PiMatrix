// Std includes

// Qt includes
#include <QObject>
#include <QCoreApplication>

// SDU-EMB4 includes
#include "QPubApp.h"
#include <joystick.h>
#include "JoystickReader.h"

/**
 * Input Server application.
 * Reads the device input for a mouse and controller.
 * mouse_reader and gamepad_reader reads the device files in seperate threads.
 * publisher receives QtSignals with the package and sends it over ZMQ
 */

#include <signal.h>
#include <unistd.h>

void catchUnixSignals(const std::vector<int>& quitSignals, const std::vector<int>& ignoreSignals = std::vector<int>()) {
	auto handler = [](int sig) ->void {
		QPubApp::quit();
	};

	// all these signals will be ignored.
	for ( int sig : ignoreSignals )
		signal(sig, SIG_IGN);
	// each of these signals calls the handler (quits the QCoreApplication).
	for ( int sig : quitSignals )
		signal(sig, handler);
}

int main(int argc, char* argv[]){
    QPubApp a(argc,argv);
	catchUnixSignals({SIGQUIT, SIGINT, SIGTERM, SIGHUP});
    return a.exec();
}
