#ifndef ENTRINGDIALOG_H
#define ENTRINGDIALOG_H
#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class EntringDialog;
}

class EntringDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EntringDialog(QWidget *parent = 0);
    ~EntringDialog();

private slots:
    void on_Start_clicked();

    void on_Exit_clicked();

private:
    Ui::EntringDialog *ui;
    MainWindow *w;

};

#endif // ENTRINGDIALOG_H
