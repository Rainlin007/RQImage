#ifndef RCONTROLLER_H
#define RCONTROLLER_H
#include "rheaders.h"
#include "mainwindow.h"
#include "ralgorithm.h"
#include "rmodel.h"
#include "rmat_qimage_coverter.h"
#include <QPainter>
#include <algorithm>
class RController
{

public:
    RController()
    {
    }
    static RController *getInstance()
    {
        static RController *instance = new RController();
        return instance;
    }

    static void thresholdWindow(int t1, int t2)
    {
        Mat &cur_mat_show = RModel::getInstance()->getCurrentMatShow();
        if (cur_mat_show.channels() != 1)
        {
            QMessageBox::warning(NULL, "Warning", "Ensure Current Image Gray");
            return;
        }
        Mat dst_mat_show;
        Mat dst_mat;
        //threshold overlayer mat
        RAlgorithm::thresholdRange(cur_mat_show, dst_mat, t1, t2);
        RModel::getInstance()->setOverlayerMat(dst_mat);
        MainWindow::getInstance()->showOverlayer(true);
    }
    static void thresholdColorWindow(int thd[3][2])
    {
        Mat cr = RModel::getInstance()->getCurrentMatShow();
        Mat dst;
        if (cr.channels() != 3)
        {
            QMessageBox::warning(NULL, "Warning", "Ensure Current Image Color");
            return;
        }

        Mat mat_overlayer;
        RAlgorithm::thresholdColorRange(cr, mat_overlayer, thd);

        RModel::getInstance()->setOverlayerMat(mat_overlayer);
        MainWindow::getInstance()->showOverlayer(true);
    }

    static QPixmap getHistogramPixmap()
    {
        Mat cm = RModel::getInstance()->getCurrentMatShow();
        auto his = RAlgorithm::getHistogram(cm);
        int his_max = *(max_element(his.begin(), his.end()));

        QPixmap pix(260, 151);
        pix.fill(Qt::transparent);
        QPainter pp(&pix); 
        QBrush qb(Qt::red);
        QPen qp(Qt::red);
        pp.setBrush(qb);
        pp.setPen(qp);
        for (int i = 0; i < 256; i++)
        {
            pp.drawLine(i, 150, i, 150 - ((his[i] + 0.0) / his_max) * 150);
        }
        return pix;
    }

    static vector<QPixmap> getHistogramPixmap_color()
    {
        vector<QPixmap> result;

        Mat cm = RModel::getInstance()->getCurrentMatShow();
        auto hiss = RAlgorithm::getHistogramColor(cm);
        int i = 0;
        Qt::red;
        vector<Qt::GlobalColor> cs;
        cs.push_back(Qt::blue);
        cs.push_back(Qt::green);
        cs.push_back(Qt::red);

        for (vector<int> his : hiss)
        {
            int his_max = *(max_element(his.begin(), his.end()));

            QPixmap pix(260, 151);
            pix.fill(Qt::transparent);
            QPainter pp(&pix); 
            QBrush qb(cs[i]);
            QPen qp(cs[i]);
            pp.setBrush(qb);
            pp.setPen(qp);
            for (int i = 0; i < 256; i++)
            {
                pp.drawLine(i, 150, i, 150 - ((his[i] + 0.0) / his_max) * 150);
            }
            result.push_back(pix);
            i++;
        }

        return result;
    }

    static void genImageInfo()
    {
        Mat ci = RModel::getInstance()->getCurrentMatShow();
        int channels = ci.channels();
        int r = ci.rows;
        int c = ci.cols;
        const char *isB = "NO";
        if (RAlgorithm::isBinary(ci) == true)
        {
            isB = "YES";
        }
        QString qs;
        qs.sprintf("Size:%d × %d\nChannel: %d\nBinary:%s", r, c, channels, isB);
        RModel::getInstance()->setCurrentInfoString(qs);
    }
};

#endif // RCONTROLLER_H
