#include "CameraWidget.h"

CameraWidget::CameraWidget(QWidget *parent):
	QDockWidget(parent)
{	
	setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable); //!This sets the features of the Camera widget allowing it to be movalbe and floatable.
	
	setWindowTitle("Camera");
	setFixedSize(400,200);

	// Initialize Camera Capture Start/Stop button
	cameraButton = new QPushButton("Start/Stop Camera Capture",this);
	cameraButton->setGeometry(50,60,250,30);
	
	//Initialize Camera status label
	cameraLabel = new QLabel("Camera Status:",this);
	cameraLabel->setGeometry(50, 100, 100, 30);
	
	//Initialize Camera status display box
	cameraStatus = new QLineEdit(this);
	cameraStatus->setGeometry(160,100,100,30);
	cameraStatus->setReadOnly(true);

	//Initialize Image counter label
	counterLabel = new QLabel("Image Counter:",this);
	counterLabel->setGeometry(50,140,100,30);

	//Initialize Image counter display box
	imageCounter = new QLineEdit(this);
	imageCounter->setGeometry(160,140,100,30);
	imageCounter->setReadOnly(true);

	//Assign button functions
	/*
	QObject::connect(startCamera, SIGNAL(clicked()), this, SLOT(nextImg()));
	QObject::connect(stopCamera, SIGNAL(clicked()), this, SLOT(lastImg()));	
	*/
}
