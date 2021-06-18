#include "showkeys.h"
#include "ui_showkeys.h"

ShowKeys::ShowKeys(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShowKeys)
{
    ui->setupUi(this);
    QPixmap bkgnd(":/img/img/grey2.jpeg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);
    setFixedSize(400,300);
}

ShowKeys::~ShowKeys()
{
    delete ui;
}
