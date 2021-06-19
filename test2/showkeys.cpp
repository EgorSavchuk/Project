#include "showkeys.h"
#include "ui_showkeys.h"
#include <string>
#include "Keygen.h"



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
    setFixedSize(400,300);

    PublicKey publickey = GenerationPublicKey(ShowBitSize());
    PrivateKey privatekey = GenerationPrivateKey(ShowBitSize());
    QString e = QString::number(publickey.e);
    QString n = QString::number(publickey.n);
    QString d = QString::number(privatekey.d);

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
