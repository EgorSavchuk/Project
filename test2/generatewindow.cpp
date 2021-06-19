#include "generatewindow.h"
#include "ui_generatewindow.h"
#include "showkeys.h"
#include <fstream>
#include <iostream>
#include "Keygen.h"


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

    PublicKey publickey;
    PrivateKey privatekey;

    if ( ui->radioButton_savefile->isChecked() and ui->radioButton_1024->isChecked()){
        QString directory = ui->lineEdit->text();
        std::string dir = directory.toStdString();
        std::ofstream fout;
        std::string name_of_publickey = "publickey.txt";
        std::string name_of_privatekey = "privatekey.txt";
        std::string dir_for_pub = dir + name_of_publickey;
        std::string dir_for_pr = dir + name_of_privatekey;
        int x = 1024;
        publickey = GenerationPublicKey(x);
        privatekey =  GenerationPrivateKey(x);
        fout.open(dir_for_pub);
        int i = 0;
        if ( fout.is_open()){
            fout << publickey.e << " " << publickey.n;
            i++;
        }
        std::ofstream gout;
        gout.open(dir_for_pr);
        if ( gout.is_open()){
            gout << privatekey.d << " " << privatekey.n;
            i++;
        }
        if ( i == 2){
            //ui->pushButton_Generate_Keys->setEnabled(false);
            ui->pushButton_Generate_Keys->setText("Ключи сгенерированы");
        }
        }
    if ( ui->radioButton_savefile->isChecked() and ui->radioButton_512->isChecked()){
        QString directory = ui->lineEdit->text();
        std::string dir = directory.toStdString();
        std::ofstream fout;
        std::string name_of_publickey = "publickey.txt";
        std::string name_of_privatekey = "privatekey.txt";
        std::string dir_for_pub = dir + name_of_publickey;
        std::string dir_for_pr = dir + name_of_privatekey;
        int x = 512;
        publickey = GenerationPublicKey(x);
        privatekey =  GenerationPrivateKey(x);
        fout.open(dir_for_pub);
        int i = 0;
        if ( fout.is_open()){
            fout << publickey.e << " " << publickey.n;
            i++;
        }
        std::ofstream gout;
        gout.open(dir_for_pr);
        if ( gout.is_open()){
            gout << privatekey.d << " " << privatekey.n;
            i++;
        }
        if ( i == 2){
            ui->pushButton_Generate_Keys->setEnabled(false);
            ui->pushButton_Generate_Keys->setText("Ключи сгенерированы");
        }
        }

        if (ui->radioButton_show->isChecked() and ui->radioButton_1024->isChecked()){
            ShowKeys window4;
            window4.setModal(true);
            SetBitSize(1024);
            window4.exec();

}
        if (ui->radioButton_show->isChecked() and ui->radioButton_512->isChecked()){
            ShowKeys window4;
            window4.setModal(true);
            SetBitSize(512);
            window4.exec();
        }
}

