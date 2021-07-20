#ifndef CDBFWRITER_H
#define CDBFWRITER_H
#include "CdbfManager.h"
#include <string>
#include <fstream>
#include <iostream>
#include "stdlib.h"


class CdbfWriter
{
public:
    CdbfWriter();
    virtual ~CdbfWriter();
    virtual bool writeDbfFile(string sFilePath,CdbfManager &Cdata);


protected:
    void copyDbfHead(char cBuffer[],CdbfManager &Cdata);
    void copyDbfFieldDefine(char cBuffer[], CdbfManager &Cdata,int iFieldNum);
    void copyDbfFieldRecord(char cBuffer[], CdbfManager &Cdata, int iCyclic);

};

#endif // CDBFWRITER_H
