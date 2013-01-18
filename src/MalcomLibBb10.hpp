// Default empty project template
#ifndef MalcomLibBb10_HPP_
#define MalcomLibBb10_HPP_

#include <QObject>
#include "malcomLib.hpp"
#include <bb/cascades/AbstractPane>
#include <bb/cascades/TextArea>
#include <bb/cascades/ActivityIndicator>

namespace bb { namespace cascades { class Application; }}

using namespace bb::cascades;

/*!
 * @brief Application pane object
 *
 *Use this object to create and init app UI, to create context objects, to register the new meta types etc.
 */
class MalcomLibBb10 : public QObject
{
    Q_OBJECT
public:
    MalcomLibBb10(bb::cascades::Application *app);
    MalcomLibBb10();
    virtual ~MalcomLibBb10() {}
public slots:
    void onFullscreen();
    void onThumbnail();

private:

    ActivityIndicator *m_activityIndicator;
    TextArea *m_logger;
	AbstractPane *root;
};


#endif /* MalcomLibBb10_HPP_ */
