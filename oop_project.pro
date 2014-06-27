#-------------------------------------------------
#
# Project created by QtCreator 2014-06-17T21:31:14
#
#-------------------------------------------------

QT       += core gui
QT       +=xml
QT       +=xmlpatterns
QT       +=sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = oop_project
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    loginwindow.cpp \
    database.cpp

HEADERS  += mainwindow.h \
    loginwindow.h \
    database.h
