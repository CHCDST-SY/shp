#ifndef CDBFVALUE_H
#define CDBFVALUE_H
#define CHAR_MAX_LENGTH 64

#include <iostream>

using namespace std;

class CdbfValue
{
public:
    CdbfValue();
    virtual ~CdbfValue();
    virtual void setFieldValue(int iNum);
    virtual void setFieldValue(double DNum);
    virtual void setFieldValue(int date[]);
    virtual void setFieldValue(char cValues[],int iFieldLength);
//    virtual int getIntegerValue();
//    virtual double getFloatValue();
//    virtual const int * getDateValue();
//    virtual const char * getCharValue();

    union{
        int m_iNum; //整型数字
        double m_dNum;//浮点型数字
        char m_cValues[CHAR_MAX_LENGTH];//各种字符
        int m_Date[3]; //YYMMDD
    };

};

#endif // CDBFVALUE_H
