#pragma once

#include "StarPacket0x01.h"
#include <iostream>
#include <string>
#include <QPushButton>
#include <QDockWidget>
#include <QLineEdit>
#include <QString>
#include <QLabel>
#include <QObject>

//! Camera Widget Class
class CameraWidget : public QDockWidget{
	Q_OBJECT
	public:
		explicit CameraWidget(QWidget *parent=0);
	private:
		QPushButton *cameraButton;
		QLineEdit   *cameraStatus;
		QLabel	    *cameraLabel;
		QPushButton *statusButton;
		QLineEdit   *imageCounter;
		QLabel      *counterLabel;

		StarPacket0x01 testPacket; //for testing purposes.

	signals:

	public slots:
		//Start or stop camera capture function
		void setCameraCapture();
		void checkStatus(); //remove if not necessary
		
};
