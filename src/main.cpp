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

//#include "videoprocessor.hpp"

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
    QCamera *camera;
    QMediaCaptureSession captureSession;
    QVideoWidget *videoWidget;

    void init() {
        setWindowTitle("RJCamera");

        mainMenu = this->menuBar();
        fileMenu = mainMenu->addMenu(tr("Record"));
        cameraMenu = mainMenu->addMenu(tr("Camera"));
        createMenuActions();

        camera = NULL;
        videoWidget = new QVideoWidget(this);
        setCentralWidget(videoWidget);

        statusBar()->showMessage("Status: Initialized");
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
        if (camera != NULL) {
            camera->stop();
            camera->deleteLater();
            camera = NULL;
        }

        QString basePath = "/dev/bus/usb/";
        qDebug() << "Attempting to access" << camDev.description() << "at" << basePath;        

        camera = new QCamera(camDev, this);
        captureSession.setCamera(camera);

        if (!videoWidget) {
            qWarning() << "Video widget not initialized!";
            return;
        }
        captureSession.setVideoOutput(videoWidget);

        /*QTimer::singleShot(100, this, [this]() {
            camera->start();
            setStatus("Camera started.");
        });*/

        QString status = "Accessing " + camDev.description() + "\n";
        setStatus(status);

        camera->start();
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
