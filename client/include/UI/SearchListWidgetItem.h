#ifndef SEARCHLISTWIDGETITEM_H
#define SEARCHLISTWIDGETITEM_H

#include <QWidget>

namespace Ui {
class SearchListWidgetItem;
}

class SearchListWidgetItem : public QWidget
{
    Q_OBJECT

public:
    explicit SearchListWidgetItem(QWidget *parent = nullptr);
    ~SearchListWidgetItem();

    void setHeaderText(const char *);
    void setPreviewImage(const char *);
    void setDescription(const char *);
    void setVideoLink(const char *);
private:
    Ui::SearchListWidgetItem *ui;
};

#endif // SEARCHLISTWIDGETITEM_H
