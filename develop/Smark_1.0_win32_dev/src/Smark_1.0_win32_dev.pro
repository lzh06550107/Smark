# Build Configure ##############################################################

TEMPLATE = app
TARGET   = smark-dev
QT       += webkit

# Input File ###################################################################

HEADERS += \
    SmarkApp.h \
    SmarkFileIO.h \
    SmarkParser.h \
    GuiHtmlView.h \
    GuiMarkEdit.h \
    GuiWindowSmark.h

FORMS += \
    GuiWindowSmark.ui

SOURCES += main.cpp \
    SmarkApp.cpp \
    SmarkFileIO.cpp \
    SmarkParser.cpp \
    GuiHtmlView.cpp \
    GuiMarkEdit.cpp \
    GuiWindowSmark.cpp

RESOURCES += rs/icon.qrc

RC_FILE += rs/LOGO.rc
