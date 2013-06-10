#ifndef GUI_SMARK_OPTION_DIALOG_H
#define GUI_SMARK_OPTION_DIALOG_H

#include <QDialog>
#include "GUI/SmarkOption.h"

namespace Ui {
class SmarkOptionDialog;
}

class SmarkOptionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SmarkOptionDialog(QWidget *parent = 0);
    ~SmarkOptionDialog();

    void InitDialog(const SmarkOption& option);

    SmarkOption option() const;

private slots:
    void on_BKColorButton_clicked();
    void on_TextColorButton_clicked();
    void on_SetDefaultButton_clicked();

private:
    Ui::SmarkOptionDialog *ui;
    int _old_width, _old_height;
};

#endif // GUI_SMARK_OPTION_DIALOG_H
