#ifndef GUI_SMARK_MAINWINDOW_H
#define GUI_SMARK_MAINWINDOW_H

#include <QMainWindow>
#include <QWebView>
#include "GUI/SmarkOption.h"
#include "GUI/PandocExecutor.h"

namespace Ui {
class SmarkMainWindow;
}

class SmarkMainWindow
        : public QMainWindow
{
    Q_OBJECT

public:
    explicit SmarkMainWindow(QWidget *parent = 0);
    ~SmarkMainWindow();

/* *****************************************************************************
 *
 *                          Commond Initial
 *
 * ****************************************************************************/

    bool openMarkdownFile(const char* file_name);

/* *****************************************************************************
 *
 *                              Event Process
 *
 * ****************************************************************************/

protected:
    virtual void resizeEvent(QResizeEvent *);
    virtual void keyPressEvent(QKeyEvent *);
    virtual void dragEnterEvent(QDragEnterEvent *);
    virtual void dropEvent(QDropEvent *);
    virtual void closeEvent(QCloseEvent *);

/* *****************************************************************************
 *
 *                              GUI slots
 *
 * ****************************************************************************/

private slots:

    // File Menu
    void on_ActionFileNew_triggered();
    void on_ActionFileOpen_triggered();
    void on_ActionFileSave_triggered();
    void on_ActionFileSaveAs_triggered();
    void on_ActionFileImport_triggered();
    void on_ActionFileExport_triggered();
    void on_ActionFilePrint_triggered();
    void on_ActionFileOption_triggered();
    void on_ActionFileQuit_triggered();

    // View Menu
    void on_ActionViewFullScreen_triggered();
    void on_ActionViewEditMode_triggered();
    void on_ActionViewReadMode_triggered();
    void on_ActionViewVerticalLayout_triggered();
    void on_ActionViewHorizontal_Layout_triggered();
    void on_ActionViewShowMenuBar_triggered();
    void on_ActionViewShowStatusBar_triggered();
    void on_ActionViewShowToolBar_triggered();

    // Edit Menu
    void on_ActionEditInsertImage_triggered();
    void on_ActionEditInsertLink_triggered();
    void on_ActionEditCSS_triggered();
    void on_ActionEditUndo_triggered();
    void on_ActionEditRedo_triggered();
    void on_ActionEditCut_triggered();
    void on_ActionEditCopy_triggered();
    void on_ActionEditPaste_triggered();
    void on_ActionEditSearch_triggered();
    void on_ActionEditFlush_triggered();

    // Format Menu
    void on_ActionFormatBlod_triggered();
    void on_ActionFormatItalic_triggered();
    void on_ActionFormatUnderLine_triggered();
    void on_ActionFormatDeleted_triggered();
    void on_ActionFormatQuote_triggered();
    void on_ActionFormatCode_triggered();
    void on_ActionFormatSub_triggered();
    void on_ActionFormatSup_triggered();
    void on_ActionFormatBigger_triggered();
    void on_ActionFormatSmaller_triggered();
    void on_ActionFormatOrderedList_triggered();
    void on_ActionFormatUnorderedList_triggered();

    // Help Menu
    void on_ActionHelpHome_triggered();
    void on_ActionHelpAbout_triggered();
    void on_ActionHelpAboutQt_triggered();

    // Search Widget
    void on_PrevButton_clicked();
    void on_NextButton_clicked();
    void on_ReplaceButton_clicked();
    void on_ReplaceAllButton_clicked();
    void on_SearchHideButton_clicked();

    // CSS Edit Widget
    void on_CSSLoadButton_clicked();
    void on_CSSApplyButton_clicked();
    void on_CSSDefaultButton_clicked();

    // Overlay
    void when_text_edited();

/* *****************************************************************************
 *
 *                              GUI Initial
 *
 * ****************************************************************************/

private:
    void _do_initialGUI();
    void _do_ApplyGUIOption(const SmarkOption& option);
    void _do_SignalSlotConnect();
    void _do_LockGUI();
    void _do_UnlockGUI();

/* *****************************************************************************
 *
 *                              Document IO
 *
 * ****************************************************************************/

private:
    bool _do_NewDocument();
    bool _do_OpenDocument();
    bool _do_SaveDocument();
    bool _do_SaveDocumentAs();
    bool _do_CloseDocument();
    void _do_SetCurrentPath(const QString& path);
    void _do_UpdateHtmlView();

/* *****************************************************************************
 *
 *                             Call pandoc
 *
 * ****************************************************************************/

private:
    void _do_RunPandoc();
private slots:
    void when_PandocProcess_finished();

/* *****************************************************************************
 *
 *                            Data Member
 *
 * ****************************************************************************/

private:
    Ui::SmarkMainWindow* ui;
    bool _is_modified;
    QString _current_path;
    QString _current_md_cache;
    QString _current_html_cache;
    PandocExecutor _pandoc_executor;
};

#endif // GUI_SMARK_MAINWINDOW_H
