#include "CdbfWriter.h"

CdbfWriter::CdbfWriter()
{

}

CdbfWriter::~CdbfWriter()
{

}

bool CdbfWriter::writeDbfFile(string sFilePath, CdbfManager &Cdata)
{
    ofstream outDbfFile;             //开始打开并准备输出dbf文件
    outDbfFile.open(sFilePath,ios::out|ios::binary);
    char caHeadBuffer[32];
    if (!outDbfFile)
       { return false;}//false;
    else{
        copyDbfHead(caHeadBuffer,Cdata);
        int iFieldNum=(Cdata.getDbfHead().nHeadLength-33)/32;
        char * pFieldDefineBuffer=new char[iFieldNum*32];
        copyDbfFieldDefine(pFieldDefineBuffer,Cdata,iFieldNum);
        char reserved[20]={0};
        char cEndMarker=13;   //文件头结束标记
        outDbfFile.write(caHeadBuffer,12);
        outDbfFile.write(reserved,20);
        outDbfFile.write(pFieldDefineBuffer,iFieldNum*32);
        outDbfFile.write(&cEndMarker,1);
        int iOneRecordLength=Cdata.getDbfHead().nOneRecordLength;
        int iRecordNum=Cdata.getDbfHead().iRecordNumber;
        char * cFieldsRecord=new char[iOneRecordLength];

        char cDeleteFlag=32;
        char *p=&cDeleteFlag;
        for(int i=0;i<iRecordNum;i++)
        {
            outDbfFile.write(p,1);
            //cout<<"record: "<<i<<endl;
            for (int k=0;k<iOneRecordLength;k++) {cFieldsRecord[k]=' ';} //初始化数组
            copyDbfFieldRecord(cFieldsRecord,Cdata,i);   //拷贝一条记录的字段值到cfieldrecord数组中

            outDbfFile.write(cFieldsRecord,iOneRecordLength-1);//一条记录长度中包含了删除标记这个字节的长度
        }
        delete [] cFieldsRecord;
        delete [] pFieldDefineBuffer;
    }
    outDbfFile.close();
    return true;
}

void CdbfWriter::copyDbfHead(char cBuffer[], CdbfManager &Cdata)
{
    char *pTemp=cBuffer;
    cBuffer[0]=Cdata.getDbfHead().cVersion;
    pTemp+=1;
    for(int i=0;i<3;i++)
    {
        cBuffer[i+1]=Cdata.getDbfHead().iDate[i];
        pTemp+=1;
    }
    *((unsigned int *)pTemp)=Cdata.getDbfHead().iRecordNumber;
    pTemp+=sizeof (unsigned int);
    *((unsigned short *)pTemp)=Cdata.getDbfHead().nHeadLength;
    pTemp+=sizeof (unsigned short);
    *((unsigned short *)pTemp)=Cdata.getDbfHead().nOneRecordLength;
    pTemp+=sizeof (unsigned short);
//    for(int i=0;i<20;i++)
//    {
//        *pTemp=Cdata.getDbfHead().acReserved[i];
//        pTemp+=1;
//    }
}

void CdbfWriter::copyDbfFieldDefine(char cBuffer[], CdbfManager &Cdata, int iFieldNum)
{
    char * pTemp=cBuffer;
    for(int i=0;i<iFieldNum;i++)
    {
        for(int jCyclic=0;jCyclic<11;jCyclic++)
        {
            *pTemp=Cdata.getDbfHead().vec_RecordDescription[i].getFieldName()[jCyclic];
            pTemp+=1;
        }
        *pTemp=Cdata.getDbfHead().vec_RecordDescription[i].getFieldDataType();
        pTemp+=1;
        for(int j=0;j<4;j++)
        {
            *pTemp=0;
            pTemp+=1;
        }
        *pTemp=(char)Cdata.getDbfHead().vec_RecordDescription[i].getFieldLength();
        pTemp+=1;
        //cout<<"field "<<i<<" length: "<<(int)(*Cdata.getDbfHead().vec_RecordDescription[i]).getFieldDefine().cFieldLength<<endl;
        *pTemp=(char)Cdata.getDbfHead().vec_RecordDescription[i].getFieldPrecision();
        pTemp+=1;
        for(int j=0;j<2;j++)
        {
            *pTemp=0;
            pTemp+=1;
        }
        *pTemp=Cdata.getDbfHead().vec_RecordDescription[i].getWorkStationID();
        pTemp+=1;
        for(int j=0;j<10;j++)
        {
            *pTemp=0;
            pTemp+=1;
        }
        *pTemp=Cdata.getDbfHead().vec_RecordDescription[i].getMDXMarker();
        pTemp+=1;
    }
}

void CdbfWriter::copyDbfFieldRecord(char cBuffer[], CdbfManager &Cdata, int iCyclic)
{
    int iFieldNum=(Cdata.getDbfHead().nHeadLength-33)/32;  //字段的个数
    int iControl=0;

    //char iFieldLength;
    char cDataType;
    unsigned short cFieldPrecision;
    unsigned short iOneFieldLength;
    char cTemp[CHAR_MAX_LENGTH];
    for(int i=0;i<iFieldNum;i++)
    {
        //cout<<"field: "<<i<<endl;
        for(int k=0;k<CHAR_MAX_LENGTH;k++){cTemp[k]=' ';}   // 每次拷贝初始化一下
        cDataType=Cdata.getDbfHead().vec_RecordDescription[i].getFieldDataType();
        iOneFieldLength=Cdata.getDbfHead().vec_RecordDescription[i].getFieldLength();
        cFieldPrecision=Cdata.getDbfHead().vec_RecordDescription[i].getFieldPrecision();
            switch (cDataType) {
                case 'D':
                    for (int k=0;k<3;k++) {
                        cBuffer[iControl]=(char)Cdata[iCyclic][i].m_Date[k];
                        iControl+=1;}
                    break;
                case 'B':
                case 'C':
                case 'G':
                case 'L':
                case 'M':         //各类字符型字段值
                    for(int j=0;j<iOneFieldLength;j++)
                    {
                        cBuffer[iControl]=Cdata[iCyclic][i].m_cValues[j];
                        iControl+=1;
                    }
                break;
                case 'N':
                    if(cFieldPrecision==0)//iOneFieldLength)  //精度与长度相等，说明没有小数点位，为整型
                    {
//                        stringstream ss;
//                        ss<<Cdata[iCyclic][i].m_iNum;
                        string str=to_string(Cdata[iCyclic][i].m_iNum);//ss.str();
                        int iDigits=str.size();
                        for(int j=0;j<iOneFieldLength-iDigits;j++)
                        {
                            cBuffer[iControl]=' ';
                            iControl+=1;
                        }
                        //cout<<"length: "<<iOneFieldLength<<"precision: "<<cFieldPrecision<<"data: "<<Cdata[iCyclic][i].m_iNum<<endl;

                        strcpy(cTemp,str.c_str());
                        //itoa(Cdata[iCyclic][i].m_iNum,cTemp,iOneFieldLength);
                        for(int j=0;j<iDigits;j++)
                        {
                            cBuffer[iControl]=cTemp[j];
                            iControl+=1;
                        }
//                        ss.clear();
                    }
                    else {    //否则即为浮点型


                        string str=to_string(Cdata[iCyclic][i].m_dNum);//ss.str();
                        int iDigits=str.size();
                        if(iDigits<=iOneFieldLength)
                        {
                            for(int j=0;j<iOneFieldLength-iDigits;j++)
                            {
                                cBuffer[iControl]=' ';
                                iControl+=1;
                            }
//                            cout<<"length: "<<iOneFieldLength<<"precision: "<<cFieldPrecision<<"data: ";
//                            printf("%.6f",Cdata[iCyclic][i].m_dNum);
//                            cout<<"stringlength: "<<iDigits<<endl;
                            //<<Cdata[iCyclic][i].m_dNum<<endl;
                            sprintf(cTemp,"%f",Cdata[iCyclic][i].m_dNum);
                            for(int j=0;j<iDigits;j++)
                            {
                                cBuffer[iControl]=cTemp[j];
                                iControl+=1;
                            }
                        }
                        else {
                            stringstream ss;
                            ss<<Cdata[iCyclic][i].m_dNum;
                            string str=ss.str();
                            int iDigits=str.size();
                            for(int j=0;j<iOneFieldLength-iDigits;j++)
                            {
                                cBuffer[iControl]=' ';
                                iControl+=1;
                            }
//                            cout<<"length: "<<iOneFieldLength<<"precision: "<<cFieldPrecision<<"data: ";
//                            printf("%.6f",Cdata[iCyclic][i].m_dNum);
//                            cout<<"stringlength: "<<iDigits<<endl;
                            //<<Cdata[iCyclic][i].m_dNum<<endl;
                            strcpy(cTemp,str.c_str());
                            //sprintf(cTemp,"%f",Cdata[iCyclic][i].m_dNum);
                            for(int j=0;j<iDigits;j++)
                            {
                                cBuffer[iControl]=cTemp[j];
                                iControl+=1;
                            }
                            ss.clear();
                            }

//
                    }
                break;
            }//cout<<"icontrol: "<<iControl<<endl;
    }
}
