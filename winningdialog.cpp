#include "winningdialog.h"
#include "ui_winningdialog.h"

WinningDialog::WinningDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WinningDialog)
{
    ui->setupUi(this);

}

WinningDialog::~WinningDialog()
{
    delete ui;
}

void WinningDialog::on_Exit_clicked()
{
    exit(1);
}
void WinningDialog::setName(QString n)
{
    ui->label_2->setText( n );
}
