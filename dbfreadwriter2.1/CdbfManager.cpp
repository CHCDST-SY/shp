#include "CdbfManager.h"

CdbfManager::CdbfManager()
{

}

CdbfManager::~CdbfManager()
{

}

void CdbfManager::setDbfHeadValue(dbfHead &CdbfHead)
{
       m_CdbfHead.cVersion=CdbfHead.cVersion;
       for (int i = 0; i < 3; i++) {
       m_CdbfHead.iDate[i]=CdbfHead.iDate[i];
       }
       m_CdbfHead.iRecordNumber=CdbfHead.iRecordNumber;
       m_CdbfHead.nHeadLength=CdbfHead.nHeadLength;
       m_CdbfHead.nOneRecordLength=CdbfHead.nOneRecordLength;
       for (size_t i = 0; i < CdbfHead.vec_RecordDescription.size(); i++) {
           m_CdbfHead.vec_RecordDescription.push_back(CdbfHead.vec_RecordDescription[i]);
       }
//       char cVersion;    //版本信息
//       //char acDate[3];    // 最后一次更新日期，YYMMDD
//       int iDate[3];
//       unsigned int iRecordNumber;   //文件中记录条数
//       unsigned short nHeadLength;   // 文件头字节数
//       unsigned short nOneRecordLength;   //一条记录的字节长度
//       char acReserved[20];   //0-1，添加新的说明信息性信息时使用，这里用0填写。2，未完成操作.3，dBASE IV编密码标记。。。。。。
//       vector<CdbfFieldDefine> vec_RecordDescription;//记录项描述数组
       //       char cEndMarker;
}

void CdbfManager::obtainDbfRecord(CdbfRecord &CdbfRecord)
{
    m_vecDbfRecord.push_back(CdbfRecord);
}

dbfHead &CdbfManager::getDbfHead()
{
    return m_CdbfHead;
}

CdbfRecord &CdbfManager::operator[](int i)
{
    return m_vecDbfRecord[i];
}

void CdbfManager::printRecords()
{
    int iFieldNum=(m_CdbfHead.nHeadLength-33)/32;  //字段的个数
    char cDataType;
    unsigned short cFieldPrecision;
    unsigned short iOneFieldLength;
    for (int iCyclic = 0; iCyclic < m_vecDbfRecord.size(); ++iCyclic) {
        for (int j=0;j<iFieldNum;j++) {
             cDataType=m_CdbfHead.vec_RecordDescription[j].getFieldDataType();
             cFieldPrecision=m_CdbfHead.vec_RecordDescription[j].getFieldPrecision();
             iOneFieldLength=m_CdbfHead.vec_RecordDescription[j].getFieldLength();
            switch (cDataType) {
                case 'D':
                    cout<<"date: ";
                    for(int k=0;k<3;k++){cout<<m_vecDbfRecord[iCyclic][j].m_Date[k]<<" "; }
                    cout<<endl;
                    break;
                case 'B':
                case 'C':
                case 'G':
                case 'L':
                case 'M':         //各类字符型字段值
                    cout<<"char: ";
                    for(int k=0;k<iOneFieldLength;k++){cout<<m_vecDbfRecord[iCyclic][j].m_cValues[k]; }
                    cout<<endl;
                    break;
                case 'N':
                    if(cFieldPrecision==iOneFieldLength)  //精度与长度相等，说明没有小数点位，为整型
                    {
                        cout<<"int: "<<m_vecDbfRecord[iCyclic][j].m_iNum<<" "<<endl;
                    }
                    else {    //否则即为浮点型
                        cout<<"float: "<<m_vecDbfRecord[iCyclic][j].m_dNum<<" "<<endl;
                    }
                break;
            }
        }
    }    
}
