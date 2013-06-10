#ifndef GUI_SMARK_Html_VIEW_H
#define GUI_SMARK_Html_VIEW_H

#include <QWebView>

class SmarkHtmlView : public QWebView
{
    Q_OBJECT
public:
    explicit SmarkHtmlView(QWidget *parent = 0);

    void setCSS(const QString& css_text)    { _CSS = css_text; }
    const QString& CSS() const              { return _CSS; }

    float scrollValue();
    void setScrollValue(int value);

    void loadHtmlFile(const QString& html_path);
    void exportHtmlFile(const QString& html_path);
    void clearHtml();

    void printPage(QPrinter *printer) const;

public slots:
    void setScrollRatio(float ratio);

private:
    QString _CSS;
    QString _styled_html;
    QString _simple_html;
};

#endif // GUI_SMARK_Html_VIEW_H
