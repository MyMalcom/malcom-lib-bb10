// Default empty project template
#include "MalcomLibBb10.hpp"

#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <QVariantList>

#include "MCMNotification.hpp"

using namespace bb::cascades;

//	PROD
//const QString uuidMalcom = "a1026807-e078-4d1d-bb3d-d618c1dbc8f7"; // SET YOUR MALCOM UUID
//const QString secretKeyMalcom = "c1971A7hcwzDOjrjzwUoaQ=="; //	SET YOUR MALCOM SECRET KEY

//	PRE
const QString uuidMalcom = "675ab455-bcb8-47ef-8a7d-3bdc0c88fbde"; // SET YOUR MALCOM UUID
const QString secretKeyMalcom = "Qw7E3oYy9FFtOze84W3TrA=="; //	SET YOUR MALCOM SECRET KEY


MalcomLibBb10::MalcomLibBb10(bb::cascades::Application *app)
: QObject(app)
{
    // create scene document from main.qml asset
    // set parent to created document to ensure it exists for the whole application lifetime
    QmlDocument *qml = QmlDocument::create("asset:///main.qml").parent(this);

    connect(app, SIGNAL(fullscreen()), this, SLOT(onFullscreen()));
    connect(app, SIGNAL(thumbnail()), this, SLOT(onThumbnail()));

    root = qml->createRootObject<AbstractPane>();

    MalcomLib::Instance() -> initMalcom(uuidMalcom, secretKeyMalcom);

    QVariantList tags;
    tags << "tag1" << "tag2" << "tag3" << "tag4";

    MalcomLib::Instance() -> setTags(tags);

    QDeclarativePropertyMap malcom;
    malcom.insert("uuid", uuidMalcom);
    malcom.insert("secretKey", secretKeyMalcom);

    qml->setContextProperty("malcom", &malcom);

    // create root object for the UI
    AbstractPane *root = qml->createRootObject<AbstractPane>();
    // set created root object as a scene
    app->setScene(root);
}

MalcomLibBb10::MalcomLibBb10() {


}

void MalcomLibBb10::onFullscreen() {
	MalcomLib::Instance() -> initAndStartBeacon();
	MCMNotification::Instance() -> registerDevice();
}

void MalcomLibBb10::onThumbnail() {
	MalcomLib::Instance() ->endBeacon();
}
