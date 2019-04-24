#ifndef RMODEL_H
#define RMODEL_H
#include "rheaders.h"
#include<map>
#include<QPixmap>
#include "rutils.h"
using namespace cv;
class RModel
{
private:
    static RModel* instance;

public:
    std::map<int,Mat> mat_map_org;
    std::map<int,Mat> mat_map_show;

    std::map<int,QPixmap> pixmap_map_show;


    QPixmap pixmap_overlayer;//overlayer image
    Mat mat_overlayer;//overlayer mat


    int cur_num=0;
    int cur_max_num=0;
public:
    RModel()
    {

    }

    static RModel *getInstance()
    {
        if(instance==NULL)
        {
            instance=new RModel();
        }
        return instance;
    }

    int addImage(QPixmap& pixmap)
    {
        pixmap_map_show[cur_max_num]=pixmap.copy();
        mat_map_org[cur_max_num]=RUtils::QPixmapToCvMat(pixmap_map_show[cur_max_num]);
        mat_map_show[cur_max_num]=mat_map_org[cur_max_num].clone();
        return cur_max_num++;
    }
    void removeImage(int id)
    {
        pixmap_map_show[id]=QPixmap();
        mat_map_org[id]=Mat();
        mat_map_show[id]=Mat();
    }




    Mat getCurrentMatShow()
    {
        return mat_map_show[cur_num];
    }
    void setCurrentMatShow(Mat& mat)
    {
        mat_map_show[cur_num]=mat;
    }



    Mat getCurrentMatOrg()
    {
        return mat_map_org[cur_num];
    }

    void setCurrentMatOrg(Mat& mat)
    {
        mat_map_org[cur_num]=mat;
    }


    QPixmap getCurrentPixmap()
    {
        return pixmap_map_show[cur_num];
    }
    void  setCurrentPixmap(QPixmap& pm)
    {
        pixmap_map_show[cur_num]=pm.copy();
    }


    QPixmap getOverlayer()
    {
        return pixmap_overlayer;
    }
    void setOverlayer(QPixmap& qp)
    {
        pixmap_overlayer=qp.copy();
    }


    Mat getMatOverlayer()
    {
        return mat_overlayer;
    }
    void setMatOverlayer(Mat& mat)
    {
        mat_overlayer=mat;
    }




};



#endif // RMODEL_H
