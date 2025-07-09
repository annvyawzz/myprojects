QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bag.cpp \
    fruit.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    abs_comp.h \
    bag.h \
    fruit.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    build/Desktop_Qt_6_9_0_MinGW_64_bit-Debug/Ob.txt \
    build/Desktop_Qt_6_9_0_MinGW_64_bit-Debug/Ob1.txt \
    build/Desktop_Qt_6_9_0_MinGW_64_bit-Debug/Ob2.txt \
    build/Desktop_Qt_6_9_0_MinGW_64_bit-Debug/TOb.txt \
    build/Desktop_Qt_6_9_0_MinGW_64_bit-Debug/TOb1.txt \
    build/Desktop_Qt_6_9_0_MinGW_64_bit-Debug/TOb2.txt
