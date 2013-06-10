#include <QScrollBar>
#include "Viz/QStringFunc.h"
#include "GUI/SmarkEditor.h"

const QChar LineSeparator(L'\u2029');

SmarkEditor::SmarkEditor(QWidget *parent)
    : QPlainTextEdit(parent)
{
    connect(verticalScrollBar(), SIGNAL(valueChanged(int)),
            this, SLOT(when_VerticalScrollBar_valueChanged(int)) );
}

float SmarkEditor::scrollRatio()
{
    QScrollBar* scroll = verticalScrollBar();
    return float(scroll->value()-scroll->minimum())
            / float(scroll->maximum()-scroll->minimum());
}

void SmarkEditor::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Tab)
    {
        QTextCursor cursor = this->textCursor();
        if(cursor.hasSelection())
        {
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

    } else {
        QPlainTextEdit::keyPressEvent(event);
    }
}

void SmarkEditor::when_VerticalScrollBar_valueChanged(int val)
{
    QScrollBar* scroll = verticalScrollBar();
    float ratio = float(val-scroll->minimum())
                   / float(scroll->maximum()-scroll->minimum());
    emit editorScroll(ratio);
}

/* *****************************************************************************
 *
 *                          find and replace
 *
 * ****************************************************************************/

void SmarkEditor::findPrevious(const QString& text, bool cased, bool whole)
{
    QTextDocument::FindFlags find_flags;
    find_flags |= QTextDocument::FindBackward;
    if(cased)
        find_flags |= QTextDocument::FindCaseSensitively;
    if(whole)
        find_flags |= QTextDocument::FindWholeWords;
    this->find(text, find_flags);
}

void SmarkEditor::findNext(const QString& text, bool cased, bool whole)
{
    QTextDocument::FindFlags find_flags;
    if(cased)
        find_flags |= QTextDocument::FindCaseSensitively;
    if(whole)
        find_flags |= QTextDocument::FindWholeWords;
    this->find(text, find_flags);
}

void SmarkEditor::replaceCurrent(const QString& new_text)
{
    QTextCursor cursor = this->textCursor();
    // cursor.removeSelectedText();
    cursor.insertText(new_text);
}

void SmarkEditor::replaceAll(const QString& old_text, const QString& new_text)
{
    QString all_text = this->toPlainText();
    ::VizReplaceAll(&all_text, old_text, new_text);
    this->setPlainText(all_text);
}

/* *****************************************************************************
 *
 *                              insert
 *
 * ****************************************************************************/

void SmarkEditor::insertImage()
{
    QTextCursor cursor = this->textCursor();
    QString text = QSTR("<p align=\"center\">") + LineSeparator
                 + QSTR("    <img src=\"IMG_PATH\" width=\"80%\">") + LineSeparator
                 + QSTR("</p>");
    cursor.insertText(text);
}

void SmarkEditor::insertLink()
{
    QTextCursor cursor = this->textCursor();
    if(cursor.hasSelection())
    {
        QString selected = cursor.selectedText();
        selected = QSTR("[") + selected + QSTR("](LINK)");
        cursor.insertText(selected);
    } else {
        cursor.insertText(QSTR("[TEXT](LINK)"));
    }
}

/* *****************************************************************************
 *
 *                              format setting
 *
 * ****************************************************************************/

void SmarkEditor::setSelectedBlod() {
    _do_SetWordsFormat("<b>", "</b>");
}
void SmarkEditor::setSelectedItalic() {
    _do_SetWordsFormat("<i>", "</i>");
}
void SmarkEditor::setSelectedUnderLine() {
    _do_SetWordsFormat("<u>", "</u>");
}
void SmarkEditor::setSelectedDeleted() {
    _do_SetWordsFormat("<del>", "</del>");
}
void SmarkEditor::setSelectedQuote() {
    QTextCursor cursor = this->textCursor();
    if(cursor.hasSelection())
    {
        QString selected = cursor.selectedText();
        QStringList lines = selected.split(LineSeparator);
        if(lines.size() == 1) {
            _do_SetWordsFormat("<q>", "</q>");
        } else {
            for(QStringList::iterator it=lines.begin(); it!=lines.end(); ++it) {
                it->prepend("> ");
            }
            cursor.insertText(lines.join(LineSeparator));
        }
    } // if(cursor.hasSelection())
}
void SmarkEditor::setSelectedCode() {
    _do_SetWordsFormat("`", "`");
}
void SmarkEditor::setSelectedSub() {
    _do_SetWordsFormat("<sub>", "</sub>");
}
void SmarkEditor::setSelectedSup() {
    _do_SetWordsFormat("<sup>", "</sup>");
}
void SmarkEditor::setSelectedBigger() {
    _do_SetWordsFormat("<big>", "</big>");
}
void SmarkEditor::setSelectedSmaller() {
    _do_SetWordsFormat("<small>", "</small>");
}

void SmarkEditor::setSelectedOrderedList()
{
    QTextCursor cursor = this->textCursor();

    QString selected =  cursor.selectedText();
    QStringList lines = selected.split(LineSeparator);
    int list_num = 1;
    for(QStringList::iterator it=lines.begin(); it!=lines.end(); ++it) {
        if(! it->isEmpty()) {
            it->prepend(" " + QSTR(list_num) + ". ");
            ++list_num;
        }
    }
    cursor.insertText(lines.join(LineSeparator));
}

void SmarkEditor::setSelectedUnorderedList()
{
    QTextCursor cursor = this->textCursor();
    QString selected =  cursor.selectedText();
    QStringList lines = selected.split(LineSeparator);
    for(QStringList::iterator it=lines.begin(); it!=lines.end(); ++it) {
        if(! it->isEmpty()) it->prepend(" + ");
    }
    cursor.insertText(lines.join(LineSeparator));
}

void SmarkEditor::_do_SetWordsFormat(const QString& before,
                                             const QString& after)
{
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
