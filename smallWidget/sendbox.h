#ifndef SENDBOX_H
#define SENDBOX_H

#include <QWidget>
#include <QImage>
#include <QPixmap>
#include <QString>
#include <QColor>
#include <QPalette>
#include <QPainterPath>
#include <QRegion>
#include <QPaintEngine>

namespace Ui {
class SendBox;
}

class SendBox : public QWidget
{
    Q_OBJECT

public:
    explicit SendBox(QWidget *parent = nullptr);
    ~SendBox();

public:
    void setTextColor(const QColor& textcolor);
    void setBackgroundColor(const QColor& backgroundcolor);
    void setBordetRadius(const int radius);
    void setStyleSheet(const QString& style);

public slots:
    void setAvatar(const QPixmap& avtar);
    void setText(const QString& text);


private:
    Ui::SendBox *ui;
};

#endif // SENDBOX_H
