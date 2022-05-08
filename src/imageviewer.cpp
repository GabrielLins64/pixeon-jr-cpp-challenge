#include "imageviewer.hpp"
#include "imageeditor.hpp"
#include "rescaledialog.h"
#include "brightnessdialog.h"
#include "contrastdialog.h"
#include <QGuiApplication>
#include <QFileDialog>
#include <QStandardPaths>
#include <QImageReader>
#include <QImageWriter>
#include <QMessageBox>
#include <QStatusBar>

ImageViewer::ImageViewer()
    : imagesList(new QListWidget),
      imageLabel(new QLabel),
      scrollArea(new QScrollArea),
      scaleFactor(1)
{
    renderWorkArea();

    createActions();
    resize(QGuiApplication::primaryScreen()->availableSize() * 3 / 5);

    statusBar()->showMessage("Welcome to the Pixeon Challenge's Image Viewer!", 3000);
}

void ImageViewer::renderWorkArea()
{
    const QString mainCss = "QMainWindow {"
                            "    background-image: url('assets/images/logo-pixeon.png');"
                            "    background-color: #ebebeb;"
                            "    background-repeat: no-repeat;"
                            "    background-position: center center"
                            "}";
    this->setStyleSheet(mainCss);

    imageLabel->setBackgroundRole(QPalette::Base);
    imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel->setScaledContents(true);

    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setWidget(imageLabel);
    scrollArea->setVisible(false);

    imagesList->setFixedWidth(200);
    imagesList->setIconSize(QSize(50,50));
    imagesList->setVisible(false);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(imagesList);
    layout->addWidget(scrollArea);

    QWidget *window = new QWidget();
    window->setLayout(layout);
    setCentralWidget(window);

    connect(imagesList,
            &QListWidget::itemClicked,
            this,
            &ImageViewer::onImagesListItemClicked);
}

static void initializeImageFileDialog(QFileDialog &dialog)
{
    static bool firstDialog = true;

    if (firstDialog)
    {
        firstDialog = false;
        const QStringList picturesLocations = QStandardPaths::standardLocations(QStandardPaths::PicturesLocation);
        dialog.setDirectory(picturesLocations.isEmpty() ? QDir::currentPath() : picturesLocations.last());
    }

    QStringList mimeTypeFilters({"image/jpeg", "image/bmp", "image/png"});

    dialog.setMimeTypeFilters(mimeTypeFilters);
    dialog.selectMimeTypeFilter("image/jpeg");
}

void ImageViewer::open()
{
    QFileDialog dialog(this, tr("Open File"));
    initializeImageFileDialog(dialog);

    while (dialog.exec() == QDialog::Accepted && !loadFile(dialog.selectedFiles().first())) {}
}

void ImageViewer::close()
{
    auto *imageWidget = imagesList->findItems(currentFileName, Qt::MatchExactly).first();
    imagesList->takeItem(imagesList->row(imageWidget));
    images.erase(currentFileName);
    imagesPath.erase(currentFileName);

    if (imagesList->count() == 0)
    {
        image = new QImage();
        scrollArea->setVisible(false);
        imagesList->setVisible(false);
        updateActions();
    }
    else
    {
        QListWidgetItem *lastItem = imagesList->item(0);
        imagesList->setCurrentRow(0);
        currentFileName = lastItem->text();
        setImage(images[lastItem->text()]);
    }
}

void ImageViewer::save()
{
    while (!saveFile(imagesPath[currentFileName])) {}
}

void ImageViewer::saveAs()
{
    QFileDialog dialog(this);
    QString saveFilePath = dialog.getSaveFileName(this, "Save File As", this->currentFileName);

    // Dealing with possible filename changing
    auto tmpImage = images[currentFileName];
    images.erase(currentFileName);
    currentFileName = saveFilePath.split('/').last();
    images[currentFileName] = tmpImage;
    imagesList->selectedItems().at(0)->setText(currentFileName);

    if (saveFilePath.isNull())
        return;

    while (!saveFile(saveFilePath)) {}
}

bool ImageViewer::loadFile(const QString &filePath)
{
    QImageReader reader(filePath);

    reader.setAutoTransform(true);
    const QImage newImage = reader.read();
    if (newImage.isNull())
    {
        QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
                                 tr("Cannot load %1: %2")
                                     .arg(QDir::toNativeSeparators(filePath), reader.errorString()));
        return false;
    }

    currentFileName = filePath.split('/').last();
    imagesPath[currentFileName] = filePath;
    QListWidgetItem *newItem = new QListWidgetItem;
    newItem->setText(currentFileName);
    newItem->setIcon(QIcon(filePath));
    imagesList->addItem(newItem);
    imagesList->setItemSelected(newItem, true);
    images[currentFileName] = newImage;

    setImage(newImage);

    setWindowFilePath(filePath);

    const QString message = tr("Opened \"%1\", %2x%3, Depth: %4")
                                .arg(QDir::toNativeSeparators(filePath))
                                .arg(image->width())
                                .arg(image->height())
                                .arg(image->depth());
    statusBar()->showMessage(message);
    return true;
}

void ImageViewer::onImagesListItemClicked(QListWidgetItem *clickedItem)
{
    QString imageName = clickedItem->text();
    QImage selectedImage = images[imageName];
    currentFileName = imageName;

    setImage(selectedImage);
}

void ImageViewer::setImage(const QImage &newImage)
{
    image = new QImage(newImage);
    imageLabel->setPixmap(QPixmap::fromImage(*image));
    scaleFactor = 1.0;

    scrollArea->setVisible(true);
    imagesList->setVisible(true);
    fitToWindowAct->setEnabled(true);
    updateActions();

    if (!fitToWindowAct->isChecked())
        imageLabel->adjustSize();
}

bool ImageViewer::saveFile(const QString &fileName)
{
    QImageWriter writer(fileName);

    if (!writer.write(*image))
    {
        QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
                                 tr("Cannot write %1: %2")
                                     .arg(QDir::toNativeSeparators(fileName)),
                                 writer.errorString());
        return false;
    }
    const QString message = tr("Wrote \"%1\"").arg(QDir::toNativeSeparators(fileName));
    statusBar()->showMessage(message);
    return true;
}

void ImageViewer::zoomIn()
{
    scaleImage(1.25);
}

void ImageViewer::zoomOut()
{
    scaleImage(0.8);
}

void ImageViewer::normalSize()
{
    imageLabel->adjustSize();
    scaleFactor = 1.0;
}

void ImageViewer::fitToWindow()
{
    bool fitToWindow = fitToWindowAct->isChecked();
    scrollArea->setWidgetResizable(fitToWindow);
    if (!fitToWindow)
        normalSize();
    updateActions();
}

void ImageViewer::copy()
{
#ifndef QT_NO_CLIPBOARD
    QGuiApplication::clipboard()->setImage(*image);
#endif // !QT_NO_CLIPBOARD
}

#ifndef QT_NO_CLIPBOARD
static QImage clipboardImage()
{
    if (const QMimeData *mimeData = QGuiApplication::clipboard()->mimeData())
    {
        if (mimeData->hasImage())
        {
            const QImage image = qvariant_cast<QImage>(mimeData->imageData());
            if (!image.isNull())
                return image;
        }
    }
    return QImage();
}
#endif // !QT_NO_CLIPBOARD

void ImageViewer::paste()
{
#ifndef QT_NO_CLIPBOARD
    const QImage newImage = clipboardImage();
    if (newImage.isNull())
    {
        statusBar()->showMessage(tr("No image in clipboard"));
    }
    else
    {
        setImage(newImage);
        setWindowFilePath(QString());
        const QString message = tr("Obtained image from clipboard, %1x%2, Depth: %3")
                                    .arg(newImage.width())
                                    .arg(newImage.height())
                                    .arg(newImage.depth());
        statusBar()->showMessage(message);
    }
#endif // !QT_NO_CLIPBOARD
}

void ImageViewer::about()
{
    QMessageBox::about(this,
                       tr("About Image Viewer"),
                       tr("<p>The <b>Image Viewer</b> example shows how to combine QLabel "
                          "and QScrollArea to display an image. QLabel is typically used "
                          "for displaying a text, but it can also display an image. "
                          "QScrollArea provides a scrolling view around another widget. "
                          "If the child widget exceeds the size of the frame, QScrollArea "
                          "automatically provides scroll bars. </p><p>The example "
                          "demonstrates how QLabel's ability to scale its contents "
                          "(QLabel::scaledContents), and QScrollArea's ability to "
                          "automatically resize its contents "
                          "(QScrollArea::widgetResizable), can be used to implement "
                          "zooming and scaling features. </p><p>In addition the example "
                          "shows how to use QPainter to print an image.</p>"));
}

void ImageViewer::createActions()
{
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));

    QAction *openAct = fileMenu->addAction(tr("&Open..."), this, &ImageViewer::open);
    openAct->setShortcut(QKeySequence::Open);

    saveAct = fileMenu->addAction(tr("Save"), this, &ImageViewer::save);
    saveAct->setShortcut(tr("Ctrl+S"));
    saveAct->setEnabled(false);

    saveAsAct = fileMenu->addAction(tr("Save As..."), this, &ImageViewer::saveAs);
    saveAsAct->setShortcut(tr("Ctrl+Shift+S"));
    saveAsAct->setEnabled(false);

    closeAct = fileMenu->addAction(tr("Close image"), this, &ImageViewer::close);
    closeAct->setEnabled(false);

    fileMenu->addSeparator();

    QAction *exitAct = fileMenu->addAction(tr("Exit"), this, &QWidget::close);
    exitAct->setShortcut(tr("Ctrl+Q"));

    QMenu *editMenu = menuBar()->addMenu(tr("&Edit"));

    copyAct = editMenu->addAction(tr("&Copy"), this, &ImageViewer::copy);
    copyAct->setShortcut(QKeySequence::Copy);
    copyAct->setEnabled(false);

    QAction *pasteAct = editMenu->addAction(tr("&Paste"), this, &ImageViewer::paste);
    pasteAct->setShortcut(QKeySequence::Paste);

    rotateClockwiseAct = editMenu->addAction(tr("Rotate Clockwise"),
                                             this,
                                             &ImageViewer::rotateClockwise);
    rotateClockwiseAct->setShortcut(tr("Ctrl+R"));
    rotateClockwiseAct->setEnabled(false);

    rotateCounterClockwiseAct = editMenu->addAction(tr("Rotate Counterclockwise"),
                                                    this,
                                                    &ImageViewer::rotateCounterClockwise);
    rotateCounterClockwiseAct->setShortcut(tr("Ctrl+Shift+R"));
    rotateCounterClockwiseAct->setEnabled(false);

    rescaleImageAct = editMenu->addAction(tr("Rescale"), this, &ImageViewer::rescaleImage);
    rescaleImageAct->setShortcut(tr("Ctrl+H"));
    rescaleImageAct->setEnabled(false);

    adjustImageBrightnessAct = editMenu->addAction(tr("Adjust Brightness"), this, &ImageViewer::onAdjustImageBrightness);
    adjustImageBrightnessAct->setShortcut(tr("Ctrl+B"));
    adjustImageBrightnessAct->setEnabled(false);

    adjustContrastAct = editMenu->addAction(tr("Adjust Contrast"), this, &ImageViewer::onAdjustContrast);
    adjustContrastAct->setShortcut(tr("Ctrl+T"));
    adjustContrastAct->setEnabled(false);

    QMenu *viewMenu = menuBar()->addMenu(tr("&View"));

    zoomInAct = viewMenu->addAction(tr("Zoom In (25%)"), this, &ImageViewer::zoomIn);
    zoomInAct->setShortcut(QKeySequence::ZoomIn);
    zoomInAct->setEnabled(false);

    zoomOutAct = viewMenu->addAction(tr("Zoom Out (25%)"), this, &ImageViewer::zoomOut);
    zoomOutAct->setShortcut(QKeySequence::ZoomOut);
    zoomOutAct->setEnabled(false);

    normalSizeAct = viewMenu->addAction(tr("&Normal Size"), this, &ImageViewer::normalSize);
    normalSizeAct->setShortcut(tr("Ctrl+N"));
    normalSizeAct->setEnabled(false);

    viewMenu->addSeparator();

    fitToWindowAct = viewMenu->addAction(tr("&Fit to Window"), this, &ImageViewer::fitToWindow);
    fitToWindowAct->setEnabled(false);
    fitToWindowAct->setCheckable(true);
    fitToWindowAct->setShortcut(tr("Ctrl+F"));

    QMenu *helpMenu = menuBar()->addMenu(tr("&Help"));

    helpMenu->addAction(tr("&About"), this, &ImageViewer::about);
    helpMenu->addAction(tr("About &Qt"), &QApplication::aboutQt);
}

void ImageViewer::updateActions()
{
    saveAct->setEnabled(!image->isNull());
    saveAsAct->setEnabled(!image->isNull());
    closeAct->setEnabled(!image->isNull());
    copyAct->setEnabled(!image->isNull());
    rotateClockwiseAct->setEnabled(!image->isNull());
    rotateCounterClockwiseAct->setEnabled(!image->isNull());
    rescaleImageAct->setEnabled(!image->isNull());
    adjustImageBrightnessAct->setEnabled(!image->isNull());
    adjustContrastAct->setEnabled(!image->isNull());
    zoomInAct->setEnabled(!fitToWindowAct->isChecked());
    zoomOutAct->setEnabled(!fitToWindowAct->isChecked());
    normalSizeAct->setEnabled(!fitToWindowAct->isChecked());
}

void ImageViewer::scaleImage(double factor)
{
    Q_ASSERT(imageLabel->pixmap());
    scaleFactor *= factor;
    imageLabel->resize(scaleFactor * imageLabel->pixmap()->size());

    adjustScrollBar(scrollArea->horizontalScrollBar(), factor);
    adjustScrollBar(scrollArea->verticalScrollBar(), factor);

    zoomInAct->setEnabled(scaleFactor < 3.0);
    zoomOutAct->setEnabled(scaleFactor > 0.333);
}

void ImageViewer::adjustScrollBar(QScrollBar *scrollBar, double factor)
{
    scrollBar->setValue(int(factor * scrollBar->value() + ((factor - 1) * scrollBar->pageStep() / 2)));
}

void ImageViewer::updateCurrentImage(QImage *image)
{
    images[currentFileName] = *image;
    setImage(*image);
}

void ImageViewer::rotateClockwise()
{
    ImageEditor::rotate(image, true);
    updateCurrentImage(image);
}

void ImageViewer::rotateCounterClockwise()
{
    ImageEditor::rotate(image, false);
    updateCurrentImage(image);
}

void ImageViewer::rescaleImage()
{
    RescaleDialog *rescDialog = new RescaleDialog();
    
    if (rescDialog->exec())
    {
        double rescaleFactor = rescDialog->getRescaleFactor();
        ImageEditor::rescale(image, rescaleFactor);
        updateCurrentImage(image);
    }
}

void ImageViewer::onAdjustImageBrightness()
{
    BrightnessDialog *brightnessDialog = new BrightnessDialog();

    connect(brightnessDialog->brightnessSlider,
            &QAbstractSlider::valueChanged,
            this,
            &ImageViewer::adjustImageBrightness);
    
    if (brightnessDialog->exec())
    {
        int brightnessFactor = brightnessDialog->getBrightnessFactor();
        ImageEditor::brightness(image, (double) brightnessFactor / 100.0);
        updateCurrentImage(image);
    }
    else
    {
        setImage(*image);
    }
}

void ImageViewer::adjustImageBrightness(int brightnessFactor)
{
    QImage original = image->copy();
    ImageEditor::brightness(image, (double) brightnessFactor / 100.0);
    setImage(*image);
    *image = original;
}

void ImageViewer::onAdjustContrast()
{
    ContrastDialog *contrastDialog = new ContrastDialog();

    connect(contrastDialog->contrastSlider,
            &QAbstractSlider::valueChanged,
            this,
            &ImageViewer::adjustContrast);
    
    if (contrastDialog->exec())
    {
        ImageEditor::contrast(image, contrastDialog->getContrastFactor());
        updateCurrentImage(image);
    }
    else
    {
        setImage(*image);
    }
}

void ImageViewer::adjustContrast(int contrastFactor)
{
    QImage original = image->copy();
    ImageEditor::contrast(image, contrastFactor);
    setImage(*image);
    *image = original;
}
