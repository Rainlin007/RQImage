#include "rdialog_morphology.h"
#include "ui_rdialog_morphology.h"
#include "ralgorithm.h"
#include "rmodel.h"
RDialog_morphology::RDialog_morphology(QWidget *parent) : QDialog(parent),
                                                          ui(new Ui::RDialog_morphology)
{
    ui->setupUi(this);
    ui->listWidget->addItem("Dilation");
    ui->listWidget->addItem("Erosion");
    ui->listWidget->addItem("Open");
    ui->listWidget->addItem("Close");
    ui->listWidget->addItem("Granient");
    ui->listWidget->addItem("Top Hat");
    ui->listWidget->addItem("Black Hat");
    ui->listWidget->addItem("Hit Miss");
    ui->spinBox->setValue(5);
    ui->listWidget->setCurrentRow(0);
}
RDialog_morphology::~RDialog_morphology()
{
    delete ui;
}

void RDialog_morphology::on_pushButton_clicked()
{
    int s = ui->spinBox->value();
    if (s <= 0)
    {
        QMessageBox::warning(NULL, "Waring", "Structure size should be greater than 0!");
        return;
    }
    QString t = ui->listWidget->currentItem()->text();
    Mat src = RModel::getInstance()->getCurrentMatShow();
    if (t == "Erosion")
    {
        RAlgorithm::morphology(src, result, MORPH_ERODE, s);
    }
    else if (t == "Dilation")
    {
        RAlgorithm::morphology(src, result, MORPH_DILATE, s);
    }
    else if (t == "Open")
    {
        RAlgorithm::morphology(src, result, MORPH_OPEN, s);
    }
    else if (t == "Close")
    {
        RAlgorithm::morphology(src, result, MORPH_CLOSE, s);
    }
    else if (t == "Granient")
    {
        RAlgorithm::morphology(src, result, MORPH_GRADIENT, s);
    }
    else if (t == "Top Hat")
    {
        RAlgorithm::morphology(src, result, MORPH_TOPHAT, s);
    }
    else if (t == "Black Hat")
    {
        RAlgorithm::morphology(src, result, MORPH_BLACKHAT, s);
    }
    else if (t == "Hit Miss")
    {
        RAlgorithm::morphology(src, result, MORPH_HITMISS, s);
    }
    imshow("morphology", result);
}

void RDialog_morphology::on_buttonBox_accepted()
{

    destroyWindow("morphology");
}

void RDialog_morphology::on_buttonBox_rejected()
{
    destroyWindow("morphology");
}
