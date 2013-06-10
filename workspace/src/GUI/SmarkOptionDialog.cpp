#include <QColorDialog>
#include "GUI/SmarkOptionDialog.h"
#include "ui_SmarkOptionDialog.h"

SmarkOptionDialog::SmarkOptionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SmarkOptionDialog)
{
    ui->setupUi(this);
}

SmarkOptionDialog::~SmarkOptionDialog()
{
    delete ui;
}

void SmarkOptionDialog::InitDialog(const SmarkOption& option)
{
    _old_width = option.WndWidth;
    _old_height = option.WndHeight;

    ui->FullScreenCheckBox->setChecked(option.FullScreen);
    ui->ShowMenuCheckBox->setChecked(option.ShowMenuBar);
    ui->ShowToolBarCheckBox->setChecked(option.ShowToolBar);
    ui->ShowStatusCheckBox->setChecked(option.ShowStatusBar);
    ui->BKColorLineEdit->setText(option.BkgColor.name());
    ui->TextColorLineEdit->setText(option.TextColor.name());
    ui->FontComboBox->setCurrentFont(QFont(option.TextFontFamily));
    ui->FontSizeSpinBox->setValue(option.TextFontSize);
}

SmarkOption SmarkOptionDialog::option() const
{
    SmarkOption option;
    option.init();

    option.WndHeight = _old_height;
    option.WndWidth = _old_width;

    option.FullScreen = ui->FullScreenCheckBox->isChecked();
    option.ShowMenuBar = ui->ShowMenuCheckBox->isChecked();
    option.ShowStatusBar = ui->ShowStatusCheckBox->isChecked();
    option.ShowToolBar = ui->ShowToolBarCheckBox->isChecked();
    option.BkgColor = QColor(ui->BKColorLineEdit->text());
    option.TextColor = QColor(ui->TextColorLineEdit->text());
    option.TextFontFamily = ui->FontComboBox->currentFont().family();
    option.TextFontSize = ui->FontSizeSpinBox->value();

    return option;
}

void SmarkOptionDialog::on_BKColorButton_clicked()
{
    QColor color = QColorDialog::getColor(QColor(ui->BKColorLineEdit->text()),
                                          this, tr("Select Background Color"));
    if(color.isValid())
        ui->BKColorLineEdit->setText(color.name());
}

void SmarkOptionDialog::on_TextColorButton_clicked()
{
    QColor color = QColorDialog::getColor(QColor(ui->TextColorLineEdit->text()),
                                          this, tr("Select Text Color"));
    if(color.isValid())
        ui->TextColorLineEdit->setText(color.name());
}

void SmarkOptionDialog::on_SetDefaultButton_clicked()
{
    SmarkOption option;
    option.init();
    InitDialog(option);
}
