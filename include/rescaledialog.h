#ifndef RESCALEDIALOG_H
#define RESCALEDIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class RescaleDialog; }
QT_END_NAMESPACE

class RescaleDialog : public QDialog
{
    Q_OBJECT

public:
    RescaleDialog(QWidget *parent = nullptr);
    ~RescaleDialog();

    double getRescaleFactor();

private slots:
    void on_horizontalSlider_valueChanged(int position);

private:
    Ui::RescaleDialog *ui;
};
#endif // RESCALEDIALOG_H
