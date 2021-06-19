#include "showmessages.h"
#include "ui_showmessages.h"

ShowMessages::ShowMessages(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShowMessages)
{
    ui->setupUi(this);
    QPixmap bkgnd(":/img/img/grey2.jpeg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);
    setFixedSize(400,300);
}

ShowMessages::~ShowMessages()
{
    delete ui;
}
