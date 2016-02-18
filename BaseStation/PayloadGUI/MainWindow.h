#pragma once

#include <QPushButton>
#include <QMainWindow>
#include <QDockWidget>
#include "NetworkWidget.h"
#include "CameraWidget.h"
#include "ImageViewer.h"
#include "../../Resources/PayloadStatus.h"


//! The main window for this application.
/*! This MainWindow class inherits from QMainWindow
    and is the primary application window in which
	all other widgets dock into. */
class MainWindow : public QMainWindow{
	
	public:
		explicit MainWindow(QMainWindow *parent=0);
		explicit MainWindow(PayloadStatus* payload_status, QMainWindow *parent = 0);
	private:
		//! The pointer to payload payload status owned by MainWindow
		PayloadStatus *MyPayloadStaus;		

		//! The widget that controlls the network.
		NetworkWidget *Network; 
		//! The widget that controlls the camera.
		CameraWidget *Camera; 
		//! The widget that controlls the viewing of images.
		ImageViewer *Viewer;
};

