#include "mainwindow.h"
#include <QLabel>
#include <QDragEnterEvent>
#include <QColor>
#include <QMessageBox>
#include <QCheckBox>
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


    this->chooseInvertImage = new QCheckBox("Invert Image", this);
    this->chooseBlacknWhite = new QCheckBox("Black & White", this);
    this->chooseGrayScale   = new QCheckBox("GrayScale", this);

    layout->addWidget(chooseInvertImage);
    layout->addWidget(chooseGrayScale);
    layout->addWidget(chooseBlacknWhite);

    centralWidget->setLayout(layout);

    this->setWindowTitle("QTransform");
    this->resize(WindowWidth, WindowHeight);
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

bool MainWindow::handleImageInvert(const QString&  filePath, const QFileInfo& fileInfo)
{
    const auto savedFilePath = fileInfo.absolutePath() + "/" + fileInfo.baseName() + "_inverted." + fileInfo.suffix().toLower();

    if(!QFile::exists(savedFilePath)) {
        QImage image(filePath);
        image = image.convertToFormat(QImage::Format_RGB32);
        image.invertPixels();
        return image.save(savedFilePath);
    }

    return true;
}

bool MainWindow::handleImageGrayScale(const QString& filePath, const QFileInfo& fileInfo) {

    const auto savedFilePath = fileInfo.absolutePath() + "/" + fileInfo.baseName() + "_grayscale." + fileInfo.suffix().toLower();

    if(!QFile::exists(savedFilePath)) {
        QImage image(filePath);
        image = image.convertToFormat(QImage::Format_Grayscale8);
        return image.save(savedFilePath);
    }

    return true;
}

bool MainWindow::handleImageBlacknWhite(const QString& filePath, const QFileInfo& fileInfo) {
    const auto savedFilePath = fileInfo.absolutePath() + "/" + fileInfo.baseName() + "_blacknwhite." + fileInfo.suffix().toLower();

    if(!QFile::exists(savedFilePath)) {
        QImage image(filePath);

        constexpr int threshold = 127;

        for(int x = 0; x < image.width(); x++) {
            for(int y = 0; y < image.height(); y++) {
                QColor color = image.pixelColor(x, y);
                int grayed = qGray(color.rgb());

                if(grayed >= threshold) {
                image.setPixelColor(x, y, QColor::fromRgb(255, 255, 255));
                } else {
                image.setPixelColor(x, y, QColor::fromRgb(0, 0, 0));
                }
            }
        }

        return image.save(savedFilePath);
    }

    return true;
}

void MainWindow::handleDroppedFile(const QString& filePath, const QFileInfo& fileInfo) {

    int chosenCount = 0;
    int succeded = 0;

    if(this->chooseInvertImage->isChecked())  {
       chosenCount++;
       succeded += handleImageInvert(filePath, fileInfo);
    }

    if(this->chooseGrayScale->isChecked()) {
        chosenCount++;
        succeded += handleImageGrayScale(filePath, fileInfo);
    }

    if(this->chooseBlacknWhite->isChecked()) {
        chosenCount++;
        succeded += handleImageBlacknWhite(filePath, fileInfo);
    }

    if(chosenCount > 0) {
        if(chosenCount == succeded) {
            QMessageBox::information(this, "Success !", "All Transformations Has Completed !");
        } else {
            QMessageBox::warning(this, "Failure :(", "Failed To Save File Maybe its the Write Perms Preventing Us ?");
        }
    }
}
