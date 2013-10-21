#include <QScrollBar>
#include "GuiMarkEdit.h"

const QChar LineSeparator(L'\u2029');

GuiMarkEdit::GuiMarkEdit(QWidget* parent)
    : QPlainTextEdit(parent)
{
    connect(verticalScrollBar(), SIGNAL(valueChanged(int)),
            this, SLOT(when_VerticalScrollBar_valueChanged(int)) );
    //    QPalette palette;
    //    palette.setColor(QPalette::Base, Qt::black);
    //    palette.setColor(QPalette::Text, Qt::white);
    //    setPalette(palette);

    //    QFont font;
    //    font.setFamily("Consolas");
    //    font.setPointSize(12);
    //    setFont(font);
    /* nothing need to do */
}

/* *****************************************************************************
 *
 *                          synchronized scrolling
 *
 * ****************************************************************************/

float GuiMarkEdit::scrollRatio() {
    QScrollBar* scroll = verticalScrollBar();
    return float(scroll->value()-scroll->minimum())
            / float(scroll->maximum()-scroll->minimum());
}

void GuiMarkEdit::when_VerticalScrollBar_valueChanged(int val) {
    QScrollBar* scroll = verticalScrollBar();
    float ratio = float(val-scroll->minimum())
            / float(scroll->maximum()-scroll->minimum());
    emit verticalScroll(ratio);
}

/* *****************************************************************************
 *
 *                              find and replace
 *
 * ****************************************************************************/

void GuiMarkEdit::findPrevious(const QString& text, bool cased, bool whole) {
    QTextDocument::FindFlags find_flags;
    find_flags |= QTextDocument::FindBackward;
    if(cased)
        find_flags |= QTextDocument::FindCaseSensitively;
    if(whole)
        find_flags |= QTextDocument::FindWholeWords;
    this->find(text, find_flags);
}

void GuiMarkEdit::findNext(const QString& text, bool cased, bool whole) {
    QTextDocument::FindFlags find_flags;
    if(cased)
        find_flags |= QTextDocument::FindCaseSensitively;
    if(whole)
        find_flags |= QTextDocument::FindWholeWords;
    this->find(text, find_flags);
}

void GuiMarkEdit::replaceCurrent(const QString& new_text) {
    QTextCursor cursor = this->textCursor();
    cursor.insertText(new_text);
}

void GuiMarkEdit::replaceAll(const QString& old_text, const QString& new_text)
{
    // \todo
}

/* *****************************************************************************
 *
 *                              set selected format
 *
 * ****************************************************************************/

void GuiMarkEdit::_aux_set_words_format(const QString& before,
                                        const QString& after ) {
    QTextCursor cursor = this->textCursor();
    QString selected =  cursor.selectedText();
    if(selected.startsWith(before) && selected.endsWith(after)) {
        selected.remove(before);
        selected.remove(after);
    } else {
        selected.prepend(before);
        selected.append(after);
    }
    cursor.insertText(selected);
}

void GuiMarkEdit::setSelectedBlod(void) {
    _aux_set_words_format("<b>", "</b>");
}

void GuiMarkEdit::setSelectedItalic(void) {
    _aux_set_words_format("<i>", "</i>");
}

void GuiMarkEdit::setSelectedUnderLine(void) {
    _aux_set_words_format("<u>", "</u>");
}

void GuiMarkEdit::setSelectedDeleted(void) {
    _aux_set_words_format("<del>", "</del>");
}

void GuiMarkEdit::setSelectedQuote(void) {
    QTextCursor cursor = this->textCursor();
    if(cursor.hasSelection()) {
        QString selected = cursor.selectedText();
        QStringList lines = selected.split(LineSeparator);
        if(lines.size() == 1) {
            _aux_set_words_format("<q>", "</q>");
        } else {
            for(QStringList::iterator it=lines.begin(); it!=lines.end(); ++it)
                it->prepend("> ");
            cursor.insertText(lines.join(LineSeparator));
        }
    } // if(cursor.hasSelection())
}

void GuiMarkEdit::setSelectedCode(void) {
    _aux_set_words_format("`", "`");
}

void GuiMarkEdit::setSelectedSub(void) {
    _aux_set_words_format("<sub>", "</sub>");
}

void GuiMarkEdit::setSelectedSup(void) {
    _aux_set_words_format("<sup>", "</sup>");
}

void GuiMarkEdit::setSelectedBigger(void) {
    _aux_set_words_format("<big>", "</big>");
}

void GuiMarkEdit::setSelectedSmaller(void) {
    _aux_set_words_format("<small>", "</small>");
}

void GuiMarkEdit::setSelectedOrderedList(void) {
    QTextCursor cursor = this->textCursor();
    QString selected =  cursor.selectedText();
    QStringList lines = selected.split(LineSeparator);
    int list_num = 1;
    for(QStringList::iterator it=lines.begin(); it!=lines.end(); ++it) {
        if(! it->isEmpty()) {
            it->prepend(" " + QString::number(list_num) + ". ");
            ++list_num;
        }
    }
    cursor.insertText(lines.join(LineSeparator));
}

void GuiMarkEdit::setSelectedUnorderedList(void) {
    QTextCursor cursor = this->textCursor();
    QString selected =  cursor.selectedText();
    QStringList lines = selected.split(LineSeparator);
    for(QStringList::iterator it=lines.begin(); it!=lines.end(); ++it)
        if(! it->isEmpty()) it->prepend(" + ");
    cursor.insertText(lines.join(LineSeparator));
}

/* *****************************************************************************
 *
 *                              event porcess
 *
 * ****************************************************************************/

void GuiMarkEdit::keyPressEvent(QKeyEvent* event)
{
    // switch tab char to spaces
    if(event->key() == Qt::Key_Tab) {
        QTextCursor cursor = this->textCursor();
        if(cursor.hasSelection()) {
            QString selected = cursor.selectedText();
            QStringList lines = selected.split(LineSeparator);
            QStringList::iterator it;
            if(event->modifiers() & Qt::ControlModifier) {
                // Ctrl + Tab, remove an indentation
                for(it=lines.begin(); it!=lines.end(); ++it)
                    if(it->startsWith("    ")) it->remove(0, 4);
            } else {
                // Only Tab, add an indentation
                for(it=lines.begin(); it!=lines.end(); ++it)
                    if(! it->isEmpty()) it->prepend("    ");
            }
            cursor.insertText(lines.join(LineSeparator));
        } else { // if(cursor.hasSelection())
            // Just insert a '\t', but we replace '\t' as "    "
            cursor.insertText("    ");
        } // if(cursor.hasSelection())
        return;
    }
    QPlainTextEdit::keyPressEvent(event);
}

