#include "CdbfFile.h"

CdbfFile::CdbfFile()
{

}

CdbfFile::~CdbfFile()
{

}

void CdbfFile::readDbfFile(string sFilePath)
{
    m_CdbfReader1.readDbfFile(sFilePath,m_CdbfSaver);
}

void CdbfFile::writeDbfFile(string sFilePath)
{
    m_CdbfWriter1.writeDbfFile(sFilePath,m_CdbfSaver);
}

const CdbfManager &CdbfFile::getDbfData()
{
    return m_CdbfSaver;
}
