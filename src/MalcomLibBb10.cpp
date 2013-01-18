// Default empty project template
#include "MalcomLibBb10.hpp"

#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <QVariantList>

using namespace bb::cascades;

const QString uuidMalcom = ""; // SET YOUR MALCOM UUID
const QString secretKeyMalcom = ""; //	SET YOUR MALCOM SECRET KEY

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
}

void MalcomLibBb10::onThumbnail() {
	MalcomLib::Instance() ->endBeacon();
}
