#include "CshpxAndDbfFile.h"

CshpxAndDbfFile::CshpxAndDbfFile()
{

}

CshpxAndDbfFile::~CshpxAndDbfFile()
{

}

void CshpxAndDbfFile::readShpxAndDbf(string sFilePath)
{
    const char *d=".";
    size_t pos = sFilePath.find(d);
    string sFomerPath=sFilePath.substr(0,pos);
    //string sShxpath=sFomerPath+".shx";      //将shp文件路径前缀取出，后缀替换为.shx
    string sDbfpath=sFomerPath+".dbf";
    m_Creader.readFile(sFilePath,m_CdataSaver);
    m_Cdbf.readDbfFile(sDbfpath);

}

void CshpxAndDbfFile::writeShpxAndDbf(string sFilePath)
{
    const char *d=".";
    size_t pos = sFilePath.find(d);
    string sFomerPath=sFilePath.substr(0,pos);
    string sShxpath=sFomerPath+".shx";      //将shp文件路径前缀取出，后缀替换为.shx
    string sDbfpath=sFomerPath+".dbf";
    m_Cdbf.writeDbfFile(sDbfpath);
    m_Cwriter.writeShpFile(sFilePath,m_CdataSaver);
    m_Cwriter.writeShxFile(sShxpath,m_CdataSaver);

}
