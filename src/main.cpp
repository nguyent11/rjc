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

    void init() {
        setWindowTitle("Monitor");

        mainMenu = this->menuBar();
        fileMenu = mainMenu->addMenu(tr("File"));
        cameraMenu = mainMenu->addMenu(tr("Camera"));
        createMenuActions();

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
        connect(refreshCameraAction, &QAction::triggered, this, &MainWindow::updateCameraMenu);
        cameraMenu->addAction(refreshCameraAction);

        return;
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
