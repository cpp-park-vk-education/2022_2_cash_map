#include "include/UI/CustomWebView.h"
#include "qcoreevent.h"

CustomWebView::CustomWebView(QWidget *parent) : QWebEngineView(parent), childObj(nullptr) {
    connect(&timer, SIGNAL(timeout()), this, SLOT(sendSignal()));
}

void CustomWebView::sendSignal() {
    emit playerStateMightChanged();
    timer.stop();
}

bool CustomWebView::event(QEvent* event) {

    if (event->type() == QEvent::ChildPolished) {
        QChildEvent *childEvent = static_cast<QChildEvent*>(event);
        childObj = childEvent->child();

        if (childObj) {
            childObj->installEventFilter(this);
        }
    }

    return QWebEngineView::event(event);
}

bool CustomWebView::eventFilter(QObject *obj, QEvent *ev) {
    if (obj == childObj && ev->type() == QEvent::MouseButtonRelease) {
        bool result =  QWebEngineView::eventFilter(obj, ev);
        timer.start(200);
        return result;
    } else if (obj == childObj && ev->type() == QEvent::KeyPress) {
        qDebug() << ev->type();
        bool result =  QWebEngineView::eventFilter(obj, ev);
        timer.start(200);
        return result;
    }

    return QWebEngineView::eventFilter(obj, ev);

}


CustomWebView::~CustomWebView() {}
