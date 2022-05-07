#pragma once

#include <QMainWindow>
#include <QtWidgets>
#include <QScrollBar>
#include <QLabel>
#include <QScrollArea>
#include <QPrinter>

class ImageViewer : public QMainWindow
{
    Q_OBJECT

public:
    ImageViewer();

    /**
     * @brief 
     * 
     * @return true 
     * @return false 
     */
    bool loadFile(const QString &);

private slots:

    /**
     * @brief Open an image
     * 
     */
    void open();

    /**
     * @brief Save the current image at the same opened file
     * 
     */
    void save();

    /**
     * @brief Opens a file dialog for saving the current image
     * 
     */
    void saveAs();

    /**
     * @brief Copy the current image to the clipboard
     * 
     */
    void copy();

    /**
     * @brief Paste the clipboard image, if any, to the viewer
     * 
     */
    void paste();

    /**
     * @brief Increases the aspect ratio to the viewing image
     * 
     */
    void zoomIn();

    /**
     * @brief Decreases the aspect ratio to the viewing image
     * 
     */
    void zoomOut();

    /**
     * @brief Return the current image to its original size
     * 
     */
    void normalSize();

    /**
     * @brief Resize the current image to fit the image viewing area
     * 
     */
    void fitToWindow();

    /**
     * @brief Open a dialog with information about the software
     * 
     */
    void about();

private:

    /**
     * @brief Create all menu actions
     * 
     */
    void createActions();

    /**
     * @brief 
     * 
     */
    void updateActions();

    /**
     * @brief Save a file
     * 
     * @param fileName Name of the file
     * @return true 
     * @return false 
     */
    bool saveFile(const QString &fileName);

    /**
     * @brief Place the newImage into the image Label (area)
     * 
     * @param newImage 
     */
    void setImage(const QImage &newImage);

    /**
     * @brief Redimension the image by using the factor
     * 
     * @param factor 
     */
    void scaleImage(double factor);

    /**
     * @brief Move the scrollBar
     * 
     * @param scrollBar 
     * @param factor 
     */
    void adjustScrollBar(QScrollBar *scrollBar, double factor);

    QImage image;
    QString currentFileName;
    QLabel *imageLabel;
    QScrollArea *scrollArea;
    double scaleFactor;

    QAction *saveAct;
    QAction *saveAsAct;
    QAction *copyAct;
    QAction *zoomInAct;
    QAction *zoomOutAct;
    QAction *normalSizeAct;
    QAction *fitToWindowAct;
};
