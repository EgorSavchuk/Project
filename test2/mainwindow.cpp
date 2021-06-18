#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "generatewindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
       /*QPixmap bkgnd(":/img/img/2code.gif");
       bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
       QPalette palette;
       palette.setBrush(QPalette::Window, bkgnd);
       this->setPalette(palette);*/
       setFixedSize(400,500);
       mo.setFileName(":/img/img/code5.gif");
       ui->label->setMovie(&mo);
       mo.start();


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_generate_clicked()
{
    GenerateWindow window;
    window.setModal(true);
    window.exec();
}


void MainWindow::on_pushButton_encode_clicked()
{
    window_encode = new EncodeWindow(this);
    window_encode->show();
}


void MainWindow::on_pushButton_decode_clicked()
{
    window_decode = new DecodeWindow(this);
    window_decode->show();
}


