// GUI includes
#include <QApplication>
#include <QPushButton>
#include <QMainWindow>
#include <QAction>
#include <QMenuBar>
#include <QStatusBar>
#include <QVector>
#include <QString>
#include <QVBoxLayout>
#include <QDebug>

// Processing includes
#include <usb.h>

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
        QWidget *centralWidget = new QWidget(this);
        // Create a menu bar
        QMenuBar *menuBar = this->menuBar();

        // Create the "File" menu and add actions
        QMenu *fileMenu = menuBar->addMenu("File");

        statusBar()->showMessage("Ready");

        // Create the list of usb devices for the user to select from
        QVBoxLayout *layout = new QVBoxLayout(centralWidget);
        QVector<QPushButton*> buttonVector;
        QStringList usbDevices = {"Device_1", "Device_2", "Device_3"};
        for (const QString &device : usbDevices) {
            QPushButton *button = new QPushButton(device, this);
            // Connect button clicked signal to a lambda or slot
            connect(button, &QPushButton::clicked, [this, device]() {
                qDebug() << "Button for " << device << " clicked.";
            });
            buttonVector.append(button);
        }
        // Add buttons from vector to layout
        for (QPushButton *button : buttonVector) {
            layout->addWidget(button);
        }

    
        centralWidget->setLayout(layout);
        setCentralWidget(centralWidget);
        
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
