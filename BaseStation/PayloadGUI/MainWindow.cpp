#include "MainWindow.h"

MainWindow::MainWindow(QMainWindow *parent):
	QMainWindow(parent)
{
	// Set window properties	
	setWindowTitle("Ping Test");
	setFixedSize(600, 600);

	Network = new NetworkWidget(this);
	Camera = new CameraWidget(this);
}
