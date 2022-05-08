#ifndef CONTRASTDIALOG_H
#define CONTRASTDIALOG_H

#include <QDialog>
#include <QSlider>

QT_BEGIN_NAMESPACE
namespace Ui { class ContrastDialog; }
QT_END_NAMESPACE

class ContrastDialog : public QDialog
{
    Q_OBJECT

public:
    ContrastDialog(QWidget *parent = nullptr);
    ~ContrastDialog();

    int getContrastFactor();

    QSlider *contrastSlider;

private:
    Ui::ContrastDialog *ui;
};
#endif // CONTRASTDIALOG_H
