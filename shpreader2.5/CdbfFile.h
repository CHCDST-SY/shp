#ifndef CDBFFILE_H
#define CDBFFILE_H
#include "CdbfManager.h"
#include "CdbfReader.h"
#include "CdbfWriter.h"


class CdbfFile
{
public:
    CdbfFile();
    virtual ~CdbfFile();
    virtual void readDbfFile(string sFilePath);
    virtual void writeDbfFile(string sFilePath);
    virtual const CdbfManager & getDbfData();

protected:
    CdbfManager m_CdbfSaver;
    CdbfReader m_CdbfReader1;
    CdbfWriter m_CdbfWriter1;
};

#endif // CDBFFILE_H
