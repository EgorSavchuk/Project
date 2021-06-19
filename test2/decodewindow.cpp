#include "decodewindow.h"
#include "ui_decodewindow.h"
#include <boost/multiprecision/cpp_int.hpp>
#include <fstream>
#include "Keygen.h"

using namespace std;


/**Дешифрует число*/
boost::multiprecision::cpp_int DecryptionNum(const boost::multiprecision::cpp_int& num, const PrivateKeys& keys) {
    return modexp(num, keys.D, keys.n);
}

string Decryption(string message, const PrivateKeys& keys) {
    string num = "";
    string result = "";
    ostringstream ss;
    message += ' ';
    ss.str("");
    ss.clear();
    for (const char& i : message) {
        if (i != ' ') {
            num += i;
        }
        else {
            boost::multiprecision::cpp_int res(num);
            num = "";
            ss << DecryptionNum(res, keys);
            string preres = ss.str();
            ss.str("");
            ss.clear();
            preres.erase(0, 1);
            int ch = 0;
            string tmp = "";
            for (const char& j : preres) {
                tmp += j;
                ch++;
                if (ch == 4) {
                    char t = stoi(tmp);
                    tmp = "";
                    ch = 0;
                    result += t;
                }
            }
        }
    }
    return result;
}

PrivateKeys PrivateKeysReading(string name) {
    ifstream input(name);
    boost::multiprecision::cpp_int D;
    boost::multiprecision::cpp_int n;
    input >> D;
    input >> n;
    PrivateKeys keys = {D, n};
    return keys;
}


DecodeWindow::DecodeWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DecodeWindow)
{
    ui->setupUi(this);
    /*QPixmap bkgnd(":/img/img/grey2.jpeg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);*/
    deo.setFileName(":/img/img/code10.gif");
    ui->label->setMovie(&deo);
    deo.start();
    setFixedSize(700,300);
}

DecodeWindow::~DecodeWindow()
{
    delete ui;
}

void DecodeWindow::on_pushButton_clicked()
{
    if (ui->radioButton_introducedkey->isChecked()){
        QString introduced_key = ui->plainTextEdit->toPlainText();
        std::string for_key = introduced_key.toStdString();
        std::string e;
        std::string n;
        bool b = 1;
        for(const char& i : for_key) {
        if (i == ' ') {
        b = 0;
        continue;
        }
        (b ? e += i : n += i);
        }
        boost::multiprecision::cpp_int E_for_encode(e);
        boost::multiprecision::cpp_int N_for_encode(n);
        PrivateKeys keys_for_encode = {E_for_encode, N_for_encode};
        QString mfe = ui->plainTextEdit_3->toPlainText();
        std::string message_for_encode = mfe.toStdString();
        std:: string result_encoding = Decryption(message_for_encode, keys_for_encode);
        QString result = QString::fromStdString(result_encoding);
        ui->plainTextEdit_3->clear();
        ui->plainTextEdit_3->insertPlainText(result);
        ui->pushButton->setEnabled(false);
        ui->pushButton->setText("Сообщение дешифровано");
        }

    if(ui->radioButton_fromfile->isChecked()){
        QString ne = ui->plainTextEdit_2->toPlainText();
        std::string name_of_file_for_decode = ne.toStdString();
        PrivateKeys keys_for_decoding = PrivateKeysReading(name_of_file_for_decode);
        QString mfe = ui->plainTextEdit_3->toPlainText();
        std::string message_for_encode = mfe.toStdString();
        std:: string result_decoding = Decryption(message_for_encode, keys_for_decoding);
        QString result = QString::fromStdString(result_decoding);
        ui->plainTextEdit_3->clear();
        ui->plainTextEdit_3->insertPlainText(result);
        ui->pushButton->setEnabled(false);
        ui->pushButton->setText("Сообщение дешифровано");


    }


}

