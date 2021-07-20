#ifndef CFILEWRITER_H
#define CFILEWRITER_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "CDataManager.h"
#include "Cpoint.h"
#include "Cpolyline.h"
#include "Cpolygon.h"

#define iPOINT_TYPE 1
#define iPOLYLINE_TYPE 3
#define iPOLYGON_TYPE 5

using namespace std;

class CFileWriter
{
public:
    CFileWriter();
    virtual ~CFileWriter();

    virtual bool writeShxFile(string sFilePath,CDataManager &Cdata);
    virtual bool writeShpFile(string sFilePath,CDataManager &Cdata);


protected:
    int changeByteOrder(int s);
    void getShpxHead(char acBuffer[],int iDiffer,CDataManager &Cdata);//idiffer=0，写入shx文件的长度，=1，写入shp文件的长度
    void getShxRecord(char acBuffer[],CDataManager &Cdata);
    void copyShpRecord(char acBuffer[],CDataManager &Cdata);
    void copyPointRecord(char acBuffer[],CDataManager &Cdata,int iCyclicValue);
    void copyPolyData(char acBuffer[],CDataManager &Cdata,int iShapeType);

};

#endif // CFILEWRITER_H
