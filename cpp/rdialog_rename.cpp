#include "rdialog_rename.h"
#include "ui_rdialog_rename.h"

RDialog_rename::RDialog_rename(QWidget *parent) : QDialog(parent),
                                                  ui(new Ui::RDialog_rename)
{
    ui->setupUi(this);
}

RDialog_rename::~RDialog_rename()
{
    delete ui;
}

void RDialog_rename::on_buttonBox_accepted()
{
}

void RDialog_rename::on_buttonBox_rejected()
{
}

QString RDialog_rename::getValue()
{
    return ui->lineEdit->text();
}
void RDialog_rename::setValue(QString t)
{
    ui->lineEdit->setText(t);
}
