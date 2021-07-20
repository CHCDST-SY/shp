#ifndef CDBFFIELDDEFINE_H
#define CDBFFIELDDEFINE_H
//#include "stdlib.h"
#include <string>



struct field{
    char caFieldName[11];
    char cDataType;
    //char caReserved[4];
    unsigned short cFieldLength;
    unsigned short cFieldPrecision;
    //char caReserved2[2];
    char cWorkStationID;
    //char caReserved3[10];            三个位置的保留字节，写回去时均用0填充
    char cMDXMarker;
};
//enum {B,C,G,L,M,N,}
class CdbfFieldDefine
{
public:
    CdbfFieldDefine();
    virtual ~ CdbfFieldDefine();
//    virtual void setFieldNum(char cName[]);
//    virtual void setDataType(char cDataType);
//    virtual void setFieldLength(char cFieldLength);
//    virtual void setFieldPrecision(char cFieldPrecision);
//    virtual void setWorkstationID(char cWorkstationID);
//    virtual void setMDXMarker(char cMDXMarker);
    virtual void setFieldDefineValues(field & Cfield);
    virtual int getFieldLength();
    virtual char getFieldDataType();
    virtual unsigned short getFieldPrecision();
    virtual const char *getFieldName();
    virtual char getWorkStationID();
    virtual char getMDXMarker();

protected:
    field m_CfieldDefine;

};

#endif // CDBFFIELDDEFINE_H
