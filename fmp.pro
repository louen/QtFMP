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

SOURCES += $$SRC/main.cpp\
           $$SRC/GUI/fmpMainWindow.cpp

HEADERS += $$SRC/GUI/fmpMainWindow.h

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
