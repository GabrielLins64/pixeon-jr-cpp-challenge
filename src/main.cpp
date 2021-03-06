#include <QApplication>
#include <QCommandLineParser>

#include "imageviewer.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QGuiApplication::setApplicationDisplayName(ImageViewer::tr("Pixeon Image Viewer"));

    ImageViewer imageViewer;

    imageViewer.show();
    return app.exec();
}
