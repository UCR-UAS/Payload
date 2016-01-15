#include "MainWindow.h"

MainWindow::MainWindow(QMainWindow *parent):
	QMainWindow(parent)
{
	// Set window properties	
	setWindowTitle("Ping Test");
	setFixedSize(600, 800);

	Network = new NetworkWidget(this);
	Camera = new CameraWidget(this);
	Viewer = new ImageViewer(this);
	//Network->move()
}
