#include "CdbfValue.h"

CdbfValue::CdbfValue()
{

}

CdbfValue::~CdbfValue()
{

}

void CdbfValue::setFieldValue(int iNum)
{
    this->m_iNum=iNum;
}

void CdbfValue::setFieldValue(double DNum)
{
    this->m_dNum=DNum;
}

void CdbfValue::setFieldValue(int date[])
{
    for(int i=0;i<3;i++)
    {
        this->m_Date[i]=date[i];
    }
}

void CdbfValue::setFieldValue(char cValues[], int iFieldLength)
{
    for (int i=0;i<iFieldLength;i++) {
        this->m_cValues[i]=cValues[i];
    }
}


