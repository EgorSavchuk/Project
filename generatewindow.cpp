#include "generatewindow.h"
#include "ui_generatewindow.h"
#include "showkeys.h"
#include <fstream>
#include <iostream>
#include "Keygen.h"


GenerateWindow::GenerateWindow(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::GenerateWindow) {
    ui->setupUi(this);
    QPixmap bkgnd(":/img/img/grey2.jpeg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);
    setFixedSize(600, 200);
}

GenerateWindow::~GenerateWindow() {
    delete ui;
}


void GenerateWindow::on_pushButton_Generate_Keys_clicked() {


    if (ui->radioButton_savefile->isChecked()) {
        QString directory = ui->lineEdit->text();
        std::string dir = directory.toStdString();
        keys all_keys = newkeys();
        PublicKeys pubkeys = {all_keys.E, all_keys.n};
        PrivateKeys privkeys = {all_keys.D, all_keys.n};
        if (PublicKeysRecording(pubkeys, dir) and PrivateKeysRecording(privkeys, dir)) {
            ui->pushButton_Generate_Keys->setEnabled(false);
            ui->pushButton_Generate_Keys->setText("Ключи сгенерированы");
        }

       }
        if (ui->radioButton_show->isChecked()) {
            window_show = new ShowKeys(this);
            window_show->show();

        }



}
