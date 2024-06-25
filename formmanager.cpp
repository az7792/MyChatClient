#include "formmanager.h"
#include "ui_formmanager.h"

Formmanager::Formmanager(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Formmanager)
{
    ui->setupUi(this);
}

Formmanager::~Formmanager()
{
    delete ui;
}
