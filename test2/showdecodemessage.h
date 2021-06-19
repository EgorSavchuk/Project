#ifndef SHOWDECODEMESSAGE_H
#define SHOWDECODEMESSAGE_H

#include <QDialog>

namespace Ui {
class ShowDecodeMessage;
}

class ShowDecodeMessage : public QDialog
{
    Q_OBJECT

public:
    explicit ShowDecodeMessage(QWidget *parent = nullptr);
    ~ShowDecodeMessage();

private:
    Ui::ShowDecodeMessage *ui;
};

#endif // SHOWDECODEMESSAGE_H
