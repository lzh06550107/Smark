#include <QMessageBox>
#include <QTextDocument>
#include <QtWebKit/QWebFrame>
#include "Viz/QStringFunc.h"
#include "GUI/SmarkFileIO.h"
#include "GUI/SmarkHtmlView.h"

SmarkHtmlView::SmarkHtmlView(QWidget *parent) :
    QWebView(parent)
{
    ::IO_LoadCSS(QSTR("://TEXT/preview.css"), &_CSS);
}

float SmarkHtmlView::scrollValue() {
    return page()->mainFrame()->scrollBarValue(Qt::Vertical);
}

void SmarkHtmlView::setScrollValue(int value) {
    page()->mainFrame()->setScrollBarValue(Qt::Vertical, value);
}

void SmarkHtmlView::loadHtmlFile(const QString& html_path)
{
    // load html_text
    QString error;
    if(! ::IO_LoadHtml(html_path, &_simple_html, &error) )
        QMessageBox::warning(this, QSTR("Error"), error);
    _styled_html = QSTR("<head><style type=\"text/css\">\n")
            + _CSS
            + QSTR("\n</style type=\"text/css\"></head></body>\n")
            + _simple_html
            + QSTR("\n</body>\n");
    setStyleSheet(_CSS);
    setHtml(_styled_html, QUrl::fromLocalFile(html_path));
    repaint(page()->mainFrame()->geometry()); // do not use update() !!!
}

void SmarkHtmlView::exportHtmlFile(const QString& html_path)
{
    QString error;
    if(! ::IO_SaveHtml(html_path, _styled_html, &error) ) {
        QMessageBox::warning(this, QSTR("Error"), error);
    }
}

void SmarkHtmlView::clearHtml()
{
    _styled_html.clear();
    _simple_html.clear();
    setHtml(VIZ_EMPTY_QSTR);
    update();
}

void SmarkHtmlView::printPage(QPrinter *printer) const
{
//    QTextDocument text_doc;
//    QString print_CSS; ::IO_LoadCSS(QSTR("://TEXT/print.css"), &print_CSS);
//    text_doc.setDefaultStyleSheet(print_CSS);
//    text_doc.setHtml(_simple_html);
//    text_doc.print(printer);

//    QString print_CSS, print_html;
//    ::IO_LoadCSS(QSTR("://TEXT/print.css"), &print_CSS);
//    print_html = QSTR("<head><style type=\"text/css\">\n")
//            + print_CSS
//            + QSTR("\n</style type=\"text/css\"></head></body>\n")
//            + _simple_html
//            + QSTR("\n</body>\n");

//    QWebView print_view(NULL);
//    print_view.setHtml(print_html);
//    print_view.print(printer);
}

void SmarkHtmlView::setScrollRatio(float ratio)
{
    int maxv = page()->mainFrame()->scrollBarMaximum(Qt::Vertical);
    int minv = page()->mainFrame()->scrollBarMinimum(Qt::Vertical);
    page()->mainFrame()->setScrollBarValue(Qt::Vertical,
                                           minv + ratio*(maxv-minv));
}
