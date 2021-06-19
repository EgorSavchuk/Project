#include "tmp.h"
#include "ui_tmp.h"

tmp::tmp(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::tmp)
{
    ui->setupUi(this);
}

tmp::~tmp()
{
    delete ui;
}
