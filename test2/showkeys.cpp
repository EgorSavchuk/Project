#include "showkeys.h"
#include "ui_showkeys.h"
#include <Qstring>
#include "Keygen.h"


std::string BigInt2Str(boost::multiprecision::cpp_int inter) {
    std::ostringstream ss;
    ss << inter;
    return ss.str();
}

ShowKeys::ShowKeys(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShowKeys)
{
    ui->setupUi(this);
    QPixmap bkgnd(":/img/img/grey2.jpeg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);
    setFixedSize(600,400);

    keys all_keys = newkeys();
    QString e = QString::fromStdString(BigInt2Str(all_keys.E));
    QString n = QString::fromStdString(BigInt2Str(all_keys.n));
    QString d = QString::fromStdString(BigInt2Str(all_keys.D));


    ui->plainTextEdit_2->insertPlainText(e);
    ui->plainTextEdit_2->insertPlainText(" ");
    ui->plainTextEdit_2->insertPlainText(n);


    ui->plainTextEdit->insertPlainText(d);
    ui->plainTextEdit->insertPlainText(" ");
    ui->plainTextEdit->insertPlainText(n);




}

ShowKeys::~ShowKeys()
{
    delete ui;
}
