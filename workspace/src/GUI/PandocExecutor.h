#ifndef GUI_PANDOC_EXECUTOR_H
#define GUI_PANDOC_EXECUTOR_H

#include <QObject>
#include "Viz/VizExternalThread.h"

enum PandocInType {
    Pandoc_In_Auto          = 0,     // Auto-determine based on the file suffix
    Pandoc_In_RST           = 1,
    Pandoc_In_Wiki          = 2,
    Pandoc_In_Docbook       = 3,
    Pandoc_In_Texttile      = 4,
    Pandoc_In_Html          = 5,
    Pandoc_In_Latex         = 6,
    Pandoc_In_Json          = 7,
    Pandoc_In_markdown      = 8
};

enum PandocOutType {
    Pandoc_Out_Auto         = 0,    // Auto-determine based on the file suffix
    Pandoc_Out_RST          = 1,
    Pandoc_Out_Wiki         = 2,
    Pandoc_Out_Texttile     = 3,
    Pandoc_Out_RTF          = 4,
    Pandoc_Out_Org          = 5,
    Pandoc_Out_ASCIIDoc     = 6,
    Pandoc_Out_Json         = 7,
    Pandoc_Out_Docx         = 8,
    Pandoc_Out_ODT          = 9,
    Pandoc_Out_EPUB         = 10,
    Pandoc_Out_Html         = 11,
    Pandoc_Out_Docbook      = 12,
    Pandoc_Out_OpenDocument = 13,
    Pandoc_Out_Latex        = 14,
    Pandoc_Out_Beamer       = 15,
    Pandoc_Out_TextInfo     = 16,
    Pandoc_Out_ManPage      = 17,
    Pandoc_Out_Markdown     = 18,
    Pandoc_Out_Plain        = 19
};

class PandocExecutor
        : public QObject
{
    Q_OBJECT

public:
    explicit PandocExecutor(QObject *parent = 0);

    virtual ~PandocExecutor();

    void execuate(const QString& in_path, const QString& out_path);
//    void execuate(const QString& in_path,  PandocInType in_type,
//                  const QString& out_path, PandocOutType out_type,);

signals:
    void completed();

private slots:
    void when_pandoc_finished();

private:
    VizExternalThread* _pandoc_thread;
};

#endif // PANDOCEXECUTOR_H
