#ifndef RALGORITHM_H
#define RALGORITHM_H
#include"rheaders.h"
#include<vector>
#include <queue>
#include<memory>
#include<time.h>
using namespace cv;
using namespace std;
struct RPoint
{
    int x,y;
    int r,c;
    RPoint(int r,int c):r(r),c(c)
    {

    }
};
struct RColor
{
    uchar r,g,b;

    RColor(int r=0,int g=0,int b=0):r(r),g(g),b(b)
    {

    }
};



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

   static void getConnectedDomainLable(Mat & src,Mat& label_mat,Mat& label_mat_show,int &connected_domin_num)
   {

       int nb[8][2]={
               {-1,-1},
               {-1,0},
               {-1,1},
               {0,-1},
               {0,1},
               {1,-1},
               {1,0},
               {1,1}
       };
       int c=src.cols;
       int r=src.rows;
       Mat dst_t=Mat::zeros(r,c,CV_32SC1);
       Mat dst_show=Mat::zeros(r,c,CV_8UC3);

       Mat src_c=src.clone();

       queue<RPoint> qrp;
       int connectedDominNum=1;
       for(int i=0;i<r;i++)
       {
           for(int j=0;j<c;j++)
           {
               if(src_c.at<uchar>(i,j)==255)
               {
                   src_c.at<uchar>(i,j)=0;
                   qrp.push(RPoint(i,j));

                    while(!qrp.empty())
                    {
                        RPoint rp=qrp.front();
                        dst_t.at<int>(rp.r,rp.c)=connectedDominNum;

                        qrp.pop();
                        for(int k=0;k<8;k++)
                        {
                            int nr=rp.r+nb[k][0];
                            int nc=rp.c+nb[k][1];

                            if(nr<0 ||nr>=r || nc<0 || nc>=c)
                            {
                                continue;
                            }
                            if(src_c.at<uchar>(nr,nc)==255)
                            {
                                src_c.at<uchar>(nr,nc)=0;
                                qrp.push(RPoint(nr,nc));
                            }
                        }
                    }
                    connectedDominNum++;
               }
           }
       }
       label_mat=dst_t;
       RColor *rcp=new RColor[connectedDominNum];
       srand(time(0));
       for(int i=0;i<connectedDominNum;i++)
       {
           rcp[i].r=rand()%256;
           rcp[i].g=rand()%256;
           rcp[i].b=rand()%256;
       }
       for(int i=0;i<r;i++)
       {
           for(int j=0;j<c;j++)
           {
               int t=dst_t.at<int>(i,j);
               if(t!=0)
               {
                   RColor &rc=rcp[t];
                   dst_show.at<Vec3b>(i,j)=Vec3b(rc.r,rc.g,rc.b);
               }
           }
       }
       label_mat_show=dst_show;

       connected_domin_num=connectedDominNum-1;
       delete[] rcp;
   }
   static bool isBinary(Mat &src)
    {
        if(src.channels()!=1)
        {
            return false;
        }
        int c=src.cols;
        int r=src.rows;

        for(int i=0;i<r;i++) {
            for (int j = 0; j < c; j++) {
                if (src.at<uchar>(i, j) != 255 && src.at<uchar>(i, j) != 0) {
                    return false;
                }
            }
        }
        return true;

    }
   static void morphology(Mat &src,Mat &dst,MorphTypes mt,int size)
   {
       Mat element = getStructuringElement(MORPH_ELLIPSE, Size(size, size));
       morphologyEx(src, dst, mt, element);
   }
};

#endif // RALGORITHM_H

















