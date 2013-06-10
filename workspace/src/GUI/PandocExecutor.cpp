#include <QDebug>
#include "GUI/PandocExecutor.h"

PandocExecutor::PandocExecutor(QObject *parent)
    : QObject(parent),
      _pandoc_thread(NULL)
{ }

PandocExecutor::~PandocExecutor()
{
    if(_pandoc_thread != NULL)
        delete _pandoc_thread;
}

void PandocExecutor::execuate(const QString& in_path, const QString& out_path)
{
    if(_pandoc_thread == NULL) {
        QString pandoc("pandoc");
        QStringList args;
        args << "-f" << "markdown" << "-t" << "html"
             << "-i" << in_path
             << "-o" << out_path;
        _pandoc_thread = new VizExternalThread(pandoc, args);
        connect(_pandoc_thread, SIGNAL(finished()),
                this, SLOT(when_pandoc_finished()) );
        _pandoc_thread->start();
    }
}

void PandocExecutor::when_pandoc_finished()
{
    emit completed();
    disconnect(_pandoc_thread, SIGNAL(finished()),
               this, SLOT(when_pandoc_finished()) );
    delete _pandoc_thread;
    _pandoc_thread = NULL;
}
