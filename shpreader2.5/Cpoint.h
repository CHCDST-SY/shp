#ifndef CPOINT_H
#define CPOINT_H
#include "Cshp.h"
using namespace std;

class Cpoint:public Cshp
{
public:
    Cpoint();
    virtual ~Cpoint();
    virtual void setOnePointVec(structPoint &CtempPoint);//点集中传入一个point的数据。
    virtual void printData() override;
    virtual const structPoint &getPointData();

};

#endif // CPOINT_H
