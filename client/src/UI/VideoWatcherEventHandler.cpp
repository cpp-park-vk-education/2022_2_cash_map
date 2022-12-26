#include "include/UI/VideoWatcherEventHandler.h"
#include "qcoreevent.h"
#include "qdebug.h"

#include <QMouseEvent>


bool VideoWatcherEventHandler::eventFilter(QObject* obj, QEvent* event) {
    qDebug() << event->type();

    return QObject::eventFilter(obj, event);
}
