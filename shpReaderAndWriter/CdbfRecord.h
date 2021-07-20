#ifndef CDBFRECORD_H
#define CDBFRECORD_H
#include "CdbfValue.h"
#include <vector>

using namespace std;

class CdbfRecord
{
public:
    CdbfRecord();
    virtual ~CdbfRecord();
    virtual void obtainDbfFieldValue(CdbfValue & CfieldValue);
    //virtual void printOneRecord();
    const CdbfValue & operator[](int i);
    

protected:
    vector<CdbfValue> m_vecOneRecord;

};

#endif // CDBFRECORD_H
