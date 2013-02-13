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
           $$SRC/GUI/fmpMainWindow.cpp\
            $$SRC/GUI/fmpScreen.cpp

HEADERS += $$SRC/GUI/fmpMainWindow.h\
            $$SRC/GUI/fmpScreen.h

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
