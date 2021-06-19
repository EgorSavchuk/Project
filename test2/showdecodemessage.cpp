#include "showdecodemessage.h"
#include "ui_showdecodemessage.h"

ShowDecodeMessage::ShowDecodeMessage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShowDecodeMessage)
{
    ui->setupUi(this);
    QPixmap bkgnd(":/img/img/grey2.jpeg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);
    setFixedSize(400,300);
}

ShowDecodeMessage::~ShowDecodeMessage()
{
    delete ui;
}
