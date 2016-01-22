#include "MainWindow.h"

MainWindow::MainWindow(QMainWindow *parent):
	QMainWindow(parent)
{	
	// Sets the main window's size be greater than the specified size.
	setMinimumSize(600,600); 

	// Set window properties	
	setWindowTitle("PayloadGCS");

	Network = new NetworkWidget(this);
	Camera = new CameraWidget(this);
	Viewer = new ImageViewer(this);

	// Adds the Network widget to QMainWindow, with a specified location.
	addDockWidget(Qt::DockWidgetArea (Qt::RightDockWidgetArea), Network); 
	// Adds the Camera Widget to QMainWindow, with a specified location.
	addDockWidget(Qt::DockWidgetArea (Qt::RightDockWidgetArea), Camera); 

	setCentralWidget(Viewer);
}
