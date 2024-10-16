#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileInfo>
#include <QCheckBox>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

constexpr int WindowWidth = 400;
constexpr int WindowHeight = 300;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

protected:
    void dragEnterEvent(QDragEnterEvent* event) override;
    void dropEvent(QDropEvent *event) override;

private:
    void handleDroppedFile(const QString& filePath, const QFileInfo& fileInfo);

    bool handleImageInvert(const QString& filePath, const QFileInfo& fileInfo);
    bool handleImageGrayScale(const QString& filePath, const QFileInfo& fileInfo);
    bool handleImageBlacknWhite(const QString& filePath, const QFileInfo& fileInfo);
private:
    QCheckBox *chooseInvertImage;
    QCheckBox *chooseBlacknWhite;
    QCheckBox *chooseGrayScale  ;
};
#endif // MAINWINDOW_H
