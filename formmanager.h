#ifndef FORMMANAGER_H
#define FORMMANAGER_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class Formmanager;
}
QT_END_NAMESPACE

class Formmanager : public QWidget
{
    Q_OBJECT

public:
    Formmanager(QWidget *parent = nullptr);
    ~Formmanager();

private:
    Ui::Formmanager *ui;
};
#endif // FORMMANAGER_H
