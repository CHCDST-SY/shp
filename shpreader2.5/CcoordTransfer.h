#ifndef CCOORDTRANSFER_H
#define CCOORDTRANSFER_H
#include "CshpxAndDbfFile.h"

struct CviewCoordinate
{
    int x;
    int y;
};

class CcoordTransfer
{
public:
    CcoordTransfer();
    virtual ~ CcoordTransfer();
    virtual CviewCoordinate & coordRealToView(structPoint &Cpoint);
    virtual void setDs(int iwidth,double dBoundWidth);
protected:
    double m_ds;  //缩放比例
    CviewCoordinate CviewPoint;


};

#endif // CCOORDTRANSFER_H
