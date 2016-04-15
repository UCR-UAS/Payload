#include "CameraWidget.h"
#include <iostream>
 using namespace std;

CameraWidget::CameraWidget(QWidget *parent):
	QDockWidget(parent)
{	
	setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable); //!This sets the features of the Camera widget allowing it to be movalbe and floatable.
	
	setWindowTitle("Camera");
	setFixedSize(400,200);

	// Initialize Camera Capture Start/Stop button
	cameraButton = new QPushButton("Start/Stop Camera Capture",this);
	cameraButton->setGeometry(50,60,190,30);

	// Initialize Check camera status button. REMOVE IF NOT NEEDED
	statusButton = new QPushButton("Check Status",this);
	statusButton->setGeometry(240,60,100,30);
	
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
	QObject::connect(cameraButton, SIGNAL(clicked()), this, SLOT(setCameraCapture()));
	QObject::connect(statusButton, SIGNAL(clicked()), this, SLOT(checkStatus()));

	//Check if camera capture is currently on or off with this test packet. 
	testPacket.setCaptureBit(0); //set this function to 0 or 1 to test the button.
	cout << "Initially: " << testPacket.getCaptureBit() << endl;

}

//Event functions
void CameraWidget::setCameraCapture(){
	//If camera capture is currently off, turn it on.
	if (testPacket.getCaptureBit()==0) {
		testPacket.setCaptureBit(1); //ON
		cameraStatus->setText("On");
		cout << "Now: " << testPacket.getCaptureBit() << endl;
	}
	//If camera capture is currently on, turn it off.
	else {
		testPacket.setCaptureBit(0); //OFF
		cameraStatus->setText("Off");
		cout << "Now: " << testPacket.getCaptureBit() << endl;
	}

}

void CameraWidget::checkStatus(){
	if (testPacket.getCaptureBit()==1) {
		cameraStatus->setText("Currently on");
		cout << "Check: " << testPacket.getCaptureBit() << endl;
	}
	else {
		cameraStatus->setText("Currently off");
		cout << "Check: " << testPacket.getCaptureBit() << endl;
	}

}
