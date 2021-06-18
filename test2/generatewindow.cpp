#include "generatewindow.h"
#include "ui_generatewindow.h"
#include "showkeys.h"

GenerateWindow::GenerateWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GenerateWindow)
{
    ui->setupUi(this);
    QPixmap bkgnd(":/img/img/grey2.jpeg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);
    setFixedSize(600,250);
}

GenerateWindow::~GenerateWindow()
{
    delete ui;
}

void GenerateWindow::on_pushButton_Generate_Keys_clicked()
{
    ShowKeys window4;
    window4.setModal(true);
    window4.exec();
}




