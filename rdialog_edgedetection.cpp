#include "rdialog_edgedetection.h"
#include "ui_rdialog_edgedetection.h"

RDialog_EdgeDetection::RDialog_EdgeDetection(QWidget *parent) : QDialog(parent),
                                                                ui(new Ui::RDialog_EdgeDetection)
{
    ui->setupUi(this);
    ui->listWidget->addItem("Grandient");
    ui->listWidget->addItem("Roberts");
    ui->listWidget->addItem("Prewitt");
    ui->listWidget->addItem("Sobel");
    ui->listWidget->addItem("Scharr");
    ui->listWidget->addItem("Canny");
}

RDialog_EdgeDetection::~RDialog_EdgeDetection()
{
    delete ui;
}

void RDialog_EdgeDetection::on_buttonBox_accepted()
{
}

void RDialog_EdgeDetection::on_listWidget_currentRowChanged(int currentRow)
{
}
