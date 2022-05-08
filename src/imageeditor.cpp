#include "imageeditor.hpp"

void ImageEditor::rescale(QImage *image, double factor)
{
    int newWidth = factor * image->width();
    int newHeight = factor * image->height();
    *image = image->scaled(newWidth, newHeight, Qt::KeepAspectRatio);
}

void ImageEditor::rotate(QImage *image, bool clockwise)
{
    int theta = clockwise ? 90 : -90;
    QPoint imgCenter = image->rect().center();
    QMatrix auxMatrix;

    auxMatrix.translate(imgCenter.x(), imgCenter.y());
    auxMatrix.rotate(theta);
    *image = image->transformed(auxMatrix);
}

void ImageEditor::brightness(QImage *image, int factor) {}

void ImageEditor::contrast(QImage *image, int factor)
{
    if (factor < 0 || factor > 20)
        return;

    double contrast = (100.0 + factor) / 100.0;
    double r, g, b;
    int pixels = image->width() * image->height();
    unsigned int *data = (unsigned int *)image->bits();
    for (int i = 0; i < pixels; ++i) {
        r = 128 + contrast * (qRed(data[i]) - 128);
        r = (r < 0x00) ? 0x00 : (r > 0xff) ? 0xff : r;
        g= 128+ contrast*(qGreen(data[i]) - 128);
        g = (g < 0x00) ? 0x00 : (g > 0xff) ? 0xff : g;
        b= 128+ contrast*(qBlue(data[i]) - 128);
        b =  (b  < 0x00) ? 0x00 : (b  > 0xff) ? 0xff : b ;
        data[i] = qRgba(r, g, b, qAlpha(data[i]));
    }
}
