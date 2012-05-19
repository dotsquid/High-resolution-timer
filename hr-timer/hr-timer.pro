TEMPLATE = app
TARGET = usage_test
CONFIG -= qt

CONFIG += debug_and_release

CONFIG(debug, debug|release)
{
    DESTDIR = ../bin/debug
}
CONFIG(release, debug|release)
{
    DESTDIR = ../bin/release
}

HEADERS += ../src/timer.h

SOURCES += ../usage/usage_test.cpp \
           ../src/timer.cpp
