#ifndef RMODEL_H
#define RMODEL_H
#include <map>
#include <QPixmap>
#include "rheaders.h"
#include "rmat_qimage_coverter.h"
using namespace cv;
class RModel
{

public:
    /**
     * @brief original mat map
     */
    std::map<int, Mat> mat_map_org;

    /**
     * @brief current show mat map
     */
    std::map<int, Mat> mat_map_show;

    /**
     * @brief current show Pixmap
     */
    std::map<int, QPixmap> pixmap_map_show;

    /**
     * @brief orginal mat infomation string
     */
    std::map<int, QString> info_string;

    /**
     * @brief do image process result string
     */
    std::map<int, QString> result_string;

    /**
     * @brief overlayer mat ,1-channel mat
     * 
     */
    Mat mat_overlayer;

    /**
     * @brief overlayer pixmap
     */
    QPixmap pixmap_overlayer;

    int cur_num = -1;
    int cur_max_num = 0;

public:
    RModel()
    {
    }

    static RModel *getInstance()
    {
        static RModel *instance = new RModel();
        return instance;
    }

    int addImage(Mat &mat)
    {
        mat_map_org[cur_max_num] = mat.clone();
        mat_map_show[cur_max_num] = mat_map_org[cur_max_num].clone();
        QPixmap qp = RMatQImageCoverter::cvMatToQPixmap(mat);
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
        QPixmap qp = RMatQImageCoverter::cvMatToQPixmap(mat);
        pixmap_map_show[cur_num] = qp.copy();
    }

    Mat &getCurrentMatShow()
    {
        return mat_map_show[cur_num];
    }
    void setCurrentMatShow(Mat &mat)
    {
        mat_map_show[cur_num] = mat;
    }

    Mat &getCurrentMatOrg()
    {
        return mat_map_org[cur_num];
    }

    void setCurrentMatOrg(Mat &mat)
    {
        mat_map_org[cur_num] = mat;
    }

    QPixmap &getCurrentPixmap()
    {
        return pixmap_map_show[cur_num];
    }
    void setCurrentPixmap(QPixmap &pm)
    {
        pixmap_map_show[cur_num] = pm.copy();
    }

    Mat &getOverlayerMat()
    {
        return mat_overlayer;
    }
    void setOverlayerMat(Mat &mat)
    {
        mat_overlayer = mat;
        pixmap_overlayer = RMatQImageCoverter::cvMat1ChannelToQPixmap(mat);
    }
    QPixmap getOverlayerPixmap()
    {
        return pixmap_overlayer;
    }

    QString &getCurrentInfoString()
    {
        return info_string[cur_num];
    }
    void setCurrentInfoString(QString t)
    {
        info_string[cur_num] = t;
    }

    QString &getCurrentResultString()
    {
        return result_string[cur_num];
    }
    void setCurrentResultString(QString t)
    {
        result_string[cur_num] = t;
    }
};

#endif // RMODEL_H
