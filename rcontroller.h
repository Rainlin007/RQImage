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
        Mat & cr=RModel::getInstance()->mat_result;
        Mat dst;
        if(cr.channels()!=1)
        {
            QMessageBox::warning(NULL,"Warning","Ensure Current Image Gray");
            return;
        }

        RAlgorithm::threshold_range(cr,dst,t1,t2);
        QPixmap qp=RUtils::cvMatToQPixmap(dst);
        mw->setOverlayer(qp);
        mw->showOverlayer(true);
    }
    static QPixmap getHistogramPixmap()
    {
        auto his=RAlgorithm::getHistogram(RModel::getInstance()->mat_result);
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

};

#endif // RCONTROLLER_H