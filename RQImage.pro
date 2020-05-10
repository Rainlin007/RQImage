#-------------------------------------------------
#
# Project created by QtCreator 2019-04-18T11:44:49
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RQImage
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# OpenCV include path
INCLUDEPATH += /usr/local/include
INCLUDEPATH += /usr/local/include/opencv4
INCLUDEPATH += /usr/local/include/opencv4/opencv2

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    rmodel.cpp \
    rutils.cpp \
    rview.cpp \
    ralgorithm.cpp \
    rdialog_threshold.cpp \
    rcontroller.cpp \
    rdialog_rename.cpp \
    rdialog_morphology.cpp \
    rdialog_edgedetection.cpp \
    rdialog_threshold_color.cpp

HEADERS += \
        mainwindow.h \
    rmodel.h \
    rutils.h \
    rheaders.h \
    rview.h \
    ralgorithm.h \
    rdialog_threshold.h \
    rcontroller.h \
    rdialog_rename.h \
    rdialog_morphology.h \
    rdialog_edgedetection.h \
    rdialog_threshold_color.h


FORMS += \
        mainwindow.ui \
    rdialog_threshold.ui \
    rdialog_rename.ui \
    rdialog_morphology.ui \
    rdialog_edgedetection.ui \
    rdialog_threshold_color.ui

# OpenCV lib
LIBS += -L/usr/local/Cellar/opencv/4.0.1/lib \
 -lopencv_core \
 -lopencv_highgui \
 -lopencv_imgproc \
 -lopencv_imgcodecs \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    README.md
