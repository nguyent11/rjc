// GUI includes
#include <QApplication>
#include <QPushButton>
#include <QMainWindow>
#include <QAction>
#include <QMenuBar>
#include <QStatusBar>

// Processing includes
#include <usb.h>
#include <stdio.h>
#include <vector>

class MainWindow : public QMainWindow {
    public:
    MainWindow() {
        // Set the window title
        setWindowTitle("");

        // Set the initial window size
        resize(800, 600);

        // Create a central widget (optional, can use for main content)
        //QPushButton *button = new QPushButton("Hello, World!", this);
        //setCentralWidget(button);

        // Create a menu bar
        QMenuBar *menuBar = this->menuBar();

        // Create the "File" menu and add actions
        QMenu *fileMenu = menuBar->addMenu("File");

        statusBar()->showMessage("Ready");

        // Create the list of usb devices for the user to select from
        std::vector<std::string> deviceList = grabUsbDevices();
        std::vector<QPushButton> deviceButtonList;
        for (int i = 0; i < deviceList.size(); i++) {
            deviceButtonList.push_back(QPushButton("deviceList[i]", this));
            
        }
    }

    private:
    std::vector<std::string> grabUsbDevices() {
        std::vector<std::string> deviceList;

        deviceList.push_back("?");

        return deviceList;
    }
};


int main(int argc, char** argv) {
    QApplication app(argc, argv);

    //QPushButton button ("Hello world!");
    //button.show();

    MainWindow mainWindow;
    mainWindow.show();

   // QPushButton button("Hello world!", &mainWindow);
   // button.show();

    return app.exec();
}
