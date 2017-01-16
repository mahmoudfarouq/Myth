#ifndef WINNINGDIALOG_H
#define WINNINGDIALOG_H

#include <QDialog>
#include <QDebug>

namespace Ui {
class WinningDialog;
}

class WinningDialog : public QDialog
{
    Q_OBJECT

public:
    explicit WinningDialog(QWidget *parent = 0);
    ~WinningDialog();
    void setName(QString n);


private slots:
    void on_Exit_clicked();

private:
    Ui::WinningDialog *ui;
};

#endif // WINNINGDIALOG_H
