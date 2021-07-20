#include "CFileWriter.h"

CFileWriter::CFileWriter()
{

}

CFileWriter::~CFileWriter()
{

}

bool CFileWriter::writeShxFile(string sFilePath, CDataManager &Cdata)
{
    ofstream outShxFile;
    outShxFile.open(sFilePath,ios::out|ios::binary);
    int iShxFileLength=Cdata.getShxFileLength()*2; //16位字，乘2后才是总字节数
    if (!outShxFile)
       { return false;}//false;
    else{
        char acHeadBuffer[100];
        char * acRecordBuffer=new char[iShxFileLength-100];
        getShpxHead(acHeadBuffer,0,Cdata);
        getShxRecord(acRecordBuffer,Cdata);
        outShxFile.write(acHeadBuffer,100);
        outShxFile.write(acRecordBuffer,iShxFileLength-100);
        delete [] acRecordBuffer;
    }
    outShxFile.close();
    return true;
}

bool CFileWriter::writeShpFile(string sFilePath, CDataManager &Cdata)
{
    ofstream outShpFile;
    outShpFile.open(sFilePath,ios::out|ios::binary);
    int iShpFileLength=Cdata.getShpFileLength()*2; //16位字，乘2后才是总字节数
    if (!outShpFile)
       { return false;}//false;
    else{
        char acHeadBuffer[100];
        char * acRecordBuffer=new char[iShpFileLength-100];
        getShpxHead(acHeadBuffer,1,Cdata);
        copyShpRecord(acRecordBuffer,Cdata);
        outShpFile.write(acHeadBuffer,100);
        outShpFile.write(acRecordBuffer,iShpFileLength-100);
        delete [] acRecordBuffer;
    }
    outShpFile.close();
    return true;
}



int CFileWriter::changeByteOrder(int s)
{
        char *p=(char *)&s;
        char cTemp;
        for(int i=0;i<2;i++)
        {
            cTemp=p[i];
            p[i]=p[3-i];
            p[3-i]=cTemp;
        }
        return *((int *)p);
}

void CFileWriter::getShpxHead(char acBuffer[], int iDiffer, CDataManager &Cdata)
{
    char * pTemp=acBuffer;
    *((int *)pTemp)=changeByteOrder( Cdata.getShpxHead().ifilenum);
    pTemp+=sizeof (int);
    for(int i=0;i<5;i++)
    {
        *((int *)pTemp)=changeByteOrder( Cdata.getShpxHead().iunused[i]);
        pTemp+=sizeof (int);
    }
    if(iDiffer==0)       //idiffer=0，写入shx文件的长度，=1，写入shp文件的长度
    {
        *((int *)pTemp)=changeByteOrder( Cdata.getShpxHead().ishxfile_length);
        pTemp+=sizeof (int);
    }
    else if(iDiffer==1)
    {
        *((int *)pTemp)=changeByteOrder( Cdata.getShpxHead().ishpfile_length);
        pTemp+=sizeof (int);
    }
    *((int *)pTemp)=Cdata.getShpxHead().iversion;//version开始无需大小端转换
    pTemp+=sizeof (int);
    *((int *)pTemp)=Cdata.getShpxHead().ishape_type;
    pTemp+=sizeof (int);
    for(int i=0;i<8;i++)
    {
        *((double *)pTemp)= Cdata.getShpxHead().boundBox[i];
        pTemp+=sizeof (double);
    }
}

void CFileWriter::getShxRecord(char acBuffer[], CDataManager &Cdata)
{
    int iCount=0;
    //int iShxFileLength=Cdata.getShxFileLength()*2; //16位字，乘2后才是总字节数
    int iShxRecordNum=Cdata.getShpRecordNum();
    char *pTemp=acBuffer;
    for(iCount=0;iCount<iShxRecordNum;iCount++)
    {
        *((int *)pTemp)=changeByteOrder(Cdata.getShxRecord()[iCount]->getOffset());
        pTemp+=sizeof (int);
        *((int *)pTemp)=changeByteOrder(Cdata.getShxRecord()[iCount]->getContentLength());
        pTemp+=sizeof (int);
    }
}

void CFileWriter::copyShpRecord(char acBuffer[], CDataManager &Cdata)
{
    int iCount=0;
    //int iShxFileLength=Cdata.getShxFileLength()*2; //16位字，乘2后才是总字节数
    int iShpRecordNum=Cdata.getShpRecordNum();
    //char *pTemp=acBuffer;
    int iShapeType=Cdata.getShapeType();

        switch (iShapeType) {
        case iPOINT_TYPE:
            for(iCount=0;iCount<iShpRecordNum;iCount++)
            {
                 char cPointBuffer[28];
                 copyPointRecord(cPointBuffer,Cdata,iCount);
                 for(int i=0;i<28;i++)
                 {
                     acBuffer[iCount*28+i]=cPointBuffer[i];
                 }
            }
                break;
        case iPOLYLINE_TYPE:
        case iPOLYGON_TYPE:{
               copyPolyData(acBuffer,Cdata,iShapeType);
            }
            break;
        }

    }


void CFileWriter::copyPointRecord(char acBuffer[], CDataManager &Cdata, int iCyclicValue)
{
    char * pTemp=acBuffer;
    Cpoint *pPoint=dynamic_cast<Cpoint *>(Cdata.getShpRecord(iCyclicValue));
    *((int*)pTemp)=changeByteOrder(iCyclicValue);
    pTemp+=sizeof (int);
    *((int*)pTemp)=changeByteOrder(10);//一个点的记录内容是20字节，以16位字为单位，即10
    pTemp+=sizeof (int);
    *((int*)pTemp)=iPOINT_TYPE;
    pTemp+=sizeof (int);
    *((double*)pTemp)=(*pPoint).getPointData().x;
    pTemp+=sizeof (double);
    *((double*)pTemp)=(*pPoint).getPointData().y;
}

void CFileWriter::copyPolyData(char acBuffer[], CDataManager &Cdata, int iShapeType)
{
    char * pTemp=acBuffer;
    int contlength;   //记录长度
    int iNumParts,iNumPoints;
    for(int j=0;j<Cdata.getShpRecordNum();j++)
    {
        *((int*)pTemp)=changeByteOrder(j);     //
        pTemp+=sizeof (int);
        Cpoly *pPoint=dynamic_cast<Cpoly *>(Cdata.getShpRecord(j)); //动态转换
        contlength=44+4*pPoint->getNumParts()+16*pPoint->getNumPoints();
        *((int*)pTemp)=changeByteOrder(contlength/2);
        pTemp+=sizeof (int);
        *((int*)pTemp)=iShapeType;
        pTemp+=sizeof (int);
        for(int i=0;i<4;i++)
        {
           *((double *)pTemp)=pPoint->getBox()[i];
           pTemp+=sizeof (double);
        }
        iNumParts=pPoint->getNumParts();
        *((int *)pTemp)=iNumParts;
        pTemp+=sizeof (int);
        iNumPoints=pPoint->getNumPoints();
        *((int *)pTemp)=iNumPoints;
        pTemp+=sizeof (int);

        for(int i=0;i<iNumParts;i++)
        {
            *((int *)pTemp)=pPoint->getParts()[i];
            pTemp+=sizeof (int);
        }
        for(int i=0;i<iNumPoints;i++)
        {
            *((double *)pTemp)=pPoint->getPoints()[i].x;
            pTemp+=sizeof (double);
            *((double *)pTemp)=pPoint->getPoints()[i].y;
            pTemp+=sizeof (double);
        }
    }
}

