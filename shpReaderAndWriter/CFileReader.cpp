#include "CFileReader.h"

CFileReader::CFileReader()
{

}

CFileReader::~CFileReader()
{

}

void CFileReader::readFile(string sFilePath, CDataManager &Cdata)
{
    const char *d=".";
    size_t pos = sFilePath.find(d);
    string sFomerPath=sFilePath.substr(0,pos);
    string sShxpath=sFomerPath+".shx";      //将shp文件路径前缀取出，后缀替换为.shx
    string sDbfpath=sFomerPath+".dbf";
    readShxFile(sShxpath,Cdata);         //先读shx，再读shp
    readShpFile(sFilePath,Cdata);
    //readDbfFile(sDbfpath,Cdata);
}

bool CFileReader::readShpFile(string sShpPath, CDataManager & Cdata)
{
    ifstream inShpFile;
    inShpFile.open(sShpPath,ios::in|ios::binary);
    if (!inShpFile)
       { return false;}//false;
    else{
        char caHeadBuffer[100];
        inShpFile.read(caHeadBuffer,100); //读文件头，使文件指针指向记录开始处
        int iShpFileLength=changeByteOrder(*((int *)(caHeadBuffer+24)));
        Cdata.setShpFileLength(iShpFileLength); //设置shp文件长度值
        int iShapeType=*((int *)(caHeadBuffer+32));
        Cshp * pTmp;
       for(int i=0;i<Cdata.getShpRecordNum();i++) {
            switch (iShapeType) {
            case iPOINT_TYPE:{
                     Cpoint * tmpPoint=new Cpoint;
                     readPointData(inShpFile,tmpPoint);
                     pTmp=tmpPoint;
                }
                    break;
            case iPOLYLINE_TYPE:{
                    Cpolyline *tmpPolyLine=new Cpolyline;
                    readPolyData(inShpFile,tmpPolyLine);
                    pTmp = tmpPolyLine;
                }
                break;
            case iPOLYGON_TYPE:{
                    Cpolygon *tmpPolygon=new Cpolygon;
                    readPolyData(inShpFile,tmpPolygon);
                    pTmp=tmpPolygon;
                }
                break;
            }
            Cdata.obtainShpPointer(pTmp);
            //vec_shpRecord.push_back(tmp);
        }
    inShpFile.close();
    }
    return true;
}

void CFileReader::readPointData(ifstream &inshpfile, Cpoint *tmpPoint)
{
    char cPointRecBuffer[28]; //点记录长度的数组。存每一条点记录
    inshpfile.read(cPointRecBuffer,ipointsize);
    char *pcTmp=cPointRecBuffer+sizeof (int)*2; //直接跳过record number和content length
    int iShapeType=*((int *)pcTmp);
    pcTmp+=sizeof(int);
    double dX=*((double *)pcTmp);
    pcTmp+=sizeof(double);
    double dY=*((double *)pcTmp);
    pcTmp+=sizeof(double);
    structPoint CtempPoint={dX,dY};
    tmpPoint->setOnePointVec(CtempPoint);
    //tmpPoint->inputData(iShapeType,dX,dY);
}

void CFileReader::readPolyData(ifstream &inshpfile, Cshp *tmpPoly)
{
    int contlength;   //记录头
    char cRecHeadBufr[8]; //8字节的记录头数组
    char *pRecContent;           //存每条记录的记录内容的数组
    int iShapeType,iNumParts,iNumPoints;
    double adBox[4];
    int * piParts;
    structPoint * pCpoints;      //point结构体临时变量，准备new空间存储记录内容
    inshpfile.read(cRecHeadBufr,8); //先直接读取一个记录头（8字节）进来
    contlength=changeByteOrder(*((int *)(cRecHeadBufr+sizeof (int)))); //直接读取记录内容的长度
//-----------读取记录内容--------------//
    pRecContent=new char[contlength*2]; //申请content length长度的数组
    inshpfile.read(pRecContent,contlength*2); //读取一条记录长度的数据进来reccontent数组
//-------------将记录内容赋给临时存储变量------------//
    char *pTemp=pRecContent;
    iShapeType=*((int *)pTemp);//四字节读出给shapetype
    pTemp+=sizeof (int);
    for(int i=0;i<4;i++)
    {
       adBox[i]=*((double *)pTemp);
       pTemp+=sizeof (double);
    }
    iNumParts=*((int *)pTemp);
    pTemp+=sizeof (int);
    iNumPoints=*((int *)pTemp);
    pTemp+=sizeof (int);
    piParts=new int[iNumParts];         //申请空间
    pCpoints=new structPoint[iNumPoints];
    for(int i=0;i<iNumParts;i++)
    {
        piParts[i]=*((int *)pTemp);
        pTemp+=sizeof (int);
    }
    for(int i=0;i<iNumPoints;i++)
    {
        pCpoints[i].x=*((double *)pTemp);
        pTemp+=sizeof (double);
        pCpoints[i].y=*((double *)pTemp);
        pTemp+=sizeof (double);
    }
 //-------临时变量的值根据shapetype传给不同的临时poly对象，并存储起来-----------//
    switch (iShapeType) {
    case iPOLYLINE_TYPE:{
        Cpolyline * pPolyline=dynamic_cast<Cpolyline *>(tmpPoly);
        pPolyline->setBox(adBox);
        pPolyline->setPartsVec(piParts,iNumParts);
        pPolyline->setPointsVec(pCpoints,iNumPoints);}
        //pPolyline->inputData(iShapeType,adBox,iNumParts,iNumPoints,piParts,pCpoints);}
        break;
    case iPOLYGON_TYPE:{
        Cpolygon *pPolygon=dynamic_cast<Cpolygon *>(tmpPoly);//new polygon ();
        pPolygon->setBox(adBox);
        pPolygon->setPartsVec(piParts,iNumParts);
        pPolygon->setPointsVec(pCpoints,iNumPoints);}
       // pPolygon->inputData(iShapeType,adBox,iNumParts,iNumPoints,piParts,pCpoints);}
        break;
    }
    delete [] pRecContent;
    delete [] piParts;
    delete [] pCpoints;
}

bool CFileReader::readShxFile(string sShxPath, CDataManager &Cdata)
{
    ifstream inShxFile;             //开始打开并读取shx文件
    inShxFile.open(sShxPath,ios::in|ios::binary);
    char caHeadBuffer[100];
    int iRecordNum=0;       //一共有多少条记录
    int iCount=0;          //记录读取计数器，记录读取的记录条数
    if (!inShxFile)
       { return false;}//false;
    else{
        //-----------读文件头-------------------//
        inShxFile.read(caHeadBuffer,100);
        readShxHeadData(Cdata,caHeadBuffer);
        int iShxFileLength=Cdata.getShxFileLength();
        iRecordNum=(iShxFileLength*2-100)/8; //shx文件记录的长度固定8字节，可直接算出有多少条记录
        for(iCount=0;iCount<iRecordNum;iCount++)
        {
           Cshx * tmpShx=new Cshx;
           readShxRecordData(inShxFile,tmpShx);
           Cdata.obtainShxPointer(tmpShx);
        }
    }
    inShxFile.close();
    return true;
    //-----------shx文件读取完毕-------------------//
}

void CFileReader::readShxHeadData(CDataManager &Cdata, char data[])
{
    shpxfilehead CtempHead;  //临时文件头结构体
    char * ptmp=data;
    CtempHead.ifilenum=changeByteOrder(*((int *)ptmp));
    ptmp+=sizeof (int);
    for(int i=0;i<5;i++){
        CtempHead.iunused[i]=changeByteOrder(*((int *)ptmp));
        ptmp+=sizeof (int);
    }
    CtempHead.ishxfile_length=changeByteOrder(*((int *)ptmp));
    ptmp+=sizeof (int);
    CtempHead.iversion=*((int *)ptmp);     //从此开始为小端序，无需转换
    ptmp+=sizeof (int);
    CtempHead.ishape_type=*((int *)ptmp);
    ptmp+=sizeof (int);
    for(int i=0;i<8;i++)
    {
        CtempHead.boundBox[i]=*((double *)ptmp);
        ptmp+=sizeof (double);
    }
    Cdata.setShxHeadData(CtempHead); //临时文件头的数据传入cdatamanager对象中
}

void CFileReader::readShxRecordData(ifstream &inShxFile, Cshx *tmpShx)
{
    char caShxRecBuffer[8]; //点记录长度的数组。存每一条点记录
    inShxFile.read(caShxRecBuffer,sizeof (int)*2);
    int iOffset=changeByteOrder(*((int *)caShxRecBuffer));
    int iContentLength=changeByteOrder(*((int *)(caShxRecBuffer+4)));
    tmpShx->setAttributeValue(iOffset,iContentLength);
}

int CFileReader::changeByteOrder(int s)
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
