#include "brightnessdialog.h"
#include "ui_brightnessdialog.h"

BrightnessDialog::BrightnessDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::BrightnessDialog)
{
    ui->setupUi(this);
    this->setFixedSize(QSize(350, 200));

    this->brightnessSlider = ui->horizontalSlider;
}

BrightnessDialog::~BrightnessDialog()
{
    delete ui;
}

int BrightnessDialog::getBrightnessFactor()
{
    return ui->horizontalSlider->value();
}
