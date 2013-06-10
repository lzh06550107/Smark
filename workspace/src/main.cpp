#include <QApplication>
#include <QTextCodec>
#include "GUI/SmarkMainWindow.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
#ifdef WINNT
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("GBK"));
#endif
    SmarkMainWindow main_wnd;
    main_wnd.setAcceptDrops(true);
    if(argc >= 2) {
        main_wnd.openMarkdownFile(argv[1]);
    }
    main_wnd.show();
    return app.exec();
}
