#ifndef RCONTROLLER_H
#define RCONTROLLER_H
#include "rheaders.h"
#include"mainwindow.h"
#include"ralgorithm.h"
#include"rmodel.h"
#include"rutils.h"
#include<QPainter>
#include <algorithm>
class RController
{
private:
    static RController *ins;
public:
    RController()
    {

    }
    static RController *getInstance()
    {
        if(ins==NULL)
        {
            ins=new RController();
        }
        return ins;
    }



    static void threshold_window(MainWindow* mw,int t1,int t2)
    {
        Mat cr=RModel::getInstance()->getCurrentMatShow();
        Mat dst;
        if(cr.channels()!=1)
        {
            QMessageBox::warning(NULL,"Warning","Ensure Current Image Gray");
            return;
        }

        Mat mat_overlayer;
        RAlgorithm::threshold_range(cr,dst,mat_overlayer,t1,t2);//threshold overlayer mat

        RModel::getInstance()->setMatOverlayer(mat_overlayer);

        QPixmap qp=RUtils::cvMatToQPixmap(dst);
        RModel::getInstance()->setOverlayer(qp);
        mw->showOverlayer(true);
    }




    static QPixmap getHistogramPixmap()
    {
        Mat cm=RModel::getInstance()->getCurrentMatShow();
        auto his=RAlgorithm::getHistogram(cm);
        int his_max=*(max_element(his.begin(),his.end()));

        QPixmap pix(260,151);
        pix.fill(Qt::transparent);
        QPainter pp(&pix);//新建QPainter类，在pix（画布）上进行绘图
        QBrush qb(Qt::red);
        QPen qp(Qt::red);
        pp.setBrush(qb);
        pp.setPen(qp);
        for(int i=0;i<256;i++)
        {
            pp.drawLine(i,150,i,150-((his[i]+0.0)/his_max)*150);
        }
        return pix;
    }




    static void  genImageInfo()
    {
        Mat ci=RModel::getInstance()->getCurrentMatShow();
        int channels=ci.channels();
        int r=ci.rows;
        int c=ci.cols;
        QString qs;
        qs.sprintf("Size:%d × %d\nChannel: %d",r,c,channels);
        MainWindow::getInstance()->setInfo(qs);
    }

};

#endif // RCONTROLLER_H
