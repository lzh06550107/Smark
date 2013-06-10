#include <QDebug>
#include <QtGui>
#include "Viz/QStringFunc.h"
#include "GUI/SmarkFileIO.h"
#include "GUI/SmarkOptionDialog.h"
#include "GUI/SmarkMainWindow.h"
#include "ui_SmarkMainWindow.h"

SmarkMainWindow::SmarkMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SmarkMainWindow),
    _is_modified(false)
{
    ui->setupUi(this);
    _do_initialGUI();
    _do_SignalSlotConnect();
    _do_ApplyGUIOption(SmarkOption());
    _do_LockGUI();
}

SmarkMainWindow::~SmarkMainWindow() {
    delete ui;
}

/* *****************************************************************************
 *
 *                          Commond Initial
 *
 * ****************************************************************************/

bool SmarkMainWindow::openMarkdownFile(const char* file_name)
{
    QString path= QString::fromLocal8Bit(file_name);
    QString err_info, md_text;
    if(! IO_LoadMarkdown(path, &md_text, &err_info)) {
        QMessageBox::warning(this, QSTR("Error"), err_info);
        return false;
    }
    ui->Editor->setPlainText(md_text);
    _do_SetCurrentPath(path);
    _is_modified = false;
    _do_RunPandoc();
    _do_UnlockGUI();
    return true;
}

/* *****************************************************************************
 *
 *                              Event Process
 *
 * ****************************************************************************/

void SmarkMainWindow::resizeEvent(QResizeEvent* event)
{
    QMainWindow::resizeEvent(event);
    if((!ui->HtmlView->isHidden()) && (!ui->Editor->isHidden())) {
        int size;
        if(ui->MainSplitter->orientation() == Qt::Horizontal)
            size = ui->CentralWidget->width()/2;
        else
            size = ui->CentralWidget->height()/2;
        QList<int> list; list.append(size); list.append(size);
        ui->MainSplitter->setSizes(list);
    }
}

void SmarkMainWindow::keyPressEvent(QKeyEvent* event)
{
    switch(event->key())
    {
    case Qt::Key_F12:
        on_ActionViewShowMenuBar_triggered();
        break;
    case Qt::Key_Escape:
        ui->SearchWidget->hide();
        ui->CSSWidget->hide();
        if(! ui->EditorWidget->isHidden()) {
            ui->Editor->setFocus();
        }
        break;
    default:
        QMainWindow::keyPressEvent(event);
        break;
    }
}

void SmarkMainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    event->acceptProposedAction();
    QMainWindow::dragEnterEvent(event);
    if(event->mimeData()->hasUrls()) {
        event->acceptProposedAction();
        event->accept();
    } else if(event->mimeData()->hasFormat("text/uri-list")) {
        event->acceptProposedAction();
        event->accept();
    }
}

void SmarkMainWindow::dropEvent(QDropEvent *event)
{
    QMainWindow::dropEvent(event);
    QList<QUrl> urls = event->mimeData()->urls();
    if(! urls.empty()) {
        QString path = urls.first().toLocalFile();
        if(! path.isEmpty()) {
            openMarkdownFile(path.toLocal8Bit().data());
        }
    }
}

void SmarkMainWindow::closeEvent(QCloseEvent* event)
{
    if(_do_CloseDocument()) {
        event->accept();
    } else {
        event->ignore();
    }
}

/* *****************************************************************************
 *
 *                              File Menu
 *
 * ****************************************************************************/

void SmarkMainWindow::on_ActionFileNew_triggered()
{
    if(_do_NewDocument()) {
        _do_UnlockGUI();
    } else {
        if(_current_path.isEmpty()) {
            _do_LockGUI();
            ui->HtmlView->clearHtml();
        }
    }
}

void SmarkMainWindow::on_ActionFileOpen_triggered()
{
    if(_do_OpenDocument()) {
        _do_UnlockGUI();
        _do_RunPandoc();
    } else {
        if(_current_path.isEmpty()) {
            _do_LockGUI();
            ui->HtmlView->clearHtml();
        }
    }
}

void SmarkMainWindow::on_ActionFileSave_triggered()
{
    _do_SaveDocument();
    if(ui->HtmlView->isVisible()) {
        _do_RunPandoc();
    }
}

void SmarkMainWindow::on_ActionFileSaveAs_triggered()
{
    _do_SaveDocumentAs();
}

void SmarkMainWindow::on_ActionFileImport_triggered()
{

}

void SmarkMainWindow::on_ActionFileExport_triggered()
{
    QString path = QFileDialog::getSaveFileName(this, QSTR("Export Html File"),
                                                ::VizLongBaseName(_current_path),
                                                QSTR("Html File (*.html)"));
    if(! path.isEmpty()) {
        ui->HtmlView->exportHtmlFile(path);
    }
}

void SmarkMainWindow::on_ActionFilePrint_triggered()
{
    QPrinter printer;
    QPrintDialog dlg(&printer, this);
    if(dlg.exec()==QDialog::Accepted) {
        ui->HtmlView->printPage(&printer);
    }
}

void SmarkMainWindow::on_ActionFileOption_triggered()
{

}

void SmarkMainWindow::on_ActionFileQuit_triggered()
{
    if(_do_CloseDocument()) {
        qApp->quit();
    }
}

/* *****************************************************************************
 *
 *                              View Menu
 *
 * ****************************************************************************/


void SmarkMainWindow::on_ActionViewFullScreen_triggered()
{
    if(this->windowState() == Qt::WindowFullScreen)
        this->showNormal();
    else
        this->showFullScreen();
}

void SmarkMainWindow::on_ActionViewEditMode_triggered()
{
    ui->EditorWidget->show();
    ui->HtmlView->hide();
    //ui->StatusBar->hide();
    //ui->ToolBar->hide();
}

void SmarkMainWindow::on_ActionViewReadMode_triggered()
{
    ui->EditorWidget->hide();
    ui->HtmlView->show();
    //ui->StatusBar->hide();
    //ui->ToolBar->hide();
}

void SmarkMainWindow::on_ActionViewVerticalLayout_triggered()
{
    ui->MainSplitter->setOrientation(Qt::Vertical);
    ui->CSSSplitter->setOrientation(Qt::Horizontal);
    ui->EditorWidget->show();
    ui->HtmlView->show();
    //ui->StatusBar->show();
    //ui->ToolBar->show();
}

void SmarkMainWindow::on_ActionViewHorizontal_Layout_triggered()
{
    ui->MainSplitter->setOrientation(Qt::Horizontal);
    ui->CSSSplitter->setOrientation(Qt::Vertical);
    ui->EditorWidget->show();
    ui->HtmlView->show();
    //ui->StatusBar->show();
    //ui->ToolBar->show();
}

void SmarkMainWindow::on_ActionViewShowMenuBar_triggered()
{
    if(ui->MenuBar->isHidden())
        ui->MenuBar->show();
    else
        ui->MenuBar->hide();
}

void SmarkMainWindow::on_ActionViewShowStatusBar_triggered()
{
    if(ui->StatusBar->isHidden())
        ui->StatusBar->show();
    else
        ui->StatusBar->hide();
}

void SmarkMainWindow::on_ActionViewShowToolBar_triggered()
{
    if(ui->ToolBar->isHidden())
        ui->ToolBar->show();
    else
        ui->ToolBar->hide();
}

/* *****************************************************************************
 *
 *                              Edit Menu
 *
 * ****************************************************************************/

void SmarkMainWindow::on_ActionEditInsertImage_triggered()
{
    if(ui->Editor->hasFocus()) {
        ui->Editor->insertImage();
    }
}

void SmarkMainWindow::on_ActionEditInsertLink_triggered()
{
    if(ui->Editor->hasFocus()) {
        ui->Editor->insertLink();
    }
}

void SmarkMainWindow::on_ActionEditCSS_triggered()
{
    if(ui->CSSWidget->isHidden()) {
        ui->CSSEditor->setPlainText(ui->HtmlView->CSS());
        ui->CSSWidget->show();
        ui->CSSEditor->setFocus();
    } else {
        ui->CSSWidget->hide();
        ui->Editor->setFocus();
    }
}

void SmarkMainWindow::on_ActionEditUndo_triggered()
{
    if(ui->Editor->hasFocus()) {
        ui->Editor->undo();
    }
}

void SmarkMainWindow::on_ActionEditRedo_triggered()
{
    if(ui->Editor->hasFocus()) {
        ui->Editor->redo();
    }
}

void SmarkMainWindow::on_ActionEditCut_triggered()
{
    if(ui->Editor->hasFocus()) {
        ui->Editor->cut();
    }
}

void SmarkMainWindow::on_ActionEditCopy_triggered()
{
    if(ui->Editor->hasFocus()) {
        ui->Editor->copy();
    }
}

void SmarkMainWindow::on_ActionEditPaste_triggered()
{
    if(ui->Editor->hasFocus()) {
        ui->Editor->paste();
    }
}

void SmarkMainWindow::on_ActionEditSearch_triggered()
{
    if(ui->SearchWidget->isHidden()) {
        ui->SearchWidget->show();
    }
    QString selected = ui->Editor->textCursor().selectedText();
    ui->SearchLineEdit->setText(selected);
    ui->NextButton->setFocus();
}

void SmarkMainWindow::on_ActionEditFlush_triggered()
{
    //_do_SaveDocument();
    _do_RunPandoc();
    if(ui->HtmlView->isHidden())
        ui->HtmlView->show();
}

/* *****************************************************************************
 *
 *                              Format Menu
 *
 * ****************************************************************************/

void SmarkMainWindow::on_ActionFormatBlod_triggered()
{
    if(ui->Editor->hasFocus()) {
        ui->Editor->setSelectedBlod();
    }
}

void SmarkMainWindow::on_ActionFormatItalic_triggered()
{
    if(ui->Editor->hasFocus()) {
        ui->Editor->setSelectedItalic();
    }
}

void SmarkMainWindow::on_ActionFormatUnderLine_triggered()
{
    if(ui->Editor->hasFocus()) {
        ui->Editor->setSelectedUnderLine();
    }
}

void SmarkMainWindow::on_ActionFormatDeleted_triggered()
{
    if(ui->Editor->hasFocus()) {
        ui->Editor->setSelectedDeleted();
    }
}

void SmarkMainWindow::on_ActionFormatQuote_triggered()
{
    if(ui->Editor->hasFocus()) {
        ui->Editor->setSelectedQuote();
    }
}

void SmarkMainWindow::on_ActionFormatCode_triggered()
{
    if(ui->Editor->hasFocus()) {
        ui->Editor->setSelectedCode();
    }
}

void SmarkMainWindow::on_ActionFormatSub_triggered()
{
    if(ui->Editor->hasFocus()) {
        ui->Editor->setSelectedSub();
    }
}

void SmarkMainWindow::on_ActionFormatSup_triggered()
{
    if(ui->Editor->hasFocus()) {
        ui->Editor->setSelectedSup();
    }
}

void SmarkMainWindow::on_ActionFormatBigger_triggered()
{
    if(ui->Editor->hasFocus()) {
        ui->Editor->setSelectedBigger();
    }
}

void SmarkMainWindow::on_ActionFormatSmaller_triggered()
{
    if(ui->Editor->hasFocus()) {
        ui->Editor->setSelectedSmaller();
    }
}

void SmarkMainWindow::on_ActionFormatOrderedList_triggered()
{
    if(ui->Editor->hasFocus()) {
        ui->Editor->setSelectedOrderedList();
    }
}

void SmarkMainWindow::on_ActionFormatUnorderedList_triggered()
{
    if(ui->Editor->hasFocus()) {
        ui->Editor->setSelectedUnorderedList();
    }
}

/* *****************************************************************************
 *
 *                              Help Menu
 *
 * ****************************************************************************/

void SmarkMainWindow::on_ActionHelpHome_triggered()
{
    ui->HtmlView->setEnabled(true);
    ui->HtmlView->load(QUrl("http://sites.google.com/site/smarkwebsite/"));
}

void SmarkMainWindow::on_ActionHelpAbout_triggered()
{
    QMessageBox::about(this, QSTR("About Smark"),
                       QSTR("<h1>Smark 0.0 Alpha</h1>"
                            "<p>A Markdown Editor bases on Qt & Pandoc under GPL</p>"
                            "<a href=\"https://sites.google.com/site/smarkwebsite/home\">Project home page</a>"));
}

void SmarkMainWindow::on_ActionHelpAboutQt_triggered()
{
    QMessageBox::aboutQt(this, QSTR("About Qt"));
}

/* *****************************************************************************
 *
 *                              Search Widget
 *
 * ****************************************************************************/

void SmarkMainWindow::on_PrevButton_clicked() {
    ui->Editor->findPrevious(ui->SearchLineEdit->text(),
                             ui->CaseCheckBox->isChecked(),
                             ui->WholeWordCheckBox->isChecked());
}

void SmarkMainWindow::on_NextButton_clicked() {
    ui->Editor->findNext(ui->SearchLineEdit->text(),
                         ui->CaseCheckBox->isChecked(),
                         ui->WholeWordCheckBox->isChecked());
}

void SmarkMainWindow::on_ReplaceButton_clicked() {
    ui->Editor->replaceCurrent(ui->ReplaceLineEdit->text());
}

void SmarkMainWindow::on_ReplaceAllButton_clicked() {
    ui->Editor->replaceAll(ui->SearchLineEdit->text(),
                           ui->ReplaceLineEdit->text());
}


void SmarkMainWindow::on_SearchHideButton_clicked()
{
    if(! ui->SearchWidget->isHidden())
        ui->SearchWidget->hide();
}

/* *****************************************************************************
 *
 *                              CSS Edit Widget
 *
 * ****************************************************************************/

void SmarkMainWindow::on_CSSLoadButton_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, QSTR("Load CSS File"),
                                                ::VizFileDir(_current_path),
                                                QSTR("CSS (*.css)"));
    if(! path.isEmpty()) {
        QString CSS_text;
        IO_LoadCSS(path, &CSS_text);
        ui->CSSEditor->setPlainText(CSS_text);
    }
}

void SmarkMainWindow::on_CSSApplyButton_clicked()
{
    ui->HtmlView->setCSS(ui->CSSEditor->toPlainText());
    _do_RunPandoc();
}

void SmarkMainWindow::on_CSSDefaultButton_clicked()
{
    QString CSS_text;
    IO_LoadCSS(QSTR("://TEXT/preview.css"), &CSS_text);
    ui->CSSEditor->setPlainText(CSS_text);
}

void SmarkMainWindow::when_text_edited() {
    _is_modified = true;
}


/* *****************************************************************************
 *
 *                              GUI Initial
 *
 * ****************************************************************************/

void SmarkMainWindow::_do_initialGUI()
{
    // ui->Editor->setAcceptDrops(false);
    // ui->HtmlView->setAcceptDrops(false);
    setAcceptDrops(true);
}

void SmarkMainWindow::_do_ApplyGUIOption(const SmarkOption& option)
{
    if(this->isMaximized()) {
        this->showMaximized();
    } else {
        resize(option.WndWidth, option.WndHeight);
    }

    ui->ActionViewFullScreen->setChecked(option.FullScreen);
    ui->ActionViewShowToolBar->setChecked(option.ShowToolBar);
    ui->ActionViewShowStatusBar->setChecked(option.ShowStatusBar);
    ui->StatusBar->hide();
    ui->ActionViewShowMenuBar->setChecked(option.ShowMenuBar);
    ui->SearchWidget->hide();
    ui->CSSWidget->hide();

    QPalette palette;
    palette.setColor(QPalette::Base, option.BkgColor);
    palette.setColor(QPalette::Text, option.TextColor);
    ui->Editor->setPalette(palette);
    ui->CSSEditor->setPalette(palette);

    QFont font;
    font.setFamily(option.TextFontFamily);
    font.setPointSize(option.TextFontSize);
    ui->Editor->setFont(font);
    ui->CSSEditor->setFont(font);
}

void SmarkMainWindow::_do_SignalSlotConnect()
{
    connect(ui->Editor, SIGNAL(textChanged()),
            this, SLOT(when_text_edited()) );
    connect(ui->Editor, SIGNAL(editorScroll(float)),
            ui->HtmlView, SLOT(setScrollRatio(float)) );
//    connect(ui->ToolBar, SIGNAL(visibilityChanged(bool)),
//            this, SLOT(on_ActionViewShowToolBar_triggered()) );
    connect(&_pandoc_executor, SIGNAL(completed()),
            this, SLOT(when_PandocProcess_finished()) );
}

void SmarkMainWindow::_do_LockGUI()
{
    // File Menu
    ui->ActionFileSave->setEnabled(false);
    ui->ActionFileSaveAs->setEnabled(false);
    ui->ActionFileExport->setEnabled(false);
    ui->ActionFilePrint->setEnabled(false);

    // Edit Menu
    ui->ActionEditInsertImage->setEnabled(false);
    ui->ActionEditInsertLink->setEnabled(false);
    ui->ActionEditCSS->setEnabled(false);
    ui->ActionEditUndo->setEnabled(false);
    ui->ActionEditRedo->setEnabled(false);
    ui->ActionEditCut->setEnabled(false);
    ui->ActionEditCopy->setEnabled(false);
    ui->ActionEditPaste->setEnabled(false);
    ui->ActionEditSearch->setEnabled(false);
    ui->ActionEditFlush->setEnabled(false);

    // Format Menu
    ui->ActionFormatBlod->setEnabled(false);
    ui->ActionFormatItalic->setEnabled(false);
    ui->ActionFormatUnderLine->setEnabled(false);
    ui->ActionFormatDeleted->setEnabled(false);
    ui->ActionFormatQuote->setEnabled(false);
    ui->ActionFormatCode->setEnabled(false);
    ui->ActionFormatSub->setEnabled(false);
    ui->ActionFormatSup->setEnabled(false);
    ui->ActionFormatBigger->setEnabled(false);
    ui->ActionFormatSmaller->setEnabled(false);
    ui->ActionFormatOrderedList->setEnabled(false);
    ui->ActionFormatUnorderedList->setEnabled(false);

    // Center Widget
    ui->EditorWidget->setEnabled(false);
    // ui->HtmlView->setEnabled(false);
}

void SmarkMainWindow::_do_UnlockGUI()
{
    // File Menu
    ui->ActionFileSave->setEnabled(true);
    ui->ActionFileSaveAs->setEnabled(true);
    ui->ActionFileExport->setEnabled(true);
    ui->ActionFilePrint->setEnabled(true);

    // Edit Menu
    ui->ActionEditInsertImage->setEnabled(true);
    ui->ActionEditInsertLink->setEnabled(true);
    ui->ActionEditCSS->setEnabled(true);
    ui->ActionEditUndo->setEnabled(true);
    ui->ActionEditRedo->setEnabled(true);
    ui->ActionEditCut->setEnabled(true);
    ui->ActionEditCopy->setEnabled(true);
    ui->ActionEditPaste->setEnabled(true);
    ui->ActionEditSearch->setEnabled(true);
    ui->ActionEditFlush->setEnabled(true);

    // Format Menu
    ui->ActionFormatBlod->setEnabled(true);
    ui->ActionFormatItalic->setEnabled(true);
    ui->ActionFormatUnderLine->setEnabled(true);
    ui->ActionFormatDeleted->setEnabled(true);
    ui->ActionFormatQuote->setEnabled(true);
    ui->ActionFormatCode->setEnabled(true);
    ui->ActionFormatSub->setEnabled(true);
    ui->ActionFormatSup->setEnabled(true);
    ui->ActionFormatBigger->setEnabled(true);
    ui->ActionFormatSmaller->setEnabled(true);
    ui->ActionFormatOrderedList->setEnabled(true);
    ui->ActionFormatUnorderedList->setEnabled(true);

    // Center Widget
    ui->EditorWidget->setEnabled(true);
    // ui->HtmlView->setEnabled(true);
}

/* *****************************************************************************
 *
 *                              Document IO
 *
 * ****************************************************************************/

bool SmarkMainWindow::_do_NewDocument()
{
    if(! _do_CloseDocument()) return false;
    _is_modified = true;
    _do_SetCurrentPath(VIZ_EMPTY_QSTR);
    return true;
}

bool SmarkMainWindow::_do_OpenDocument()
{
    // close current project at first
    if(! _do_CloseDocument()) return false;

    // get open file name
    QString path = QFileDialog::getOpenFileName(
                this, QSTR("Open File"),
                ::VizFileDir(_current_path),
                QSTR("Markdown Files (*.markdown *.md *mkd)"));
    if(path.isEmpty()) return false;

    // load the markdown file
    QString err_info, md_text;
    if(! ::IO_LoadMarkdown(path, &md_text, &err_info)) {
        QMessageBox::warning(this, QSTR("Error"), err_info);
        return false;
    }
    ui->Editor->setPlainText(md_text);

    _do_SetCurrentPath(path);
    //_is_modified = false;
    return true;
}

bool SmarkMainWindow::_do_SaveDocument()
{
    if(_current_path.isEmpty()) {
        // need choose a path to save
        QString path;
        path = QFileDialog::getSaveFileName(this,
                                            QSTR("Save Document"),
                                            _current_path,
                                            QSTR("Markdown Files (*.markdown *.md *mkd)"));
        if(path.isEmpty()) {
            return false;
        } else {
            _do_SetCurrentPath(path);
        }
    }

    QString err_info, md_text;
    md_text = ui->Editor->toPlainText();
    if(! ::IO_SaveMarkdown(_current_path, md_text, &err_info)) {
        QMessageBox::warning(this, QSTR("Error"), err_info);
        return false;
    }

    _is_modified = false;
    return true;
}

bool SmarkMainWindow::_do_SaveDocumentAs()
{
    QString path = QFileDialog::getSaveFileName(this,
                                                QSTR("Save Document"),
                                                ::VizFileDir(_current_path)+QSTR("/Untitled.md"),
                                                QSTR("Markdown Files (*.markdown *.md *mkd)"));
    if(path.isEmpty()) return false;

    QString err_info, md_text;
    md_text = ui->Editor->toPlainText();
    if(! ::IO_SaveMarkdown(path, md_text, &err_info)) {
        QMessageBox::warning(this, QSTR("Error"), err_info);
        return false;
    }
    return true;
}

bool SmarkMainWindow::_do_CloseDocument()
{
    if(_is_modified)
    {
        QMessageBox::StandardButton select = QMessageBox::warning(
                    this,
                    QSTR("Warning"),
                    QSTR("Do you want to save your"
                         " modifications to the current document ?"),
                    QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel,
                    QMessageBox::Cancel);

        if(QMessageBox::Cancel == select) {
            return false;
        } else if(QMessageBox::Yes == select) {
            _do_SaveDocument();
            //            if(!_current_path.isEmpty())
            //                ::IO_RemoveFile(CacheFilePath(_current_path));
        } else {
            //            if(!_current_path.isEmpty())
            //                ::IO_RemoveFile(CacheFilePath(_current_path));
        }
    }

    // do clear project
    ui->Editor->clear();
    ui->HtmlView->clearHtml();
    _do_SetCurrentPath(VIZ_EMPTY_QSTR);
    _is_modified = false;
    return true;
}

void SmarkMainWindow::_do_SetCurrentPath(const QString& path)
{
    if(path.isEmpty()) {
        _current_path.clear();;
        _current_md_cache.clear();;
        _current_html_cache.clear();
        this->setWindowTitle(QSTR("Smark"));
    } else {
        _current_path = path;
        _current_md_cache = ::IO_MDCachePath(path);
        _current_html_cache = ::IO_HtmlCachePath(path);
        QString wnd_title =  QSTR("Smark - ") + ::VizFileName(path);
        this->setWindowTitle(wnd_title);
    }
}

void SmarkMainWindow::_do_UpdateHtmlView()
{
//    if(! _current_path.isEmpty()) {
//        ui->HtmlView->loadHtmlFile(_current_html_cache);
//    } else {
//        ui->HtmlView->clearHtml();
//    }
}

/* *****************************************************************************
 *
 *                              Call pandoc
 *
 * ****************************************************************************/

void SmarkMainWindow::_do_RunPandoc()
{
    QString err_info, md_text;
    md_text = ui->Editor->toPlainText();
    if(! ::IO_SaveMarkdown(_current_md_cache, md_text, &err_info)) {
        QMessageBox::warning(this, QSTR("Error"), err_info);
        return;
    }
    _pandoc_executor.execuate(_current_md_cache,
                              _current_html_cache);
}

void SmarkMainWindow::when_PandocProcess_finished()
{
    if(! _current_path.isEmpty()) {
        int position = ui->HtmlView->scrollValue();
        ui->HtmlView->loadHtmlFile(_current_html_cache);
        ui->HtmlView->setScrollValue(position);
        ::IO_RemoveFile(_current_html_cache);
        ::IO_RemoveFile(_current_md_cache);
    } else {
        ui->HtmlView->clearHtml();
    }
}
