#ifndef RECVBOX_H
#define RECVBOX_H

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
class RecvBox;
}

class RecvBox : public QWidget
{
    Q_OBJECT

public:
    explicit RecvBox(QWidget *parent = nullptr);
    ~RecvBox();

public:
    void setTextColor(const QColor& textcolor);
    void setBackgroundColor(const QColor& backgroundcolor);
    void setBordetRadius(const int radius);
    void setStyleSheet(const QString& style);

public slots:
    void setAvatar(const QPixmap& avtar);
    void setText(const QString& text);

private:
    Ui::RecvBox *ui;
};

#endif // RECVBOX_H
