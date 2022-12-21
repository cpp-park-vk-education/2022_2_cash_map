#include "include/UI/CustomWebView.h"
#include "qcoreevent.h"

CustomWebView::CustomWebView(QWidget *parent) : QWebEngineView(parent), childObj(nullptr) {
    qDebug() << "webEngine started";
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
    // qDebug() << ev->type();
    if (obj == childObj && ev->type() == QEvent::MouseButtonPress) {
        qDebug() << ev->type();
        bool result =  QWebEngineView::eventFilter(obj, ev);
        emit playerStateMightChanged();
        return result;
    } else if (obj == childObj && ev->type() == QEvent::KeyPress) {
        qDebug() << ev->type();
        bool result =  QWebEngineView::eventFilter(obj, ev);
        emit playerStateMightChanged();
        return result;
    } else if (obj == childObj && ev->type() == QEvent::InputMethodQuery) {
        qDebug() << ev->type();
        bool result =  QWebEngineView::eventFilter(obj, ev);
        emit playerStateMightChanged();
        return result;
    }

    return QWebEngineView::eventFilter(obj, ev);

}


CustomWebView::~CustomWebView() {}
