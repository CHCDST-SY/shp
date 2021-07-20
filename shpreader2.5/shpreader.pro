TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        CDataManager.cpp \
        CFileReader.cpp \
        CFileWriter.cpp \
        CcoordTransfer.cpp \
        CdbfFieldDefine.cpp \
        CdbfFile.cpp \
        CdbfManager.cpp \
        CdbfReader.cpp \
        CdbfRecord.cpp \
        CdbfValue.cpp \
        CdbfWriter.cpp \
        Cpoint.cpp \
        Cpoly.cpp \
        Cpolygon.cpp \
        Cpolyline.cpp \
        Cshp.cpp \
        CshpxAndDbfFile.cpp \
        Cshx.cpp \
        main.cpp

HEADERS += \
    CDataManager.h \
    CFileReader.h \
    CFileWriter.h \
    CcoordTransfer.h \
    CdbfFieldDefine.h \
    CdbfFile.h \
    CdbfManager.h \
    CdbfReader.h \
    CdbfRecord.h \
    CdbfValue.h \
    CdbfWriter.h \
    Cpoint.h \
    Cpoly.h \
    Cpolygon.h \
    Cpolyline.h \
    Cshp.h \
    CshpxAndDbfFile.h \
    Cshx.h
