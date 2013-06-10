#include <ctime>
#include <QFile>
#include <QTextStream>
#include "Viz/QStringFunc.h"
#include "GUI/SmarkOption.h"
#include "GUI/SmarkFileIO.h"


bool IO_LoadOption(const QString& path, SmarkOption* option)
{
    return true;
}

bool IO_SaveOption(const QString& path, const SmarkOption& option)
{
    QFile file;
    file.setFileName(path);
    if(! file.open(QIODevice::WriteOnly)) {
        return false;
    }

    QTextStream fstream(&file);
    fstream << "SMARK_OPTION_FILE" << endl;
    fstream << "window-size  = " << option.WndWidth << ", " << option.WndHeight << endl;
    fstream << "fullscreen   = " << QSTR(option.FullScreen) << endl;
    fstream << "show-menu    = " << QSTR(option.ShowMenuBar) << endl;
    fstream << "show-toolbar = " << QSTR(option.ShowToolBar) << endl;
    fstream << "show-status  = " << QSTR(option.ShowStatusBar) << endl;
    fstream << "bkg-color    = " << option.BkgColor.name() << endl;
    fstream << "text-color   = " << option.TextColor.name() << endl;
    fstream << "text-font    = " << option.TextFontFamily
            << " , " << option.TextFontSize << endl;
    file.close();
    return true;
}

bool IO_LoadCSS(const QString& path, QString* CSS_text)
{
    QFile file(path);
    if(! file.open(QIODevice::ReadOnly) )
        return false;
    *CSS_text = QObject::trUtf8(file.readAll().data());
    file.close();
    return true;
}

bool IO_SaveCSS(const QString& path, const QString& CSS_text)
{
    QFile file(path);
    if(! file.open(QIODevice::WriteOnly))
        return false;
    file.write(CSS_text.toUtf8());
    file.close();
    return true;
}

bool IO_LoadHtml(const QString& path, QString* html_text,
                 QString* error)
{
    QFile file(path);
    if(! file.open(QIODevice::ReadOnly) ) {
        if(error != NULL) {
            *error = QSTR("Can not open Html file :") + path
                   + QSTR(" for reading \n") + file.errorString();
        }
        return false;
    }
    *html_text = QObject::trUtf8(file.readAll().data());
    file.close();
    return true;
}

bool IO_SaveHtml(const QString& path, const QString& html_text,
                 QString* error)
{
    QFile file(path);
    if(! file.open(QIODevice::WriteOnly)) {
        if(error != NULL) {
            *error = QSTR("Can not open Html file :") + path
                    + QSTR(" for writing \n") + file.errorString();
        }
        return false;
    }
    file.write(html_text.toUtf8());
    file.close();
    return true;
}


bool IO_LoadMarkdown(const QString& path, QString* md_text,
                     QString* error)
{
    QFile file(path);
    if(! file.open(QIODevice::ReadOnly) ) {
        if(error != NULL) {
            *error = QSTR("Can not open markdown file :") + path
                    + QSTR(" for reading \n") + file.errorString();
        }
        return false;
    }
    *md_text = QObject::trUtf8(file.readAll().data());
    ::VizReplaceAll(md_text, QSTR("\t"), QSTR("    "));
    file.close();
    return true;
}

bool IO_SaveMarkdown(const QString& path, const QString& md_text,
                     QString* error)
{
    QFile file(path);
    if(! file.open(QIODevice::WriteOnly)) {
        if(error != NULL) {
            *error = QSTR("Can not open markdown file :") + path
                    + QSTR(" for writing \n") + file.errorString();
        }
        return false;
    }
    file.write(md_text.toUtf8());
    file.close();
    return true;
}

bool IO_RemoveFile(const QString &path)
{
    QFile file(path);
    return file.remove();
}

#include <QDebug>
QString IO_MDCachePath(const QString& md_path)
{
    Q_ASSERT(!md_path.isEmpty());
    QString path = ::VizFileDir(md_path) + QSTR("/") + QSTR(qHash(md_path));
    qDebug() << path;
    return path;
}

QString IO_HtmlCachePath(const QString& md_path)
{
    Q_ASSERT(!md_path.isEmpty());
    QString path = ::VizFileDir(md_path) + QSTR("/") + QSTR(qHash(md_path));
    qDebug() << path;
    return path;
}
