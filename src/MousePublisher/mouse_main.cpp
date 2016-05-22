// Std includes

// Qt includes
#include <QObject>
#include <QCoreApplication>

// SDU-EMB4 includes
#include <mouse.h>
#include "QPubApp.h"
#include "MouseReader.h"

#include <signal.h>
#include <unistd.h>

void catchUnixSignals(const std::vector<int>& quitSignals, const std::vector<int>& ignoreSignals = std::vector<int>()) {
	auto handler = [](int sig) ->void {
		QPubApp::quit();
	};

	for(int sig : ignoreSignals )
		signal(sig, SIG_IGN);
	for(int sig : quitSignals )
		signal(sig, handler);
}

Q_DECLARE_METATYPE( input_event_t )

int main(int argc, char* argv[]){

    qRegisterMetaType<input_event_t>();
    QPubApp a(argc,argv);

    MouseReader mouse;

    QObject::connect(&mouse,SIGNAL(mouse_event(input_event_t)),&a,SLOT(new_input(input_event_t)));
	mouse.start();

	catchUnixSignals({SIGQUIT, SIGINT, SIGTERM, SIGHUP});

    return a.exec();
}
