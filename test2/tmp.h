#ifndef TMP_H
#define TMP_H

#include <QWidget>

namespace Ui {
class tmp;
}

class tmp : public QWidget
{
    Q_OBJECT

public:
    explicit tmp(QWidget *parent = nullptr);
    ~tmp();

private:
    Ui::tmp *ui;
};

#endif // TMP_H
