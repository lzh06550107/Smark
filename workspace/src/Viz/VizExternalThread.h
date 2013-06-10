#ifdef QT_GUI_LIB
#ifndef LIB_VIZ_EXTERNAL_THREAD_H
#define LIB_VIZ_EXTERNAL_THREAD_H

#include <QThread>
#include <QProcess>

class VizExternalThread
        : public QThread
{
    Q_OBJECT

public:

    VizExternalThread(const QString& program,
                      const QStringList& args,
                      QObject * parent = NULL)
        : QThread(parent), _program(program), _args(args)
    { /*nothing need to do*/ }

    virtual ~VizExternalThread() { /*nothing need to do*/ }

protected:

    void run() {
        if(_args.isEmpty())
            QProcess::execute(_program);
        else
            QProcess::execute(_program, _args);
    }

private:
    QString _program;
    QStringList _args;
};

#endif // LIB_VIZ_EXTERNAL_THREAD_H
#endif // QT_GUI_LIB

