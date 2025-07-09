#-------------------------------------------------
#
# Project created by QtCreator 2015-09-24T19:55:44
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = paint
TEMPLATE = app


SOURCES += main.cpp\
    figure.cpp \
        paint.cpp \
    paintarea.cpp \
    paintscene.cpp \
    romb.cpp \
    simplemenu.cpp \
    square.cpp \
    triangle.cpp

HEADERS  += paint.h \
    figure.h \
    paintarea.h \
    paintscene.h \
    romb.h \
    simplemenu.h \
    square.h \
    triangle.h

FORMS    += paint.ui

DISTFILES += \
    build/Desktop_Qt_6_9_0_MinGW_64_bit-Debug/dannye
