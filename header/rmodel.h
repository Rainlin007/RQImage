#ifndef RMODEL_H
#define RMODEL_H
#include <map>
#include <QPixmap>
#include "rheaders.h"
#include "rmat_qimage_coverter.h"
using namespace cv;
class RModel
{

private:
    /**
     * @brief original mat map
     */
    std::map<int, Mat> mat_map_org;

    /**
     * @brief current show mat map
     */
    std::map<int, Mat> mat_map_show;

    /**
     * @brief current show Pixmap map
     */
    std::map<int, QPixmap> pixmap_map_show;

    /**
     * @brief current mat infomation string
     */
    std::map<int, QString> info_string;

    /**
     * @brief image process result string
     */
    std::map<int, QString> result_string;

    /**
     * @brief overlayer mat ,1-channel mat
     * 
     */
    Mat mat_overlayer;

    /**
     * @brief overlayer pixmap, overlayer mat to colored pixmap
     */
    QPixmap pixmap_overlayer;

    int cur_id = -1;
    int cur_max_id = 0;

public:
    RModel()
    {
    }

    static RModel *getInstance()
    {
        static RModel *instance = new RModel();
        return instance;
    }

    int getCurShowImageId()
    {
        return cur_id;
    }
    void setCurShowImageId(int id)
    {
        cur_id = id;
    }
    int addImage(Mat &mat)
    {
        mat_map_org[cur_max_id] = mat.clone();
        mat_map_show[cur_max_id] = mat_map_org[cur_max_id].clone();
        QPixmap qp = RMatQImageCoverter::cvMatToQPixmap(mat);
        pixmap_map_show[cur_max_id] = qp.copy();
        return cur_max_id++;
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
        mat_map_show[cur_id] = mat.clone();
        QPixmap qp = RMatQImageCoverter::cvMatToQPixmap(mat);
        pixmap_map_show[cur_id] = qp.copy();
    }

    Mat &getCurrentMatShow()
    {
        return mat_map_show[cur_id];
    }
    void setCurrentMatShow(Mat &mat)
    {
        mat_map_show[cur_id] = mat;
    }

    Mat &getCurrentMatOrg()
    {
        return mat_map_org[cur_id];
    }

    void setCurrentMatOrg(Mat &mat)
    {
        mat_map_org[cur_id] = mat;
    }

    QPixmap &getCurrentPixmap()
    {
        return pixmap_map_show[cur_id];
    }
    void setCurrentPixmap(QPixmap &pm)
    {
        pixmap_map_show[cur_id] = pm.copy();
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
        return info_string[cur_id];
    }
    void setCurrentInfoString(QString t)
    {
        info_string[cur_id] = t;
    }

    QString &getCurrentResultString()
    {
        return result_string[cur_id];
    }
    void setCurrentResultString(QString t)
    {
        result_string[cur_id] = t;
    }
};

#endif // RMODEL_H
