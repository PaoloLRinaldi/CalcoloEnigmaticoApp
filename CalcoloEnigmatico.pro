#-------------------------------------------------
#
# Project created by QtCreator 2017-07-02T12:16:33
#
#-------------------------------------------------

QT       += core gui
QT += multimedia
CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CalcoloEnigmatico
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    calc_enig_generator.cpp \
    lab_tab.cpp \
    big_lib.cpp

HEADERS  += mainwindow.h \
    calc_enig_generator.h \
    lab_tab.h \
    big_lib.h

FORMS    += mainwindow.ui
CONFIG += qtc_runnable.
# remove possible other optimization flags
QMAKE_CXXFLAGS_RELEASE -= -O
QMAKE_CXXFLAGS_RELEASE -= -O1
QMAKE_CXXFLAGS_RELEASE -= -O3

# add the desired -O3 if not present
QMAKE_CXXFLAGS_RELEASE *= -O2

DISTFILES += \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
