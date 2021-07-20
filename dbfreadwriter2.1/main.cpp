#include <iostream>
#include "CdbfManager.h"
#include "CdbfReader.h"
#include "CdbfWriter.h"

using namespace std;

int main()
{
    CdbfManager CdbfFileManager;
    CdbfReader CdbfReader1;
    CdbfWriter CdbfWriter1;
    //CdbfReader1.readDbfFile("C:/Users/ghj56/Desktop/readshp/map/shengjixingzhengqu.dbf",CdbfFileManager);
    CdbfReader1.readDbfFile("C:/Users/DELL/Desktop/qt-read-shp/map/shengjixingzhengqu.dbf",CdbfFileManager);
    CdbfFileManager.printRecords();
    CdbfWriter1.writeDbfFile("C:/Users/DELL/Desktop/outshp/outdbf.dbf",CdbfFileManager);

    cout << "Hello World!" << endl;
    return 0;
}
