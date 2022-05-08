#pragma once

#include <QMainWindow>
#include <QtWidgets>
#include <QScrollBar>
#include <QLabel>
#include <QScrollArea>
#include <QPrinter>
#include <map>

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

protected slots:
    /**
     * @brief When a image on the images list is clicked
     * 
     * @param clickedItem 
     */
    void onImagesListItemClicked(QListWidgetItem *clickedItem);

private slots:

    /**
     * @brief Open an image
     * 
     */
    void open();

    /**
     * @brief Close the current viewing image
     * 
     */
    void close();

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

    /**
     * @brief Rotates the image clockwise
     * 
     */
    void rotateClockwise();

    /**
     * @brief Rotates the image counterclockwise
     * 
     */
    void rotateCounterClockwise();

    /**
     * @brief Rescales the image
     * 
     */
    void rescaleImage();

    /**
     * @brief When the brightness slider is triggered
     * 
     */
    void onAdjustImageBrightness();

    /**
     * @brief Adjusts the brightness of the image
     * 
     * @param brightnessFactor 
     */
    void adjustImageBrightness(int brightnessFactor);

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

    /**
     * @brief Renders the work area (images list and image viewer)
     * 
     */
    void renderWorkArea();

    /**
     * @brief Updates the current image in the UI and private data structures
     * 
     * @param image The new image pointer
     */
    void updateCurrentImage(QImage *image);

    QImage *image;
    QListWidget *imagesList;
    std::map<QString, QImage> images;
    std::map<QString, QString> imagesPath;
    QString currentFileName;
    QLabel *imageLabel;
    QScrollArea *scrollArea;
    double scaleFactor;

    // File handling actions
    QAction *saveAct;
    QAction *saveAsAct;
    QAction *closeAct;

    // View actions
    QAction *zoomInAct;
    QAction *zoomOutAct;
    QAction *normalSizeAct;
    QAction *fitToWindowAct;

    // Edit Actions
    QAction *copyAct;
    QAction *rotateClockwiseAct;
    QAction *rotateCounterClockwiseAct;
    QAction *rescaleImageAct;
    QAction *adjustImageBrightnessAct;
};
