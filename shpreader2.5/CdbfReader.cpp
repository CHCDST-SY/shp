#include "CdbfReader.h"

CdbfReader::CdbfReader()
{

}

CdbfReader::~CdbfReader()
{

}

bool CdbfReader::readDbfFile(string sDbfPath, CdbfManager &Cdata)
{
    ifstream inDbfFile;             //开始打开并读取shx文件
    inDbfFile.open(sDbfPath,ios::in|ios::binary);
    dbfHead CdbfHead;   //dbf文件头结构体，传值用
    char caHeadBuffer[32];
    if (!inDbfFile)
       { return false;}//false;
    else{
        //-----------读文件头-------------------//
        inDbfFile.read(caHeadBuffer,32);
        readDbfHeadData(CdbfHead,caHeadBuffer); //文件头数据传入dbfhead结构体中
        readDbfFieldDefine(CdbfHead,inDbfFile);
        Cdata.setDbfHeadValue(CdbfHead);   //dbfhead结构体数据传入datamanager对象中存储起来
        readDbfFieldRecord(inDbfFile,Cdata,CdbfHead);
    }
    inDbfFile.close();
    return true;
}

void CdbfReader::readDbfHeadData(dbfHead &CdbfHead, char data[])
{
    CdbfHead.cVersion=data[0];
    for(int i=0;i<3;i++)
    {
        CdbfHead.iDate[i]=(int)data[i+1];
    }
    CdbfHead.iRecordNumber=*((unsigned int *)(data+4));  //CdbfHead.iRecordNumber;
    CdbfHead.nHeadLength=*((unsigned short *)(data+8));//CdbfHead.nHeadLength;
    CdbfHead.nOneRecordLength=*((unsigned short *)(data+10));
}

void CdbfReader::readDbfFieldDefine(dbfHead &CdbfHead, ifstream &inDbfFile)
{
    int iFieldNum=(CdbfHead.nHeadLength-33)/32;//<<endl;
    char caFieldDefineBuffer[32];   //存读进来的一个字段描述信息
    field Cfield;  //按不同内容存caFieldDefineBuffer的数据
    for(int i=0;i<iFieldNum;i++)
    {
        inDbfFile.read(caFieldDefineBuffer,32);
        CdbfFieldDefine * pFieldDefine=new CdbfFieldDefine;
        copyFieldDefine(Cfield,caFieldDefineBuffer);//将数组caFieldDefineBuffer按内容存入field结构体中
        pFieldDefine->setFieldDefineValues(Cfield);
        CdbfHead.vec_RecordDescription.push_back(*pFieldDefine);
    }
    //char * pcEndMarker=&CdbfHead.cEndMarker;
    char  pcEndMarker;
    inDbfFile.read(&pcEndMarker,1);//读取记录项终止标识
    //cout<<"head end marker: "<<(int)*pcEndMarker<<endl;
}

void CdbfReader::copyFieldDefine(field &Cfield, char data[])
{
    for(int i=0;i<11;i++)
    {
      Cfield.caFieldName[i]=data[i];
    }
    Cfield.cDataType=data[11];
    Cfield.cFieldLength=data[16];
    Cfield.cFieldPrecision=data[17];
    Cfield.cWorkStationID=data[20];
    Cfield.cMDXMarker=data[31];
}

void CdbfReader::readDbfFieldRecord(ifstream &inDbfFile, CdbfManager &Cdata, dbfHead &CdbfHead)
{
    int iRecordNum=CdbfHead.iRecordNumber;       //一共有多少条记录
    int iFieldNum=(CdbfHead.nHeadLength-33)/32;  //字段的个数
    char cDeleteFlag;   //删除标记
    char *pDeleteFlag=&cDeleteFlag;
    int iOneFieldLength;
    char acTempFieldValue[CHAR_MAX_LENGTH]={' '};
    for(int i=0;i<iRecordNum;i++)
    {
        inDbfFile.read(pDeleteFlag,1);  //读一个删除标记，文件指针后移一位
        CdbfRecord * pDbfRecord=new CdbfRecord;
        for(int j=0;j<iFieldNum;j++)
        {
            iOneFieldLength=CdbfHead.vec_RecordDescription[j].getFieldLength();
            CdbfValue * pDbfValue=new CdbfValue;
            for(int k=0;k<CHAR_MAX_LENGTH;k++){acTempFieldValue[k]=' ';} //每次读，初始化一下数组
            inDbfFile.read(acTempFieldValue,iOneFieldLength);
            copyFieldValue(*pDbfValue,acTempFieldValue,CdbfHead,j);
            pDbfRecord->obtainDbfFieldValue(*pDbfValue);

        }
        Cdata.obtainDbfRecord(*pDbfRecord);
    }
}

void CdbfReader::copyFieldValue(CdbfValue &Cvalue, char cFieldBuffer[],dbfHead &CdbfHead,int jCyclic)
{
    
    char cDataType=CdbfHead.vec_RecordDescription[jCyclic].getFieldDataType();
    unsigned short cFieldPrecision=CdbfHead.vec_RecordDescription[jCyclic].getFieldPrecision();
    unsigned short iOneFieldLength=CdbfHead.vec_RecordDescription[jCyclic].getFieldLength();
    switch (cDataType) {
        case 'D':{
            int date[3];
            for (int i=0;i<3;i++) {
                date[i]=(int)cFieldBuffer[i];
            }
            Cvalue.setFieldValue(date);
            }break;
        case 'B':
        case 'C':
        case 'G':
        case 'L':
        case 'M':         //各类字符型字段值
            Cvalue.setFieldValue(cFieldBuffer,iOneFieldLength);//行记录对象获取字符字段的值
        break;
        case 'N':
            if(cFieldPrecision==0)//iOneFieldLength)  //精度与长度相等，说明没有小数点位，为整型
            {
                string istr(cFieldBuffer);
                int iTempFieldValue=atoi(istr.c_str());
                Cvalue.setFieldValue(iTempFieldValue); //行记录对象获取整型字段的值
            }
            else {    //否则即为浮点型
                string dstr(cFieldBuffer);
                double dTempFieldValue=atof(dstr.c_str());
                Cvalue.setFieldValue(dTempFieldValue);//行记录对象浮点型字符字段的值
            }
        break;
    }
}
