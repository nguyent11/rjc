// GUI includes
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

// Processing includes

class MainWindow : public QMainWindow {
    public:
    MainWindow() {
        // Set up window, menu, status
        init();
    }

    void setStatus(QString statusmsg) {
        this->statusBar()->showMessage(statusmsg);
    }

    private:
    void init() {
        setWindowTitle("Monitor");

        QMenuBar *menuBar = this->menuBar();
        QMenu *fileMenu = menuBar->addMenu(tr("File"));
        QMenu *cameraMenu = menuBar->addMenu(tr("Camera"));
        createMenuActions(fileMenu, cameraMenu);

        statusBar()->showMessage(tr("Status: Initialized"));
    }

    void createMenuActions(QMenu* fileMenu, QMenu* cameraMenu) {
        // File menu actions
        QAction *recordAction = new QAction("Record to File", this);
        //recordAction->setShortcut(QKeySequence::SaveAs);
        //connect(recordAction, &QAction::triggered, this, &MainWindow::saveAs);
        fileMenu->addAction(recordAction);

        // Camera menu actions
        updateCameraMenu(cameraMenu);        

        return;
    }
    
    void updateCameraMenu(QMenu* cameraMenu) {
        const QList<QCameraDevice> cameras = QMediaDevices::videoInputs();
        cameraMenu->clear();        
    
        for (const QCameraDevice &camera : cameras) {
            QString name = camera.description();
            QAction *cameraAction = new QAction(name, this);

            /*connect(action, &QAction::triggered, this, [name]() {
                qDebug() << "Selected camera:" << name;
                // You can create a QCamera object with `camera` here
            });*/

            cameraMenu->addAction(cameraAction);
        }

        QAction *refreshCameraAction = new QAction("Refresh Device List", this);
        cameraMenu->addAction(refreshCameraAction);

        return;
    }
};


int main(int argc, char** argv) {
    QApplication app(argc, argv);

    MainWindow mainWindow;
    mainWindow.showMaximized();
    mainWindow.show();

    return app.exec();
}
