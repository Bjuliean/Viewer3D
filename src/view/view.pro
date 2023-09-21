QT       += core gui opengl openglwidgets printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../controller/controller.cc \
    ../model/data/data.cc \
    ../model/model.cc \
    ../model/parser/parser.cc \
    ../model/renderer/matrixevents.cc \
    ../model/renderer/renderer.cc \
    ../model/renderer/shaders/shader.cc \
    ../main.cc \
    mainwindow/view.cc

HEADERS += \
    ../controller/controller.h \
    ../model/data/data.h \
    ../model/data/objectdata.h \
    ../model/model.h \
    ../model/parser/parser.h \
    ../model/renderer/matrixevents.h \
    ../model/renderer/renderer.h \
    ../model/renderer/shaders/shader.h \
    ../model/renderer/utils.h \
    mainwindow/view.h

FORMS += \
    mainwindow/view.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ../model/renderer/shaders/shaders.qrc

DISTFILES += \
    ../model/renderer/shaders/fshader.fsh \
    ../model/renderer/shaders/simplefshader.fsh \
    ../model/renderer/shaders/simplevshader.vsh \
    ../model/renderer/shaders/vshader.vsh

include(mainwindow/libs/QtGifImage/src/gifimage/qtgifimage.pri)
