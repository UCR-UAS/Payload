#include "MainWindow.h"

MainWindow::MainWindow(QMainWindow *parent):
	QMainWindow(parent)
{	
	setMinimumSize(600,600); //!This sets the main window's size be greater than the specified size.

	// Set window properties	
	setWindowTitle("Ping Test");

	Network = new NetworkWidget(this);
	Camera = new CameraWidget(this);

	addDockWidget(Qt::DockWidgetArea (Qt::RightDockWidgetArea), Network); //!This adds the Network widget to QMainWindow, with a specified location.
	addDockWidget(Qt::DockWidgetArea (Qt::RightDockWidgetArea), Camera); //!This adds the Camera Widget to QMainWindow, with a specified location.

}
