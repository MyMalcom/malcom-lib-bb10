// Default empty project template
#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/AbstractPane>

#include <QLocale>
#include <QTranslator>
#include <Qt/qdeclarativedebug.h>
#include "MalcomLibBb10.hpp"

using namespace bb::cascades;

void messageLogger(QtMsgType type, const char *msg) {
	std::fprintf(stdout, "%s\n", msg);
	std::fflush(stdout);
}

Q_DECL_EXPORT int main(int argc, char **argv)
{
    // this is where the server is started etc
    Application app(argc, argv);

    // The fullscreen signal can be used to determine if the app
    // was launched in the background.

    MalcomLibBb10 mainApp;

    QObject::connect(&app, SIGNAL(fullscreen()), &mainApp, SLOT(onFullscreen()));

    // localization support
    QTranslator translator;
    QString locale_string = QLocale().name();
    QString filename = QString( "malcom_lib_bb10_%1" ).arg( locale_string );
    if (translator.load(filename, "app/native/qm")) {
        app.installTranslator( &translator );
    }

    qInstallMsgHandler(messageLogger);
    new MalcomLibBb10(&app);

    // we complete the transaction started in the app constructor and start the client event loop here
    return Application::exec();
    // when loop is exited the Application deletes the scene which deletes all its children (per qt rules for children)
}
