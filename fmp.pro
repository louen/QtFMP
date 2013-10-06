TARGET = fmp
TEMPLATE = app
CONFIG += qt \ 
    debug_and_release \
    warn_on

QT += widgets

ROOT = $$PWD
SRC = $$ROOT/src
TMP = $$ROOT/tmp
BIN = $$ROOT/bin

INCLUDEPATH += $$SRC

SOURCES += $$SRC/main.cpp\
           $$SRC/gui/fmpMainWindow.cpp\
            $$SRC/gui/fmpScreen.cpp\
            $$SRC/game/fmp.cpp\
            $$SRC/game/fmpPathFinder.cpp

HEADERS += $$SRC/gui/fmpMainWindow.h\
            $$SRC/gui/fmpScreen.h\
            $$SRC/game/fmp.h \
            $$SRC/game/fmpGame.h \
            $$SRC/game/fmpGameObject.h \
            $$SRC/game/fmpWeather.h  \
            $$SRC/game/fmpPathFinder.h

# config release
MOC_DIR = $$TMP/release/moc
OBJECTS_DIR = $$TMP/release/obj
DESTDIR = $$BIN/release

# config debug in separate directories
build_pass:CONFIG(debug,debug|release) {
    MOC_DIR = $$TMP/debug/moc
    OBJECTS_DIR = $$TMP/debug/obj
    DESTDIR = $$BIN/debug
}
