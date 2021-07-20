#include "CdbfFieldDefine.h"

CdbfFieldDefine::CdbfFieldDefine()
{

}

CdbfFieldDefine::~CdbfFieldDefine()
{

}

void CdbfFieldDefine::setFieldDefineValues(field &Cfield)
{
    memcpy(m_CfieldDefine.caFieldName,Cfield.caFieldName,11);
    m_CfieldDefine.cDataType=Cfield.cDataType;
    m_CfieldDefine.cFieldLength=Cfield.cFieldLength;
    m_CfieldDefine.cFieldPrecision=Cfield.cFieldPrecision;
    m_CfieldDefine.cWorkStationID=Cfield.cWorkStationID;
    m_CfieldDefine.cMDXMarker=Cfield.cMDXMarker;

}

int CdbfFieldDefine::getFieldLength()
{
    return (int)m_CfieldDefine.cFieldLength;
}

char CdbfFieldDefine::getFieldDataType()
{
    return m_CfieldDefine.cDataType;
}

unsigned short CdbfFieldDefine::getFieldPrecision()
{
    return m_CfieldDefine.cFieldPrecision;
}

const char *CdbfFieldDefine::getFieldName()
{
    return m_CfieldDefine.caFieldName;
}

char CdbfFieldDefine::getWorkStationID()
{
    return m_CfieldDefine.cWorkStationID;
}

char CdbfFieldDefine::getMDXMarker()
{
    return m_CfieldDefine.cMDXMarker;
}
