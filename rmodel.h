#ifndef RMODEL_H
#define RMODEL_H
#include "rheaders.h"
using namespace cv;
class RModel
{
private:
    static RModel* instance;

public:
    Mat mat_org; //orginal Mat,read Mat
    Mat mat_result;//result Mat,show Mat

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


};

#endif // RMODEL_H
