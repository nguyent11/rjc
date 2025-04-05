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
        // Set the window title
        setWindowTitle("");

        // Set the initial window size
        // resize(800, 600);

        // Create a menu bar
        QMenuBar *menuBar = this->menuBar();

        // Create the "File" menu. Used to record and save to file.
        QMenu *fileMenu = menuBar->addMenu("File");
	

    	// Create "Camera" menu. Used to select camera
	    QMenu *cameraMenu = menuBar->addMenu("Camera");

        createMenuActions(fileMenu, cameraMenu);

	    // Message at bottom of screen
        statusBar()->showMessage("Status: Init");

        //updateCameraMenu(cameraMenu);
    }

    void setStatus(QString statusmsg) {
        this->statusBar()->showMessage(statusmsg);
    }

    private:
    void createMenuActions(QMenu* fileMenu, QMenu* cameraMenu) {
        // File menu actions
        QAction *recordAction = new QAction(tr("&Record to File"), this);
        //recordAction->setShortcut(QKeySequence::SaveAs);
        //connect(recordAction, &QAction::triggered, this, &MainWindow::saveAs);
        fileMenu->addAction(recordAction);

        // Camera menu actions
        /*QStringList devices = {"Device_1", "Device_2", "Device_3"};
        for (int i = 0; i < devices.length(); i++) {
            QAction *cameraAction = new QAction(devices[i], this);
            cameraMenu->addAction(cameraAction);
        }*/
        updateCameraMenu(cameraMenu);        

        return;
    }
    
    void updateCameraMenu(QMenu* cameraMenu) {
        const QList<QCameraDevice> cameras = QMediaDevices::videoInputs();
        //cameraMenu->clear();        
    
        for (const QCameraDevice &camera : cameras) {
            QString name = camera.description();
            QAction *cameraAction = new QAction(name, this);

            /*connect(action, &QAction::triggered, this, [name]() {
                qDebug() << "Selected camera:" << name;
                // You can create a QCamera object with `camera` here
            });*/

            cameraMenu->addAction(cameraAction);
        }

        return;
    }
};


int main(int argc, char** argv) {
    QApplication app(argc, argv);

    //QPushButton button ("Hello world!");
    //button.show();

    MainWindow mainWindow;
    mainWindow.showMaximized();
    mainWindow.show();

   // QPushButton button("Hello world!", &mainWindow);
   // button.show();


    mainWindow.setStatus(QString("Status: Ready"));

    return app.exec();
}
