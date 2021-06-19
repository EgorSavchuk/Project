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
    setFixedSize(600,200);
}

GenerateWindow::~GenerateWindow()
{
    delete ui;
}


void GenerateWindow::on_pushButton_Generate_Keys_clicked()
{


    if ( ui->radioButton_savefile->isChecked()){
        QString directory = ui->lineEdit->text();
        std::string dir = directory.toStdString();
        std::string name_of_publickey = "publickey.txt";
        std::string name_of_privatekey = "privatekey.txt";
        std::string dir_for_pub = dir + name_of_publickey;
        std::string dir_for_pr = dir + name_of_privatekey;
        keys all_keys = newkeys();
        std::ofstream fout;
        fout.open(dir_for_pub);
        int i = 0;
        if ( fout.is_open()){
            fout << all_keys.E << " " << all_keys.n;
            i++;
        }
        std::ofstream gout;
        gout.open(dir_for_pr);
        if ( gout.is_open()){
            gout << all_keys.D << " " << all_keys.n;
            i++;
        }
        if ( i == 2){
            ui->pushButton_Generate_Keys->setEnabled(false);
            ui->pushButton_Generate_Keys->setText("Ключи сгенерированы");
        }
        }

        if (ui->radioButton_show->isChecked()){
            window_show = new ShowKeys(this);
            window_show->show();

}

}

