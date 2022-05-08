#pragma once

#include <QImage>

class ImageEditor
{
    ImageEditor() {}

public:
    /**
     * @brief Rescales the image
     *
     * @param image Image to be rescaled
     * @param factor Factor to rescale image (> 1 to enlarge) (< 1 to reduce)
     */
    static void rescale(QImage *image, double factor);

    /**
     * @brief Rotates the image
     * 
     * @param image Image to be rotated
     * @param clockwise Boolean specifying if the rotation is clockwise
     */
    static void rotate(QImage *image, bool clockwise);

    /**
     * @brief Adjust the image brightness
     * 
     * @param image Image that the brightness will be adjusted
     * @param factor Factor of adjustment
     */
    static void brightness(QImage *image, double brightnessFactor);

    /**
     * @brief Adjust the image contrast
     * 
     * @param image Image that the contrast will be adjusted
     * @param factor 
     */
    static void contrast(QImage *image, int factor);
};
