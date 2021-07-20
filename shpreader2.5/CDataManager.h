#ifndef CDATAMANAGER_H
#define CDATAMANAGER_H
#include <iostream>
#include <vector>
//#include "CFileReader.h"

#include "Cshp.h"
#include "Cshx.h"

#include <string>
using namespace std;





struct shpxfilehead            //shp和shx文件的头结构体
{
    int ifilenum;
    int iunused[5],ishpfile_length,iversion,ishape_type,ishxfile_length;
    double boundBox[8];   //0-7分别表示xmin ymin xmax ymax zmin zmax mmin mmax
};


class CDataManager
{
public:
    CDataManager();
    virtual ~CDataManager();
    void setShxHeadData(shpxfilehead &Chead);//写入shx文件头内容
    void setShpFileLength(int iFileLength);


    void obtainShxPointer(Cshx * pShx);//shx *的指针pushback到vector中
    void obtainShpPointer(Cshp * pShp);//shp *的指针pushback到vector中

    int getShxFileLength(); //返回shx文件的长度
    int getShpRecordNum();//返回shp文件的记录数(shx文件的记录数与之相同)
    int getShpFileLength();
    int getShapeType();
    const shpxfilehead &getShpxHead(); //返回shp和shx文件头结构体的引用
    const vector<Cshx *> & getShxRecord();
     Cshp * getShpRecord(int i);



    void printShpxData();

    Cshx * operator[](int i);

protected:
    shpxfilehead m_CshpAndShxHead;   //shp和shx文件头结构体
    vector <Cshp *> m_vec_shpRecord;
    vector <Cshx *> m_vec_shxRecord;

};

#endif // CDATAMANAGER_H
