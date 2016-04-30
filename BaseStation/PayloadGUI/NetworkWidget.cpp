#include "NetworkWidget.h"
#include <iostream>
 using namespace std;

NetworkWidget::NetworkWidget(QWidget *parent):
	QDockWidget(parent)
{
	setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable); //!This sets the features of the Network widget allowing it to be movalbe and floatable...

	setWindowTitle("Network");
	setFixedSize(400,200);
	
	// Initialize ip address input label
	ipLabel = new QLabel("IP Address: ",this);
	ipLabel->setGeometry(50, 40, 100,30);

	// Initialize ip address input field
	ipInput = new QLineEdit(this);
	ipInput->setGeometry(160,40,150,30);
	
	// Initialize port input label
	portLabel = new QLabel("Port: ",this);
	portLabel->setGeometry(50, 80, 100,30);

	// Initialize port input field
	portInput = new QLineEdit(this);
	portInput->setGeometry(160,80,100,30);

	// Initialize network status label
	networkLabel = new QLabel("Network Status: ",this);
	networkLabel->setGeometry(50, 120, 100,30);

	//Initialize network status display box
	networkStatus = new QLineEdit(this);
	networkStatus->setGeometry(160,120,100,30);
	networkStatus->setReadOnly(true);

	// Initialize network status button
	networkButton = new QPushButton("Check Status",this);
	networkButton->setGeometry(270,160,100,30);
	
	// Initialize Connect button
	connectButton = new QPushButton("Connect",this);
	connectButton->setGeometry(50,160,100,30);

	// Initialize Disconnect button
	disconnectButton = new QPushButton("Disconnect",this);
	disconnectButton->setGeometry(160,160,100,30);

	//Assign button functions
	QObject::connect(connectButton, SIGNAL(clicked()), this, SLOT(setConnect()));
	QObject::connect(disconnectButton, SIGNAL(clicked()), this, SLOT(setDisconnect()));
	QObject::connect(networkButton, SIGNAL(clicked()), this, SLOT(checkNetwork()));

	testPacket.setNetworkBit(0); //set this function to 0 or 1 to test the button.

}

//Event functions
// NOTE: Need network api for network functions!
void NetworkWidget::setConnect(){
	QString ipString = ipInput->text();
	QString portString = portInput->text();
	string temp = portString.toStdString();

	net = new Network(ipString.toStdString(), atoi( temp.c_str() ), 0);
}

void NetworkWidget::setDisconnect(){


}

void NetworkWidget::checkNetwork(){
	if (testPacket.getNetworkBit()==1) {
		networkStatus->setText("Connected");
		//cout << "Check: " << testPacket.getNetworkBit() << endl;
	}
	else {
		networkStatus->setText("Disconnected");
		//cout << "Check: " << testPacket.getNetworkBit() << endl;
	}

}


