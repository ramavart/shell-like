TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        src/CommandDirector.cpp \
        src/CommandParser.cpp \
        src/ListCommand.cpp \
        src/main.cpp

HEADERS += \
    include/CommandDirector.h \
    include/CommandParser.h \
    include/DataTypes.h \
    include/ICommand.h \
    include/ICommandDirector.h \
    include/ICommandParser.h \
    include/ListCommand.h \
    include/templates.h
