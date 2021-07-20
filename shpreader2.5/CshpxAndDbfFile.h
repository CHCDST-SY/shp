#ifndef CSHPXANDDBFFILE_H
#define CSHPXANDDBFFILE_H
#include "CFileReader.h"
#include "CFileWriter.h"
#include "CdbfFile.h"
#include "CDataManager.h"

class CshpxAndDbfFile
{
public:
    CshpxAndDbfFile();
    virtual ~CshpxAndDbfFile();
    virtual void readShpxAndDbf(string sFilePath);
    virtual void writeShpxAndDbf(string sFilePath);


protected:
    CDataManager m_CdataSaver;
    CdbfFile m_Cdbf;
    CFileReader m_Creader;
    CFileWriter m_Cwriter;



};

#endif // CSHPXANDDBFFILE_H
