######################################################################
# Automatically generated by qmake (3.1) Sat May 7 11:53:10 2022
######################################################################

TEMPLATE = app
TARGET = build/main
INCLUDEPATH += . \
               include

# The following define makes your compiler warn you if you use any
# feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Input
HEADERS += include/imageviewer.hpp \
           include/imageeditor.hpp \
           include/rescaledialog.h \
           include/brightnessdialog.h \
           include/contrastdialog.h
SOURCES += src/imageviewer.cpp \
           src/imageeditor.cpp \
           src/rescaledialog.cpp \
           src/brightnessdialog.cpp \
           src/contrastdialog.cpp \
           src/main.cpp

FORMS += assets/designs/rescaledialog.ui \
         assets/designs/brightnessdialog.ui \
         assets/designs/contrastdialog.ui

QT += widgets core gui
requires(qtConfig(filedialog))
qtHaveModule(printsupport): QT += printsupport
