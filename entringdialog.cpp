#include "entringdialog.h"
#include "ui_entringdialog.h"

EntringDialog::EntringDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EntringDialog)
{
    ui->setupUi(this);
}

EntringDialog::~EntringDialog()
{
    delete ui;
}

void EntringDialog::on_Start_clicked()
{
    this->hide();
    w = new MainWindow;
    w->show();
}

void EntringDialog::on_Exit_clicked()
{
    exit(1);
}
