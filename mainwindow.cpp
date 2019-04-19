#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "rmodel.h"
#include "rheaders.h"
#include<qfile.h>
#include<qfiledialog.h>
#include"rutils.h"
#include"ralgorithm.h"
#include"rdialog_threshold.h"
MainWindow* MainWindow::ins=NULL;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ins=this;
    ui->setupUi(this);
    initUI();
}



MainWindow::~MainWindow()
{
    delete ui;
}
//Related Method----------------------------------------------------------------------------------------------------------
MainWindow* MainWindow::getInstance()
{
    return ins;
}
void MainWindow::initUI()
{
    //make TabWidget left to right
    ui->horizontalLayout->addStretch();
    ui->horizontalLayout_2->addStretch();
    ui->horizontalLayout_4->addStretch();

    //connet toolbutton to action
    connect(ui->toolButton_5,SIGNAL(clicked()),ui->actionOpen,SLOT(trigger()));
    connect(ui->toolButton_9,SIGNAL(clicked()),ui->actionZoom_2,SLOT(trigger()));
    connect(ui->toolButton_10,SIGNAL(clicked()),ui->actionZoom_3,SLOT(trigger()));
    connect(ui->toolButton_7,SIGNAL(clicked()),ui->actionRGB2Gray,SLOT(trigger()));
    connect(ui->toolButton,SIGNAL(clicked()),ui->actionReset,SLOT(trigger()));
    connect(ui->toolButton_6,SIGNAL(clicked()),ui->actionThreshold,SLOT(trigger()));

}

void MainWindow::setOverlayer(QPixmap & p)
{
    pixmap_overlayer=p;
}
void MainWindow::showOverlayer(bool status)
{
    scene_mainshow.clear();
    overlayer_show=status;
    if(status==false)
    {
        scene_mainshow.addPixmap(pixmap_mainshow);
    }else
    {
        scene_mainshow.addPixmap(pixmap_mainshow);
        scene_mainshow.addPixmap(pixmap_overlayer);
    }

    scene_mainshow.update();

}



//Slots------------------------------------------------------------------------------------------------------------------
void MainWindow::on_actionOpen_triggered()
{

    QString imagePath = QFileDialog::getOpenFileName(this, tr("Open image"),"",
                                             tr("All Files (*);;"
                                                "All Images (*.bpm *.gif *.jpg *.jpeg *.png *.ppm *.xbm *.xpm);;"
                                                "Image BPM (*.bpm);;"
                                                "Image GIF (*.gif);;"
                                                "Image JPG (*.jpg);;"
                                                "Image JPEG (*.jpeg);;"
                                                "Image PNG (*.png);;"
                                                "Image PPM (*.ppm);;"
                                                "Image XBM (*.xbm);;"
                                                "Image XPM (*.xpm);;"));

    if (!imagePath.isEmpty())
    {
        QFile file(imagePath);
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::critical(this, tr("error"),
                                  tr("Unable to open image."));
            return;
        }

        // upload image
        auto info = new QFileInfo(imagePath);

        //read image
        pixmap_mainshow.load(info->filePath());
        RModel::getInstance()->mat_org=RUtils::QPixmapToCvMat(pixmap_mainshow);
        RModel::getInstance()->mat_result=RModel::getInstance()->mat_org.clone();

        //show image
        scene_mainshow.clear();
        scene_mainshow.addPixmap(pixmap_mainshow);
        ui->graphicsView->setScene(&scene_mainshow);
        ui->graphicsView->show();


        this->setWindowTitle(info->fileName() + " - ImageQt");
    }

}

void MainWindow::on_actionZoom_2_triggered()
{
    ui->graphicsView->scale(1.1,1.1);
}


void MainWindow::on_actionZoom_3_triggered()
{
    ui->graphicsView->scale(0.9,0.9);
}

void MainWindow::on_actionRGB2Gray_triggered()
{
    auto & cur_result=RModel::getInstance()->mat_result;
    RAlgorithm::RGB2Gray(cur_result,cur_result);
    this->pixmap_mainshow=RUtils::cvMatToQPixmap(cur_result);
    scene_mainshow.clear();
    scene_mainshow.addPixmap(pixmap_mainshow);
    scene_mainshow.update();
}

void MainWindow::on_actionSave_As_triggered()
{
    QString imagePath = QFileDialog::getSaveFileName(this, tr("Save image"),"",
                                             tr("All Files (*);;"
                                                "All Images (*.bpm *.gif *.jpg *.jpeg *.png *.ppm *.xbm *.xpm);;"
                                                "Image BPM (*.bpm);;"
                                                "Image GIF (*.gif);;"
                                                "Image JPG (*.jpg);;"
                                                "Image JPEG (*.jpeg);;"
                                                "Image PNG (*.png);;"
                                                "Image PPM (*.ppm);;"
                                                "Image XBM (*.xbm);;"
                                                "Image XPM (*.xpm);;"));

    if (!imagePath.isEmpty())
    {
        imwrite(imagePath.toStdString(),RModel::getInstance()->mat_result);
    }
}

void MainWindow::on_actionReset_triggered()
{
    RModel::getInstance()->mat_result=RModel::getInstance()->mat_org.clone();
    this->pixmap_mainshow=RUtils::cvMatToQPixmap(RModel::getInstance()->mat_result);
    scene_mainshow.clear();
    scene_mainshow.addPixmap(pixmap_mainshow);
    scene_mainshow.update();
}

void MainWindow::on_actionTools_Bar_triggered()
{

}

void MainWindow::on_actionTools_Bar_toggled(bool arg1)
{
    ui->tabWidget->setVisible(arg1);
}

void MainWindow::on_actionThreshold_triggered()
{

    RDialog_threshold rdt;
    ui->checkBox->setChecked(true);
    int status=rdt.exec();
    if(status==true)
    {
        ui->checkBox->setChecked(true);
    }else
    {
        ui->checkBox->setChecked(false);
    }
}

void MainWindow::on_actionOverlayer_toggled(bool arg1)
{
    showOverlayer(arg1);
}

void MainWindow::on_checkBox_stateChanged(int arg1)
{
    ui->actionOverlayer->setChecked(arg1);
}
