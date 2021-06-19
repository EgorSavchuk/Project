#ifndef SHOWKEYS_H
#define SHOWKEYS_H

#include <QDialog>

namespace Ui {
    class ShowKeys;
}

class ShowKeys : public QDialog {
Q_OBJECT

public:
    explicit ShowKeys(QWidget *parent = nullptr);

    ~ShowKeys();

private:
    Ui::ShowKeys *ui;
};

#endif // SHOWKEYS_H
