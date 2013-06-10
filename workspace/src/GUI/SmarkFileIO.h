#ifndef GUI_SMARK_FILE_IO_H
#define GUI_SMARK_FILE_IO_H

#include "GUI/SmarkOption.h"

bool IO_LoadOption(const QString& path, SmarkOption* option);
bool IO_SaveOption(const QString& path, const SmarkOption& option);

bool IO_LoadCSS(const QString& path, QString* CSS_text);
bool IO_SaveCSS(const QString& path, const QString& CSS_text);

bool IO_LoadHtml(const QString& path, QString* html_text,
                 QString* error=NULL);
bool IO_SaveHtml(const QString& path, const QString& html_text,
                 QString* error=NULL);

bool IO_LoadMarkdown(const QString& path, QString* md_text,
                     QString* error=NULL);
bool IO_SaveMarkdown(const QString& path, const QString& md_text,
                     QString* error=NULL);

bool IO_RemoveFile(const QString& path);

QString IO_MDCachePath(const QString& md_path);
QString IO_HtmlCachePath(const QString& md_path);

#endif // SMARKFILEIO_H
