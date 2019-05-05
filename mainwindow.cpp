#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "rmodel.h"
#include "rheaders.h"
#include<qfile.h>
#include<qfiledialog.h>
#include"rutils.h"
#include"ralgorithm.h"
#include"rdialog_threshold.h"
#include"rdialog_rename.h"
#include"rdialog_morphology.h"
#include"rdialog_edgedetection.h"
#include"rdialog_threshold_color.h"
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
    connect(ui->toolButton_2,SIGNAL(clicked()),ui->actionAddImage,SLOT(trigger()));

    connect(ui->toolButton_4,SIGNAL(clicked()),ui->actionSave_As,SLOT(trigger()));
    connect(ui->toolButton_3,SIGNAL(clicked()),ui->actionConnected_Domin_Lable,SLOT(trigger()));
    connect(ui->toolButton_8,SIGNAL(clicked()),ui->actionmorphology_process,SLOT(trigger()));
    connect(ui->toolButton_11,SIGNAL(clicked()),ui->actionDestoryAllCvWindows,SLOT(trigger()));
    connect(ui->toolButton_12,SIGNAL(clicked()),ui->actionEdge_Detection,SLOT(trigger()));
    connect(ui->toolButton_13,SIGNAL(clicked()),ui->actionThreshold_Color,SLOT(trigger()));
    //listView
    ui->listWidget_2->setContextMenuPolicy(Qt::CustomContextMenu);


    //show menu
    list_m_contextMenu = new QMenu();
    list_m_contextMenu->addAction(ui->actionRemove_Image);
    list_m_contextMenu->addAction(ui->actionRename);

    //init GraphicsView
    ui->graphicsView->setScene(&scene_mainshow);
    ui->graphicsView->show();
}

void MainWindow::showOverlayer(bool status)
{
    scene_mainshow.clear();
    if(status==false)
    {
        scene_mainshow.addPixmap(RModel::getInstance()->getCurrentPixmap());
    }else
    {
        scene_mainshow.addPixmap(RModel::getInstance()->getCurrentPixmap());
        scene_mainshow.addPixmap(RModel::getInstance()->getOverlayer());
    }
    scene_mainshow.update();
}

void MainWindow::updateCurrentImage()
{
    if(RModel::getInstance()->cur_num==-1)//called when image removed
    {
        scene_mainshow.clear();
        scene_mainshow.setSceneRect(QRectF(0,0,0,0));
        ui->textEdit_2->setText("");
        ui->textEdit_3->setText("");
        return;
    }
    RController::genImageInfo();
    scene_mainshow.clear();
    QPixmap cp=RModel::getInstance()->getCurrentPixmap();
    scene_mainshow.setSceneRect(QRectF(0,0,cp.width(),cp.height()));
    scene_mainshow.addPixmap(cp);
    ui->textEdit_2->setText(RModel::getInstance()->getCurrentInfoString());
    ui->textEdit_3->setText(RModel::getInstance()->getCurrentResultString());

}

void  MainWindow::switchCurrentImage(int pm_num)
{
    if(pm_num==-1)//called when image removed
    {
        scene_mainshow.clear();
        RModel::getInstance()->cur_num=-1;
        scene_mainshow.setSceneRect(QRectF(0,0,0,0));
        ui->textEdit_2->setText("");
        ui->textEdit_3->setText("");
        return;
    }

    RModel::getInstance()->cur_num=pm_num;
    RController::genImageInfo();
    scene_mainshow.clear();
    QPixmap cp=RModel::getInstance()->getCurrentPixmap();
    scene_mainshow.setSceneRect(QRectF(0,0,cp.width(),cp.height()));
    scene_mainshow.addPixmap(cp);
    ui->textEdit_2->setText(RModel::getInstance()->getCurrentInfoString());
    ui->textEdit_3->setText(RModel::getInstance()->getCurrentResultString());
}

//listview--------------------------------------------------------------------------------------------------------------
void MainWindow::addListItem(QString text,int pm_num)
{
    QListWidgetItem* lwi=new QListWidgetItem();
    lwi->setText(text);
    lwi->setData(1,pm_num);
    ui->listWidget_2->addItem(lwi);
    ui->listWidget_2->setCurrentItem(lwi);
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
        Mat mat=imread(info->filePath().toStdString(),IMREAD_UNCHANGED);

        //read image
        //QPixmap pixmap_mainshow;
        //pixmap_mainshow.load(info->filePath());

        //load Data
        int cur_pm_num=RModel::getInstance()->addImage(mat);
        addListItem(info->fileName(),cur_pm_num);
        switchCurrentImage(cur_pm_num);
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
    Mat cur_result=RModel::getInstance()->getCurrentMatShow();
    RAlgorithm::RGB2Gray(cur_result,cur_result);
    RModel::getInstance()->setCurrentMatShow(cur_result);

    QPixmap pm=RUtils::cvMatToQPixmap(cur_result);
    RModel::getInstance()->setCurrentPixmap(pm);

    updateCurrentImage();
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
        imwrite(imagePath.toStdString(),RModel::getInstance()->getCurrentMatShow());
    }
}

void MainWindow::on_actionReset_triggered()
{
    Mat mo=RModel::getInstance()->getCurrentMatOrg().clone();
    RModel::getInstance()->setCurrentMatShow(mo);

    QPixmap pm=RUtils::cvMatToQPixmap(mo);
    RModel::getInstance()->setCurrentPixmap(pm);

    updateCurrentImage();
}

void MainWindow::on_actionTools_Bar_toggled(bool arg1)
{
    ui->tabWidget->setVisible(arg1);
}

void MainWindow::on_actionThreshold_triggered()
{
    Mat cr=RModel::getInstance()->getCurrentMatShow();
    if(cr.channels()!=1)
    {
        QMessageBox::warning(NULL,"Warning","Ensure Current Image Gray!");
        return;
    }

    RDialog_threshold rdt;
    rdt.exec();

    updateCurrentImage();
}


void MainWindow::on_listWidget_2_itemDoubleClicked(QListWidgetItem *item)
{
    int num=item->data(1).toInt();
    switchCurrentImage(num);
}

void MainWindow::on_listWidget_2_customContextMenuRequested(const QPoint &pos)
{
    if(ui->listWidget_2->count()<=0)
    {
        return;
    }
    list_m_contextMenu->exec(QCursor::pos());
}

void MainWindow::on_actionRemove_Image_triggered()
{
    QListWidgetItem* ci=ui->listWidget_2->currentItem();
    int index=ci->data(1).toInt();
    RModel::getInstance()->removeImage(index);
    int row=ui->listWidget_2->currentRow();
    ui->listWidget_2->takeItem(row);

    switchCurrentImage(-1);
}

void MainWindow::on_actionRename_triggered()
{
    QListWidgetItem* ci=ui->listWidget_2->currentItem();
    RDialog_rename rrn;
    rrn.setValue(ci->text());
    if(rrn.exec()==true)
    {
        ci->setText(rrn.getValue());
    }
    
}

void MainWindow::on_actionAddImage_triggered()
{
    Mat mat=RModel::getInstance()->getCurrentMatShow();
    QString str;
    int cur_pm_num=RModel::getInstance()->addImage(mat);
    str.sprintf("Image-%d",cur_pm_num);
    addListItem(str,cur_pm_num);

    switchCurrentImage(cur_pm_num);
}


void MainWindow::on_actionConnected_Domin_Lable_triggered()
{
    Mat t=RModel::getInstance()->getCurrentMatShow();
    if(RAlgorithm::isBinary(t)== false)
    {
        QMessageBox::warning(NULL,"Warning","Connected Domin Lable Need Binary Image!");
        return;
    }

    Mat src=RModel::getInstance()->getCurrentMatShow();
    Mat dst,dst_show;
    int num=0;
    RAlgorithm::getConnectedDomainLable(src,dst,dst_show,num);
    QString str;
    str.sprintf("Domin Num:%d",num);
    imshow("Connected Domin Lable",dst_show);
    //RModel::getInstance()->setCurrentImage(dst_show);

    RModel::getInstance()->setCurrentResultString(str);
    updateCurrentImage();
}


void MainWindow::on_actionmorphology_process_triggered()
{
    Mat t=RModel::getInstance()->getCurrentMatShow();
    if(RAlgorithm::isBinary(t)==false)
    {
        QMessageBox::warning(NULL,"Warning","Current image should be binary image!");
        return;
    }
    RDialog_morphology rdm;
    if(rdm.exec()==true)
    {
        RModel::getInstance()->setCurrentImage(rdm.result);
        updateCurrentImage();
    }

}

void MainWindow::on_actionDestoryAllCvWindows_triggered()
{
    destroyAllWindows();
}

void MainWindow::on_actionEdge_Detection_triggered()
{
    RDialog_EdgeDetection red;
    red.exec();

}

void MainWindow::on_actionThreshold_Color_triggered()
{
    Mat cr=RModel::getInstance()->getCurrentMatShow();
    if(cr.channels()!=3)
    {
        QMessageBox::warning(NULL,"Warning","Ensure Current Image Color!");
        return;
    }

    RDialog_threshold_color rtc;
    rtc.exec();

    updateCurrentImage();



}
