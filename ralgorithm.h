#ifndef RALGORITHM_H
#define RALGORITHM_H
#include"rheaders.h"
#include<vector>
using namespace cv;
using namespace std;
class RAlgorithm
{
public:
    RAlgorithm()
    {

    }
public:
   static void RGB2Gray(Mat & mat_1,Mat& mat_2)
   {
       if(mat_1.channels()<3)
       {
            return;
       }
       cvtColor(mat_1,mat_2,COLOR_RGB2GRAY);
   }
   static void threshold_range(Mat& src,Mat& dst_show,Mat& dst_threshold,int t1,int t2)
   {
        if(src.channels()!=1)
        {
            return;
        }
        int c=src.cols;
        int r=src.rows;
        Mat dst_t=Mat::zeros(r,c,CV_8UC4);
        Mat dst_t2=Mat::zeros(r,c,CV_8UC1);



        for(int i=0;i<r;i++)
        {
            for(int j=0;j<c;j++)
            {
                if(src.at<uchar>(i,j)>=t1&&src.at<uchar>(i,j)<=t2)
                {
                    dst_t.at<Vec4b>(i,j)=Vec4b(0,0,255,255);
                    dst_t2.at<uchar>(i,j)=255;
                }
                else {
                    dst_t.at<Vec4b>(i,j)=Vec4b(0,0,0,0);
                    dst_t2.at<uchar>(i,j)=0;
                }
            }
        }
        dst_show=dst_t;
        dst_threshold=dst_t2;
   }
   static vector<int> getHistogram(Mat &src)
   {
       vector<int> values;
       values.resize(256,0);
       int c=src.cols;
       int r=src.rows;
       for(int i=0;i<r;i++)
       {
           for(int j=0;j<c;j++)
           {
               values[src.at<uchar>(i,j)]++;
           }
       }
       return values;
   }

};

#endif // RALGORITHM_H
