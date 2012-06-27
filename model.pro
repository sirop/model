TEMPLATE = app
TARGET = model
QT += xml
DEPENDPATH += .
INCLUDEPATH += . /home/boris/marble_old/HEADER /home/boris/marble_old/src/lib /home/boris/marble_old/src/lib/geodata/parser /home/boris/marble_old/src/lib/geodata/data
LIBS+= /home/boris/marble-build/src/lib/libmarblewidget.so
# Input
HEADERS += ImportKml.h MyMarbleWidget.h
SOURCES += ImportKml.cpp MyMarbleWidget.cpp main.cpp
