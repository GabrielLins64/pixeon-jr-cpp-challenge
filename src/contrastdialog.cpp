#include "contrastdialog.h"
#include "ui_contrastdialog.h"

ContrastDialog::ContrastDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::ContrastDialog)
{
    ui->setupUi(this);
    this->setFixedSize(QSize(350, 200));

    this->contrastSlider = ui->horizontalSlider;
}

ContrastDialog::~ContrastDialog()
{
    delete ui;
}

int ContrastDialog::getContrastFactor()
{
    return ui->horizontalSlider->value();
}
