#ifndef VIDEOWATCHEREVENTHANDLER_H
#define VIDEOWATCHEREVENTHANDLER_H

#include <QObject>

namespace Ui {
class VideoWatcherEventHandler;
}

class VideoWatcherEventHandler : public QObject
{
    Q_OBJECT

protected:
    bool eventFilter(QObject* obj, QEvent* event);
};

#endif // VIDEOWATCHEREVENTHANDLER_H
