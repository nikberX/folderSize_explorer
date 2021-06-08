QT       += core gui
QT       += charts
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        Strategies/filetypestrategy.cpp \
        Strategies/folderstrategy.cpp \
        barchart.cpp \
        barchartadapter.cpp \
        chart.cpp \
        fileexplorermodel.cpp \
        fileexplorerobserver.cpp \
        listadapter.cpp \
        main.cpp \
        mainwindow.cpp \
        piechart.cpp \
        piechartadapter.cpp \
        sizecalculator.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    FileData.h \
    Strategies/filetypestrategy.h \
    Strategies/folderstrategy.h \
    barchart.h \
    barchartadapter.h \
    calculationstrategy.h \
    chart.h \
    fileexplorerlistener.h \
    fileexplorermodel.h \
    fileexplorerobserver.h \
    listadapter.h \
    mainwindow.h \
    piechart.h \
    piechartadapter.h \
    sizecalculator.h
