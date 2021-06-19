
#ifndef GENERATEWINDOW_H
#define GENERATEWINDOW_H

#include <QDialog>

namespace Ui {
class GenerateWindow;
}

class GenerateWindow : public QDialog
{
    Q_OBJECT

public:
    explicit GenerateWindow(QWidget *parent = nullptr);
    ~GenerateWindow();

private slots:
    void on_pushButton_Generate_Keys_clicked();


private:
    Ui::GenerateWindow *ui;
};

#endif // GENERATEWINDOW_H


