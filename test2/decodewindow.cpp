#include "decodewindow.h"
#include "ui_decodewindow.h"

DecodeWindow::DecodeWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DecodeWindow)
{
    ui->setupUi(this);
    QPixmap bkgnd(":/img/img/grey2.jpeg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);
    setFixedSize(700,300);
}

DecodeWindow::~DecodeWindow()
{
    delete ui;
}

void DecodeWindow::on_pushButton_clicked()
{
    window_showdecodemessages = new ShowDecodeMessage(this);
    window_showdecodemessages->show();
}

