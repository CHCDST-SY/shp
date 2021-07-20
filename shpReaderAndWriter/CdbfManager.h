#ifndef CDBFMANAGER_H
#define CDBFMANAGER_H
#include "CdbfRecord.h"
#include "CdbfFieldDefine.h"
#include <string>

struct dbfHead{
    char cVersion;    //版本信息
    //char acDate[3];    // 最后一次更新日期，YYMMDD
    int iDate[3];
    unsigned int iRecordNumber;   //文件中记录条数
    unsigned short nHeadLength;   // 文件头字节数
    unsigned short nOneRecordLength;   //一条记录的字节长度
   // char acReserved[20];   //0-1，添加新的说明信息性信息时使用，这里用0填写。2，未完成操作.3，dBASE IV编密码标记。。。。。。
    vector<CdbfFieldDefine> vec_RecordDescription;//记录项描述数组
   // char cEndMarker;
};

class CdbfManager
{
public:
    CdbfManager();
    virtual ~ CdbfManager();
    virtual void setDbfHeadValue(dbfHead & CdbfHead);
    virtual void obtainDbfRecord(CdbfRecord & CdbfRecord);
    virtual dbfHead & getDbfHead();
    CdbfRecord & operator[](int i);
    virtual void printRecords();
protected:
    dbfHead m_CdbfHead;
    vector<CdbfRecord> m_vecDbfRecord;

};

#endif // CDBFMANAGER_H
