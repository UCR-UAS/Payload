#pragma once

#include <iostream>
#include <string>
#include <QPushButton>
#include <QDockWidget>
#include <QLineEdit>
#include <QString>
#include <QLabel>


class CameraWidget : public QDockWidget{
	public:
		explicit CameraWidget(QWidget *parent=0);
	private:
		QPushButton *cameraButton;
		QLineEdit   *cameraStatus;
		QLabel	    *cameraLabel;
		QLineEdit   *imageCounter;
		QLabel      *counterLabel;

	signals:

	public slots:
		//Start camera capture function
		/*
		void startCamera() {
			if( ) {
			
			}
		}
		//Stop camera capture function
		void stopCamera() {
			if( ) {
			
			}	
		}
		*/
};
