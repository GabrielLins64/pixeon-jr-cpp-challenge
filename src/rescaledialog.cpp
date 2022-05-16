#include "rescaledialog.h"
#include "ui_rescaledialog.h"

RescaleDialog::RescaleDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::RescaleDialog)
{
    ui->setupUi(this);
    this->setFixedSize(QSize(350, 200));
}

RescaleDialog::~RescaleDialog()
{
    delete ui;
}

void RescaleDialog::on_horizontalSlider_valueChanged(int position)
{
    double newScale = (double)position / 100.0;
    ui->scaleLabel->setNum(newScale);
}

double RescaleDialog::getRescaleFactor()
{
    return ui->scaleLabel->text().toDouble();
}
