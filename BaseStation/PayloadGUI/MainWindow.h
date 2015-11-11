#pragma once

#include <QPushButton>
#include <QMainWindow>
#include <QDockWidget>
#include "NetworkWidget.h"
#include "CameraWidget.h"

//! The main window for this application.
/*! This MainWindow class inherits from QMainWindow
    and is the primary application window in which
	all other widgets dock into. */
class MainWindow : public QMainWindow{
	public:
		explicit MainWindow(QMainWindow *parent=0);
	private:
		NetworkWidget *Network; //!< The widget that controlls the network.
		CameraWidget *Camera; //!< The widget that controlls the camera.
};

