// This file contains function main() and an implementation of the MainWindow class.

#include <QApplication>
#include <QPushButton>
#include <QMainWindow>
#include <QAction>
#include <QMenuBar>
#include <QStatusBar>
#include <QVBoxLayout>
#include <QDebug>
#include <QString>
#include <QCamera>
#include <QMediaDevices>
#include <QMediaCaptureSession>
#include <QVideoWidget>
#include <QCameraDevice>
#include <QTimer>
#include <QLabel>

#include "videoprocessor.hpp"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow() {
        // Set up window, menu, status
        init();
    }

    void setStatus(QString statusmsg) {
        this->statusBar()->showMessage(statusmsg);
    }

private:
    // Private variables
    QMenuBar *mainMenu;
    QMenu *fileMenu;
    QMenu *cameraMenu;
    
    QLabel *videoDisplay;
    VideoProcessor *vidProc;

    void init() {
        setWindowTitle("RJCamera");

        mainMenu = this->menuBar();
        fileMenu = mainMenu->addMenu(tr("Record"));
        cameraMenu = mainMenu->addMenu(tr("Camera"));
        createMenuActions();

        statusBar()->showMessage("Status: Initialized");

        videoDisplay = new QLabel("Waiting for camera...");
        videoDisplay->setAlignment(Qt::AlignCenter);
        videoDisplay->setMinimumSize(640, 480);

        auto *centralWidget = new QWidget(this);
        auto *layout = new QVBoxLayout(centralWidget);
        layout->addWidget(videoDisplay);
        setCentralWidget(centralWidget);
    }

    void createMenuActions() {
        // File menu actions
        QAction *recordAction = new QAction("Record to File", this);
        //recordAction->setShortcut(QKeySequence::SaveAs);
        //connect(recordAction, &QAction::triggered, this, &MainWindow::saveAs);
        fileMenu->addAction(recordAction);

        // Camera menu actions
        updateCameraMenu();        

        return;
    }
    
    void updateCameraMenu() {
        qDebug() << "at function updateCameraMenu()\n";        

        const QList<QCameraDevice> cameras = QMediaDevices::videoInputs();
        cameraMenu->clear();                

        for (const QCameraDevice &cam : cameras) {
            QAction *cameraAction = new QAction(cam.description(), this);

            connect(cameraAction, &QAction::triggered, this, [this, cam]() {
                //qDebug() << "Selected camera:" << camera.description();
                startCamera(cam); 
            });

            cameraMenu->addAction(cameraAction);
        }

        QAction *refreshCameraAction = new QAction("Refresh Device List", this);
        connect(refreshCameraAction, &QAction::triggered, this, &MainWindow::updateCameraMenu);
        cameraMenu->addAction(refreshCameraAction);

        return;
    }

    void startCamera(const QCameraDevice &camDev) {
        qDebug() << "At startCamera() in class Mainwindow";
        
        /*if (vidProc != NULL) {
            vidProc->stop();
            delete vidProc;
            vidProc = NULL;
        }*/

        qDebug() << "Attempting to access" << camDev.description();        
        QString status = "Accessing " + camDev.description() + "\n";
        setStatus(status);

        vidProc = new VideoProcessor(camDev, this);
        connect(vidProc, &VideoProcessor::frameReady, this, [=](const QImage &img) {
            videoDisplay->setPixmap(QPixmap::fromImage(img).scaled(
            videoDisplay->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        });

        setStatus("Camera started: " + camDev.description());
    }
};

#include "main.moc"

int main(int argc, char** argv) {
    QApplication app(argc, argv);

    MainWindow mainWindow;
    mainWindow.showMaximized();
    mainWindow.show();

    return app.exec();
}
