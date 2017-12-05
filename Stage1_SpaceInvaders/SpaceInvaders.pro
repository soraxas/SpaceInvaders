#-------------------------------------------------
#
# Project created by QtCreator 2017-03-20T14:44:30
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SpaceInvaders
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
    spaceship.cpp \
    graphicsrenderer.cpp \
    director.cpp \
    bullet.cpp \
    logicEngine.cpp \
    bulletbuilderdefault.cpp \
    spaceshipbuilderdefault.cpp \
    config.cpp \
    energyorb.cpp \
    helpers.cpp

HEADERS  += \
    spaceship.h \
    graphicsrenderer.h \
    director.h \
    spaceshipbuilder.h \
    logicEngine.h \
    bullet.h \
    bulletbuilder.h \
    bulletbuilderdefault.h \
    spaceshipbuilderdefault.h \
    config.h \
    energyorb.h \
    helpers.h

RESOURCES += \
    resources.qrc

# PLEASE manual copy the content of copy_to_install_dir to the root of the install / build directory

#FORMS +=
#
#copy the contents of the 'copy_to_install_dir' subdirectory of the project
# to the root of the install / build directory
#copydata.commands = $(COPY_DIR) $$PWD/copy_to_install_dir/* $$OUT_PWD
#first.depends = $(first) copydata
#export(first.depends)
#export(copydata.commands)
#QMAKE_EXTRA_TARGETS += first copydata
