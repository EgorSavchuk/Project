#include "showdecodemessages.h"
#include "ui_showdecodemessages.h"

ShowDecodeMessages::ShowDecodeMessages(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShowDecodeMessages)
{
    ui->setupUi(this);
}

ShowDecodeMessages::~ShowDecodeMessages()
{
    delete ui;
}
