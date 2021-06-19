#include "encodewindow.h"
#include "ui_encodewindow.h"
#include <string>
#include <boost/multiprecision/cpp_int.hpp>
#include "Keygen.h"


EncodeWindow::EncodeWindow(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::EncodeWindow) {
    ui->setupUi(this);
    eo.setFileName(":/img/img/code10.gif");
    ui->label->setMovie(&eo);
    eo.start();
    setFixedSize(700, 300);


}

EncodeWindow::~EncodeWindow() {
    delete ui;
}

void EncodeWindow::on_pushButton_clicked() {
    if (ui->radioButton_introducedkey->isChecked()) {

        QString introduced_key = ui->plainTextEdit->toPlainText();
        std::string for_key = introduced_key.toStdString();
        std::string e;
        std::string n;
        bool b = 1;
        for (const char &i : for_key) {
            if (i == '/') {
                b = 0;
                continue;
            }
            (b ? e += i : n += i);
        }
        boost::multiprecision::cpp_int E_for_encode(e);
        boost::multiprecision::cpp_int N_for_encode(n);
        PublicKeys keys_for_encode = {E_for_encode, N_for_encode};
        QString mfe = ui->plainTextEdit_3->toPlainText();
        std::string message_for_encode = mfe.toStdString();
        std::string result_encoding = Encryption(message_for_encode, keys_for_encode);
        QString result = QString::fromStdString(result_encoding);
        ui->plainTextEdit_3->clear();
        ui->plainTextEdit_3->insertPlainText(result);
        ui->pushButton->setEnabled(false);
        ui->pushButton->setText("Сообщение зашифровано");
    }


    if (ui->radioButton_fromfile->isChecked()) {
        QString ne = ui->plainTextEdit_2->toPlainText();
        std::string name_of_file_for_encode = ne.toStdString();
        PublicKeys keys_for_encoding = PublicKeysReading(name_of_file_for_encode);
        QString mfe = ui->plainTextEdit_3->toPlainText();
        std::string message_for_encode = mfe.toStdString();
        std::string result_encoding = Encryption(message_for_encode, keys_for_encoding);
        QString result = QString::fromStdString(result_encoding);
        ui->plainTextEdit_3->clear();
        ui->plainTextEdit_3->insertPlainText(result);
        ui->pushButton->setEnabled(false);
        ui->pushButton->setText("Сообщение зашифровано");


    }
}

