#include "rdialog_threshold.h"
#include "ui_rdialog_threshold.h"
#include "rcontroller.h"
RDialog_threshold::RDialog_threshold(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RDialog_threshold)
{
    ui->setupUi(this);
    Qt::WindowFlags flags = 0;
    flags |= Qt::WindowMinimizeButtonHint;
    setWindowFlags(flags); // No max
    setFixedSize(this->width(),this->height()); // No change size
}

RDialog_threshold::~RDialog_threshold()
{
    delete ui;
}

void RDialog_threshold::on_pushButton_clicked()
{

    Mat ol=RModel::getInstance()->getMatOverlayer();
    RModel::getInstance()->setCurrentImage(ol);
    this->accept();
}

void RDialog_threshold::on_pushButton_2_clicked()
{
    this->reject();
};
void RDialog_threshold::on_spinBox_valueChanged(int arg1)
{
    threshold_1=arg1;
    if(threshold_2<threshold_1)
    {
        threshold_2=threshold_1;
        ui->spinBox_2->setValue(threshold_1);
        ui->horizontalSlider_2->setValue(threshold_1);
    }

    RController::threshold_window(threshold_1,threshold_2);
}

void RDialog_threshold::on_spinBox_2_valueChanged(int arg1)
{
    threshold_2=arg1;
    if(threshold_1>threshold_2)
    {
        threshold_1=threshold_2;
        ui->spinBox->setValue(threshold_1);
        ui->horizontalSlider->setValue(threshold_1);
    }
    RController::threshold_window(threshold_1,threshold_2);
}

void RDialog_threshold::on_checkBox_stateChanged(int arg1)
{
    MainWindow::getInstance()->showOverlayer(arg1);
}
