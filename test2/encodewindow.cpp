#include "encodewindow.h"
#include "ui_encodewindow.h"
#include <fstream>
#include <boost/multiprecision/cpp_int.hpp>
#include "Keygen.h"


using namespace std;

PublicKeys PublicKeysReading(string name) {
    ifstream input(name);
    boost::multiprecision::cpp_int E;
    boost::multiprecision::cpp_int n;
    input >> E;
    input >> n;
    PublicKeys keys = {E, n};
    return keys;
}


/**Шифрует число*/
boost::multiprecision::cpp_int EncryptionNum(const boost::multiprecision::cpp_int& num, const PublicKeys& keys) {
    return modexp(num, keys.E, keys.n);
}

string Encryption(const string& message, const PublicKeys& keys) {
    string x = "";
    int ch = 0;
    ostringstream ss;
    ostringstream ss2;
    ss << setfill('0');
    for (const char& i : message) {
        x = to_string((int)i);
        ss << setw(4) << x;
        ch++;
        if (ch == 100) {
            string str = '1' + ss.str();
            ss.str("");
            ss.clear();
            boost::multiprecision::cpp_int res(str);
            ss2 << EncryptionNum(res, keys) << ' ';
            ch = 0;
        }
    }
    if (ch != 0) {
        string str = '1' + ss.str();
        boost::multiprecision::cpp_int res(str);
        ss2 << EncryptionNum(res, keys);
    }
    string result = ss2.str();
    return result;
}
EncodeWindow::EncodeWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EncodeWindow)
{
    ui->setupUi(this);
    /*QPixmap bkgnd(":/img/img/grey2.jpeg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);*/
    eo.setFileName(":/img/img/code10.gif");
    ui->label->setMovie(&eo);
    eo.start();
    setFixedSize(700,300);


}

EncodeWindow::~EncodeWindow()
{
    delete ui;
}

void EncodeWindow::on_pushButton_clicked()
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
        PublicKeys keys_for_encode = {E_for_encode, N_for_encode};
        QString mfe = ui->plainTextEdit_3->toPlainText();
        std::string message_for_encode = mfe.toStdString();
        std:: string result_encoding = Encryption(message_for_encode, keys_for_encode);
        QString result = QString::fromStdString(result_encoding);
        ui->plainTextEdit_3->clear();
        ui->plainTextEdit_3->insertPlainText(result);
        ui->pushButton->setEnabled(false);
        ui->pushButton->setText("Сообщение зашифровано");
        }









    if(ui->radioButton_fromfile->isChecked()){
        QString ne = ui->plainTextEdit_2->toPlainText();
        std::string name_of_file_for_encode = ne.toStdString();
        PublicKeys keys_for_encoding = PublicKeysReading(name_of_file_for_encode);
        QString mfe = ui->plainTextEdit_3->toPlainText();
        std::string message_for_encode = mfe.toStdString();
        std:: string result_encoding = Encryption(message_for_encode, keys_for_encoding);
        QString result = QString::fromStdString(result_encoding);
        ui->plainTextEdit_3->clear();
        ui->plainTextEdit_3->insertPlainText(result);
        ui->pushButton->setEnabled(false);
        ui->pushButton->setText("Сообщение зашифровано");


    }
}

