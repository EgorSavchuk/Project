#ifndef DECODEWINDOW_H
#define DECODEWINDOW_H

#include <QDialog>
#include <QMovie>
#include "showdecodemessage.h"

namespace Ui {
class DecodeWindow;
}

class DecodeWindow : public QDialog
{
    Q_OBJECT

public:
    explicit DecodeWindow(QWidget *parent = nullptr);
    ~DecodeWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::DecodeWindow *ui;
    QMovie deo;

};

#endif // DECODEWINDOW_H
