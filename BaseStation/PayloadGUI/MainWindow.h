#pragma once

#include <QPushButton>
#include <QMainWindow>
#include <QDockWidget>
#include "NetworkWidget.h"
#include "CameraWidget.h"

class MainWindow : public QMainWindow{
	public:
		explicit MainWindow(QMainWindow *parent=0);
	private:
		NetworkWidget *Network;
		CameraWidget *Camera;
};

