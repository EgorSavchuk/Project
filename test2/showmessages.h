#ifndef SHOWMESSAGES_H
#define SHOWMESSAGES_H

#include <QDialog>

namespace Ui {
class ShowMessages;
}

class ShowMessages : public QDialog
{
    Q_OBJECT

public:
    explicit ShowMessages(QWidget *parent = nullptr);
    ~ShowMessages();

private:
    Ui::ShowMessages *ui;
};

#endif // SHOWMESSAGES_H
