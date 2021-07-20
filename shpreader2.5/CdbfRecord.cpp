#include "CdbfRecord.h"

CdbfRecord::CdbfRecord()
{

}

CdbfRecord::~CdbfRecord()
{

}

void CdbfRecord::obtainDbfFieldValue(CdbfValue &CfieldValue)
{
    m_vecOneRecord.push_back(CfieldValue);
}

const CdbfValue &CdbfRecord::operator[](int i)
{
    return m_vecOneRecord[i];
}
