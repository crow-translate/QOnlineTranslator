QT += network multimedia

HEADERS += $$PWD/src/qonlinetranslator.h

SOURCES += $$PWD/src/qonlinetranslator.cpp

INCLUDEPATH += $$PWD/src

CONFIG += c++14

TRANSLATIONS += $$files(translations/crow_*.ts)
