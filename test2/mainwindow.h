#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <Qmovie>
#include "encodewindow.h"
#include "decodewindow.h"
#include "generatewindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_pushButton_generate_clicked();

    void on_pushButton_encode_clicked();

    void on_pushButton_decode_clicked();


    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    EncodeWindow *window_encode;
    DecodeWindow *window_decode;
    GenerateWindow *window_generate;
    QMovie mo;
    double m;

};
#endif // MAINWINDOW_H
