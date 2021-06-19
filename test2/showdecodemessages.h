#ifndef SHOWDECODEMESSAGES_H
#define SHOWDECODEMESSAGES_H

#include <QDialog>

namespace Ui {
class ShowDecodeMessages;
}

class ShowDecodeMessages : public QDialog
{
    Q_OBJECT

public:
    explicit ShowDecodeMessages(QWidget *parent = nullptr);
    ~ShowDecodeMessages();

private:
    Ui::ShowDecodeMessages *ui;
};

#endif // SHOWDECODEMESSAGES_H
