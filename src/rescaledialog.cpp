#include "rescaledialog.h"
#include "ui_rescaledialog.h"

rescaleDialog::rescaleDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::rescaleDialog)
{
    ui->setupUi(this);
    this->setFixedSize(QSize(350,200));
}

rescaleDialog::~rescaleDialog()
{
    delete ui;
}


void rescaleDialog::on_horizontalSlider_valueChanged(int position)
{
    double newScale = (double)position / 100.0;
    ui->scaleLabel->setNum(newScale);
}

double rescaleDialog::getRescaleFactor()
{
    return ui->scaleLabel->text().toDouble();
}
