#ifndef CSHX_H
#define CSHX_H
#include "iostream"

using namespace std;

class Cshx
{
public:
    Cshx();
    virtual ~Cshx();
    void setAttributeValue(int iOffset,int iContentLength );
    virtual int getOffset();
    virtual int getContentLength();
protected:
    int m_iOffset; //大端序，16位字，记录的是文件头开始到该记录的偏移量，如第一条记录该值为50
    int m_iContentLength; //与shp文件每条记录的记录头相同，大端序，16位字

};

#endif // CSHX_H
