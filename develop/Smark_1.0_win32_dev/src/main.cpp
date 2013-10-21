#include <QtGui>
#include <QApplication>
#include <QTextCodec>
#include "GuiWindowSmark.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
#ifdef WIN32
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("GBK"));
#endif
    gInitApp(argc, argv);

    GuiWindowSmark wnd(NULL);
    if(argc > 1) {
        wnd.openMarkdownFile(gApp().StartPath);
        wnd.show();
    } else {
        wnd.show();
    }
    return app.exec();
}
