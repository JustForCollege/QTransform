#include "mainwindow.h"
#include <QLabel>
#include <QDragEnterEvent>
#include <QColor>
#include <QMessageBox>
#include <QDropEvent>
#include <QMimeData>
#include <QVBoxLayout>
#include <QFileInfo>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget* centralWidget = new QWidget(this);

    QLabel* label = new QLabel("Drag & Drop Your Image ...");
    label->setAlignment(Qt::AlignCenter);

    QFont labelFont = label->font();
    labelFont.setPointSize(20);
    label->setFont(labelFont);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(label);
    layout->setAlignment(Qt::AlignCenter);

    centralWidget->setLayout(layout);
    this->setCentralWidget(centralWidget);
}

void MainWindow::dragEnterEvent(QDragEnterEvent* event)
{
    if(event->mimeData()->hasUrls()) {
        event->acceptProposedAction();
    }
}

void MainWindow::dropEvent(QDropEvent* event) {
    const QMimeData* mimeData = event->mimeData();

    if(mimeData->hasUrls()) {
        QList<QUrl> urls = mimeData->urls();

        for(const QUrl& url : urls) {
            if(url.isLocalFile()) {
                QString filePath = url.toLocalFile();
                QFileInfo fileInfo(filePath);

                bool isImage =
                    fileInfo.suffix().toLower() == "png"
                    || fileInfo.suffix().toLower() == "jpg"
                    || fileInfo.suffix().toLower() == "jpeg"
                    || fileInfo.suffix().toLower() == "bmp";

                if(isImage) {
                    handleDroppedFile(filePath, fileInfo);
                } else {
                    QMessageBox::warning(this, "Invalid File", "Please drop an image file (PNG, JPG, or BMP).");
                }
            }
        }
    }
}

void MainWindow::handleDroppedFile(const QString& filePath, const QFileInfo& fileInfo) {
    QImage image;
    image.load(filePath);
    image = image.convertToFormat(QImage::Format_RGB32);
    image.invertPixels();
    const auto savedFilePath = fileInfo.absolutePath() + "/" + fileInfo.baseName() + "_inverted." + fileInfo.suffix().toLower();

    if(image.save(savedFilePath)) {
        QMessageBox::information(this, "Completed !", "Saved Inverted File at: " + savedFilePath);
    } else {
        QMessageBox::warning(this, "Failure :(", "Failed To Saved File, Maybe its Write Permissions Blocking Us ?");
    }
}
