#include "include/UI/CustomWebView.h"
#include "qcoreevent.h"

CustomWebView::CustomWebView(QWidget *parent) : QWebEngineView(parent), childObj(nullptr) {

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
    if (obj == childObj && (ev->type() == QEvent::MouseButtonPress || ev->type() == QEvent::MouseButtonDblClick
                            || ev->type() == QEvent::KeyPress)) {
        qDebug() << ev->type();
        bool result =  QWebEngineView::eventFilter(obj, ev);
        emit playerStateMightChanged();
        return result;
    }
    return QWebEngineView::eventFilter(obj, ev);

}


CustomWebView::~CustomWebView() {
    delete childObj;
}
