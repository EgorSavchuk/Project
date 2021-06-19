#ifndef ENCODEWINDOW_H
#define ENCODEWINDOW_H

#include <QDialog>
#include "showmessages.h"

namespace Ui {
class EncodeWindow;
}

class EncodeWindow : public QDialog
{
    Q_OBJECT

public:
    explicit EncodeWindow(QWidget *parent = nullptr);
    ~EncodeWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::EncodeWindow *ui;
    ShowMessages *window_showmessages;

};

#endif // ENCODEWINDOW_H