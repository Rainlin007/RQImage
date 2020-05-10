#ifndef RUTILS_H
#define RUTILS_H
#include "rheaders.h"
#include <unordered_map>
class RMatQImageCoverter final
{
public:
    RMatQImageCoverter() = delete;
    RMatQImageCoverter(const RMatQImageCoverter &) = delete;
    RMatQImageCoverter &operator=(const RMatQImageCoverter &) = delete;

    static std::unordered_map<uchar, cv::Vec3b> color_map;
    static static QImage cvMatToQImage(const cv::Mat &inMat)
    {
        switch (inMat.type())
        {
        // 8-bit, 4 channel
        case CV_8UC4:
        {
            QImage image(inMat.data,
                         inMat.cols, inMat.rows,
                         static_cast<int>(inMat.step),
                         QImage::Format_ARGB32);

            return image;
        }

        // 8-bit, 3 channel
        case CV_8UC3:
        {
            QImage image(inMat.data,
                         inMat.cols, inMat.rows,
                         static_cast<int>(inMat.step),
                         QImage::Format_RGB888);

            return image.rgbSwapped();
        }

        // 8-bit, 1 channel
        case CV_8UC1:
        {
            QImage image(inMat.data,
                         inMat.cols, inMat.rows,
                         static_cast<int>(inMat.step),
                         QImage::Format_Grayscale8); //Format_Alpha8 and Format_Grayscale8 were added in Qt 5.5

            return image;
        }

        default:
            qWarning() << "CVS::cvMatToQImage() - cv::Mat image type not handled in switch:" << inMat.type();
            break;
        }

        return QImage();
    }

    static QPixmap cvMatToQPixmap(const cv::Mat &inMat)
    {
        return QPixmap::fromImage(cvMatToQImage(inMat));
    }

    static cv::Mat QImageToCvMat(const QImage &inImage, bool inCloneImageData = true)
    {
        switch (inImage.format())
        {
        // 8-bit, 4 channel
        case QImage::Format_ARGB32:
        case QImage::Format_ARGB32_Premultiplied:
        {
            cv::Mat mat(inImage.height(), inImage.width(),
                        CV_8UC4,
                        const_cast<uchar *>(inImage.bits()),
                        static_cast<size_t>(inImage.bytesPerLine()));

            return (inCloneImageData ? mat.clone() : mat);
        }

        // 8-bit, 3 channel
        case QImage::Format_RGB32:
        case QImage::Format_RGB888:
        {
            if (!inCloneImageData)
            {
                qWarning() << "CVS::QImageToCvMat() - Conversion requires cloning because we use a temporary QImage";
            }

            QImage swapped = inImage;

            if (inImage.format() == QImage::Format_RGB32)
            {
                swapped = swapped.convertToFormat(QImage::Format_RGB888);
            }

            swapped = swapped.rgbSwapped();

            return cv::Mat(swapped.height(), swapped.width(),
                           CV_8UC3,
                           const_cast<uchar *>(swapped.bits()),
                           static_cast<size_t>(swapped.bytesPerLine()))
                .clone();
        }

        // 8-bit, 1 channel
        case QImage::Format_Indexed8:
        case QImage::Format_Grayscale8:
        {
            cv::Mat mat(inImage.height(), inImage.width(),
                        CV_8UC1,
                        const_cast<uchar *>(inImage.bits()),
                        static_cast<size_t>(inImage.bytesPerLine()));

            return (inCloneImageData ? mat.clone() : mat);
        }

        default:
            qWarning() << "CVS::QImageToCvMat() - QImage format not handled in switch:" << inImage.format();
            break;
        }

        return cv::Mat();
    }

    static cv::Mat QPixmapToCvMat(const QPixmap &inPixmap, bool inCloneImageData = true)
    {
        return QImageToCvMat(inPixmap.toImage(), inCloneImageData);
    }

    /**
     * @brief init color_map
     * 
     */
    static void initColorMap()
    {
        for (uchar i = 1; i < 255; ++i)
        {
            //random color
            color_map[i] = cv::Vec3b((i * 3 + 13) % 255, ((127 - i) * 7 + 17) % 255, ((255 - i) * 2 + 23) % 255);
        }
        color_map[0] = cv::Vec3b(0, 0, 0);
        color_map[255] = cv::Vec3b(255, 255, 255);
    }
    /**
     * @brief covert 1-channel mat to QPixmap with color
     * 
     * @param src 
     * @param inCloneImageData 
     * @return QPixmap 
     */
    static QPixmap cvMat1ChannelToQPixmap(const cv::Mat &src, bool inCloneImageData = true)
    {
        if (color_map.empty())
        {
            initColorMap();
        }
        cv::Mat dst = cv::Mat::zeros(src.rows, src.cols, CV_8UC3);
        for (int i = 0; i < src.rows; ++i)
        {
            for (int j = 0; j < src.cols; ++j)
            {
                dst.at<cv::Vec3b>(i, j) = color_map[src.at<uchar>(i, j)];
            }
        }
        return QPixmap::fromImage(cvMatToQImage(dst));
    }
};

#endif // RUTILS_H
