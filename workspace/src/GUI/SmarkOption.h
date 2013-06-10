#ifndef GUI_SMARK_OPTION_H
#define GUI_SMARK_OPTION_H

#include <QString>
#include <QColor>

enum SmarkMode {
    SmarkEditMode = 0,
    SmarkReadMode = 1,
    SmarkZenMode  = 2
};

struct SmarkOption
{
public:
    int         WndWidth, WndHeight;
    bool        FullScreen;
    bool        ShowMenuBar;
    bool        ShowToolBar;
    bool        ShowStatusBar;
    QColor      BkgColor;
    QColor      TextColor;
    QString     TextFontFamily;
    int         TextFontSize;

public:
    SmarkOption() { init(); }

    void init() {
        WndHeight       = 800;
        WndWidth        = 1000;
        FullScreen      = false;
        ShowMenuBar     = true;
        ShowToolBar     = true;
        ShowStatusBar   = false;
        BkgColor        = Qt::black;
        TextColor       = Qt::white;
    #ifdef WIN32
        TextFontFamily  = QString("Consolas");
    #else
        TextFontFamily  = QString("Monospace");
    #endif
        TextFontSize = 12;
    }
};

#endif // GUI_SMARK_OPTION_H
