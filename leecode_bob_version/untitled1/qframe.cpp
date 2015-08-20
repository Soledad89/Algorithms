#include "qframe.h"
#include "ui_qframe.h"

QFrame::QFrame(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QFrame)
{
    ui->setupUi(this);
}

QFrame::~QFrame()
{
    delete ui;
}
