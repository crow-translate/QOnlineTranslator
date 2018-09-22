QT += network multimedia

HEADERS += $$PWD/src/qonlinetranslator.h \
    $$PWD/src/qdefinition.h \
    $$PWD/src/qdictionary.h

SOURCES += $$PWD/src/qonlinetranslator.cpp \
    $$PWD/src/qdefinition.cpp \
    $$PWD/src/qdictionary.cpp

INCLUDEPATH += $$PWD/src

CONFIG += c++14
