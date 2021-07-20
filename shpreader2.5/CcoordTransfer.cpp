#include "CcoordTransfer.h"

CcoordTransfer::CcoordTransfer()
{

}

CcoordTransfer::~CcoordTransfer()
{

}

CviewCoordinate &CcoordTransfer::coordRealToView(structPoint &Cpoint)
{

    CviewPoint.x=Cpoint.x*m_ds;
    CviewPoint.y=Cpoint.y*m_ds;
    return CviewPoint;
}

void CcoordTransfer::setDs(int iwidth, double dBoundWidth)
{
    m_ds=iwidth/dBoundWidth;
}
