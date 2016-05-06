#ifndef _MAIN_WINDOW_H
#define _MAIN_WINDOW_H

#include "Network.h"
#include <QPushButton>
#include <QMainWindow>
#include <QDockWidget>
#include "NetworkWidget.h"
#include "CameraWidget.h"
#include "ImageViewer.h"


//! The main window for this application.
/*! This MainWindow class inherits from QMainWindow
    and is the primary application window in which
	all other widgets dock into. */
class MainWindow : public QMainWindow{
	
	public:
		explicit MainWindow(QMainWindow *parent=0);
		Network* getNetwork(){return &netPtr;}
	private:
		//! The widget that controlls the network.
		NetworkWidget *NetworkW; 
		//! The widget that controlls the camera.
		CameraWidget *Camera; 
		//! The widget that controlls the viewing of images.
		ImageViewer *Viewer;
		//!
		Network netPtr;
};

#endif
