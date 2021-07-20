#include <iostream>
#include "CDataManager.h"
#include "CFileReader.h"
#include "CFileWriter.h"
#include "CdbfManager.h"
#include "CdbfWriter.h"
#include "CdbfReader.h"
#include <iostream>
using namespace std;

int main()
{
    CDataManager CdataSaver;
    CdbfManager CdbfSaver;
    CdbfReader CdbfReader1;
    CdbfWriter CdbfWriter1;

    CFileReader reader;
    CFileWriter Cwriter;
    CdbfReader1.readDbfFile("C:/Users/DELL/Desktop/qt-read-shp/map/shengjixingzhengqu.dbf",CdbfSaver);
    //CdbfReader1.readDbfFile("C:/Users/DELL/Desktop/qt-read-shp/map/guojiexian.dbf",CdbfSaver);
    //CdbfReader1.readDbfFile("C:/Users/DELL/Desktop/qt-read-shp/map/dijichengshizhudi.dbf",CdbfSaver);


    //reader.readFile("C:/Users/DELL/Desktop/qt-read-shp/map/dijichengshizhudi.shp",CdataSaver);
    //reader.readFile("C:/Users/DELL/Desktop/qt-read-shp/map/guojiexian.shp",CdataSaver);
    reader.readFile("C:/Users/DELL/Desktop/qt-read-shp/map/shengjixingzhengqu.shp",CdataSaver);
    //reader.readFile("C:/Users/ghj56/Desktop/readshp/map/shengjixingzhengqu.shp",CdataSaver);
    //CdataSaver.printDbfRecordValue();

    CdbfWriter1.writeDbfFile("C:/Users/DELL/Desktop/outshp/1.dbf",CdbfSaver);
    Cwriter.writeShxFile("C:/Users/DELL/Desktop/outshp/1.shx",CdataSaver);
    Cwriter.writeShpFile("C:/Users/DELL/Desktop/outshp/1.shp",CdataSaver);
   // Cwriter.writeDbfFile("C:/Users/DELL/Desktop/outshp/1.dbf",CdataSaver);

    //CdataSaver.printShpxData();
    return 0;
}
