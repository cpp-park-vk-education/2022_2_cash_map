#ifndef CHATMESSAGEWIDGET_H
#define CHATMESSAGEWIDGET_H

#include <QWidget>

namespace Ui {
class ChatMessageWidget;
}

class ChatMessageWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ChatMessageWidget(const QString &sender, const QString &message, const QString &time, QWidget *parent = nullptr);
    ~ChatMessageWidget();

private:
    Ui::ChatMessageWidget *ui;
};

#endif // CHATMESSAGEWIDGET_H
