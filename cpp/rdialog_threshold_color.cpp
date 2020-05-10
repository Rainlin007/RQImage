#include "rdialog_threshold_color.h"
#include "ui_rdialog_threshold_color.h"
#include "rcontroller.h"
RDialog_threshold_color::RDialog_threshold_color(QWidget *parent) : QDialog(parent),
                                                                    ui(new Ui::RDialog_threshold_color)
{
    ui->setupUi(this);
    Qt::WindowFlags flags = 0;
    flags |= Qt::WindowMinimizeButtonHint;
    setWindowFlags(flags);                       // No max
    setFixedSize(this->width(), this->height()); // No change size
}

RDialog_threshold_color::~RDialog_threshold_color()
{
    delete ui;
}

void RDialog_threshold_color::on_checkBox_stateChanged(int arg1)
{
    MainWindow::getInstance()->showOverlayer(arg1);
}

void RDialog_threshold_color::on_spinBox_valueChanged(int arg1)
{
    threshold[0][0] = arg1;
    if (threshold[0][1] < threshold[0][0])
    {
        threshold[0][1] = threshold[0][0];
        ui->spinBox_2->setValue(threshold[0][0]);
        ui->horizontalSlider_2->setValue(threshold[0][0]);
    }
    RController::thresholdColorWindow(threshold);
}

void RDialog_threshold_color::on_spinBox_2_valueChanged(int arg1)
{
    threshold[0][1] = arg1;
    if (threshold[0][1] < threshold[0][0])
    {
        threshold[0][0] = threshold[0][1];
        ui->spinBox->setValue(threshold[0][0]);
        ui->horizontalSlider->setValue(threshold[0][0]);
    }
    RController::thresholdColorWindow(threshold);
}

void RDialog_threshold_color::on_spinBox_3_valueChanged(int arg1)
{
    threshold[1][0] = arg1;
    if (threshold[1][1] < threshold[1][0])
    {
        threshold[1][1] = threshold[1][0];
        ui->spinBox_4->setValue(threshold[1][0]);
        ui->horizontalSlider_4->setValue(threshold[1][0]);
    }
    RController::thresholdColorWindow(threshold);
}
void RDialog_threshold_color::on_spinBox_4_valueChanged(int arg1)
{

    threshold[1][1] = arg1;
    if (threshold[1][1] < threshold[1][0])
    {
        threshold[1][0] = threshold[1][1];
        ui->spinBox_3->setValue(threshold[1][0]);
        ui->horizontalSlider_3->setValue(threshold[1][0]);
    }
    RController::thresholdColorWindow(threshold);
}

void RDialog_threshold_color::on_spinBox_5_valueChanged(int arg1)
{
    threshold[2][0] = arg1;
    if (threshold[2][1] < threshold[2][0])
    {
        threshold[2][1] = threshold[2][0];
        ui->spinBox_6->setValue(threshold[2][0]);
        ui->horizontalSlider_6->setValue(threshold[2][0]);
    }
    RController::thresholdColorWindow(threshold);
}

void RDialog_threshold_color::on_spinBox_6_valueChanged(int arg1)
{
    threshold[2][1] = arg1;
    if (threshold[2][1] < threshold[2][0])
    {
        threshold[2][0] = threshold[2][1];
        ui->spinBox_5->setValue(threshold[2][0]);
        ui->horizontalSlider_5->setValue(threshold[2][0]);
    }
    RController::thresholdColorWindow(threshold);
}

void RDialog_threshold_color::on_buttonBox_accepted()
{
    Mat ol = RModel::getInstance()->getMatOverlayer();
    RModel::getInstance()->setCurrentImage(ol);
    this->accept();
}

void RDialog_threshold_color::on_buttonBox_rejected()
{
}
