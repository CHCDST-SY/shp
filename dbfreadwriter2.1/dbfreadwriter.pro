TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        CdbfFieldDefine.cpp \
        CdbfManager.cpp \
        CdbfReader.cpp \
        CdbfRecord.cpp \
        CdbfValue.cpp \
        CdbfWriter.cpp \
        main.cpp

HEADERS += \
    CdbfFieldDefine.h \
    CdbfManager.h \
    CdbfReader.h \
    CdbfRecord.h \
    CdbfValue.h \
    CdbfWriter.h
