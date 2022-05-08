#ifndef BRIGHTNESSDIALOG_H
#define BRIGHTNESSDIALOG_H

#include <QDialog>
#include <QSlider>

QT_BEGIN_NAMESPACE
namespace Ui { class BrightnessDialog; }
QT_END_NAMESPACE

class BrightnessDialog : public QDialog
{
    Q_OBJECT

public:
    BrightnessDialog(QWidget *parent = nullptr);
    ~BrightnessDialog();

    int getBrightnessFactor();

    QSlider *brightnessSlider;

private:
    Ui::BrightnessDialog *ui;
};
#endif // BRIGHTNESSDIALOG_H
