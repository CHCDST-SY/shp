#ifndef CDBFREADER_H
#define CDBFREADER_H
#include "CdbfManager.h"
#include <fstream>
#include <vector>

class CdbfReader
{
public:
    CdbfReader();
    virtual ~ CdbfReader();
    virtual bool readDbfFile(string sDbfPath,CdbfManager & Cdata);




protected:
    void readDbfHeadData(dbfHead &CdbfHead, char data[]);
    void readDbfFieldDefine(dbfHead &CdbfHead, ifstream &inDbfFile);
    void copyFieldDefine(field &Cfield, char data[]);
    void readDbfFieldRecord(ifstream &inDbfFile, CdbfManager &Cdata,dbfHead &CdbfHead);
    void copyFieldValue(CdbfValue &Cvalue,char c[],dbfHead &CdbfHead,int jCyclic);

};

#endif // CDBFREADER_H
