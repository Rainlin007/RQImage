#ifndef RMODEL_H
#define RMODEL_H
#include <map>
#include <QPixmap>
#include "rheaders.h"
#include "rutils.h"
using namespace cv;
class RModel
{
private:
    static RModel *instance;

public:
    std::map<int, Mat> mat_map_org;  //original Mat
    std::map<int, Mat> mat_map_show; //current show Mat

    std::map<int, QPixmap> pixmap_map_show; //current show Pixmap

    std::map<int, QString> info_string;
    std::map<int, QString> result_string;

    QPixmap pixmap_overlayer; //overlayer image
    Mat mat_overlayer;        //overlayer mat

    int cur_num = -1;
    int cur_max_num = 0;

public:
    RModel()
    {
    }

    static RModel *getInstance()
    {
        if (instance == NULL)
        {
            instance = new RModel();
        }
        return instance;
    }

    //    int addImage(QPixmap& pixmap)
    //    {
    //        int d=pixmap.depth();
    //        pixmap_map_show[cur_max_num]=pixmap.copy();
    //        mat_map_org[cur_max_num]=RUtils::QPixmapToCvMat(pixmap_map_show[cur_max_num]);
    //        mat_map_show[cur_max_num]=mat_map_org[cur_max_num].clone();
    //        return cur_max_num++;
    //    }

    int addImage(Mat &mat)
    {
        mat_map_org[cur_max_num] = mat.clone();
        mat_map_show[cur_max_num] = mat_map_org[cur_max_num].clone();
        QPixmap qp = RUtils::cvMatToQPixmap(mat);
        pixmap_map_show[cur_max_num] = qp.copy();
        return cur_max_num++;
    }

    void removeImage(int id)
    {
        pixmap_map_show[id] = QPixmap();
        mat_map_org[id] = Mat();
        mat_map_show[id] = Mat();
        info_string[id] = "";
    }

    void setCurrentImage(Mat mat)
    {
        mat_map_show[cur_num] = mat.clone();
        QPixmap qp = RUtils::cvMatToQPixmap(mat);
        pixmap_map_show[cur_num] = qp.copy();
    }

    Mat getCurrentMatShow()
    {
        return mat_map_show[cur_num];
    }
    void setCurrentMatShow(Mat &mat)
    {
        mat_map_show[cur_num] = mat;
    }

    Mat getCurrentMatOrg()
    {
        return mat_map_org[cur_num];
    }

    void setCurrentMatOrg(Mat &mat)
    {
        mat_map_org[cur_num] = mat;
    }

    QPixmap getCurrentPixmap()
    {
        return pixmap_map_show[cur_num];
    }
    void setCurrentPixmap(QPixmap &pm)
    {
        pixmap_map_show[cur_num] = pm.copy();
    }

    QPixmap getOverlayer()
    {
        return pixmap_overlayer;
    }
    void setOverlayer(QPixmap &qp)
    {
        pixmap_overlayer = qp.copy();
    }

    Mat getMatOverlayer()
    {
        return mat_overlayer;
    }
    void setMatOverlayer(Mat &mat)
    {
        mat_overlayer = mat;
    }

    QString getCurrentInfoString()
    {
        return info_string[cur_num];
    }
    void setCurrentInfoString(QString t)
    {
        info_string[cur_num] = t;
    }

    QString getCurrentResultString()
    {
        return result_string[cur_num];
    }
    void setCurrentResultString(QString t)
    {
        result_string[cur_num] = t;
    }
};

#endif // RMODEL_H
