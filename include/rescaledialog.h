#ifndef RESCALEDIALOG_H
#define RESCALEDIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class rescaleDialog; }
QT_END_NAMESPACE

class rescaleDialog : public QDialog
{
    Q_OBJECT

public:
    rescaleDialog(QWidget *parent = nullptr);
    ~rescaleDialog();

    double getRescaleFactor();

private slots:
    void on_horizontalSlider_valueChanged(int position);

private:
    Ui::rescaleDialog *ui;
};
#endif // RESCALEDIALOG_H
