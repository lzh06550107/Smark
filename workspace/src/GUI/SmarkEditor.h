#ifndef GUI_SMARK_EDITOR_H
#define GUI_SMARK_EDITOR_H

#include <QPlainTextEdit>

class SmarkEditor : public QPlainTextEdit
{
    Q_OBJECT
public:
    explicit SmarkEditor(QWidget *parent = 0);

    float scrollRatio();

    // find and replace
    void findPrevious(const QString& text, bool cased, bool whole);
    void findNext(const QString& text, bool cased, bool whole);
    void replaceCurrent(const QString& new_text);
    void replaceAll(const QString& old_text, const QString& new_text);

    // insert
    void insertImage();
    void insertLink();

    // format setting
    void setSelectedBlod();
    void setSelectedItalic();
    void setSelectedUnderLine();
    void setSelectedDeleted();
    void setSelectedQuote();
    void setSelectedCode();
    void setSelectedSub();
    void setSelectedSup();
    void setSelectedBigger();
    void setSelectedSmaller();
    void setSelectedOrderedList();
    void setSelectedUnorderedList();

protected:
    virtual void keyPressEvent(QKeyEvent *e);

private slots:
    void when_VerticalScrollBar_valueChanged(int val);

signals:
    void editorScroll(float ratio);

private:
    void _do_SetWordsFormat(const QString& before, const QString& after);
};

#endif // GUI_SMARK_EDITOR_H
