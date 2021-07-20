#ifndef CFILEREADER_H
#define CFILEREADER_H
#include "CDataManager.h"
#include <vector>
#include <fstream>
#include <iostream>
#include "Cpoint.h"
#include "Cpolyline.h"
#include "Cpolygon.h"
#include <stdlib.h>
#include <string>
#define ipointsize 28
#define iPOINT_TYPE 1
#define iPOLYLINE_TYPE 3
#define iPOLYGON_TYPE 5
using namespace std;



class CFileReader
{
public:
    CFileReader();
    virtual ~CFileReader();
    virtual void readFile(string sFilePath,CDataManager & Cdata);

protected:

    bool readShpFile(string sShpPath,CDataManager & Cdata);
    //void readShpHeadData(CDataManager & Cdata,char data[]);
    void readPointData(ifstream &inshpfile,Cpoint  * tmpPoint);
    void readPolyData(ifstream &inshpfile,Cshp * tmpPoly);

    bool readShxFile(string sShxPath,CDataManager &Cdata);         //使用时，先读shx，再读shp
    void readShxHeadData(CDataManager &Cdata,char data[]);
    void readShxRecordData(ifstream &inShxFile,Cshx *tmpShx);



    int changeByteOrder(int s);


};

#endif // CFILEREADER_H
