#include "encodewindow.h"
#include "ui_encodewindow.h"

EncodeWindow::EncodeWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EncodeWindow)
{
    ui->setupUi(this);
    QPixmap bkgnd(":/img/img/grey2.jpeg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);
    setFixedSize(700,300);
}

EncodeWindow::~EncodeWindow()
{
    delete ui;
}

void EncodeWindow::on_pushButton_clicked()
{
    window_showmessages = new ShowMessages(this);
    window_showmessages->show();
}

