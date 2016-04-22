#include "NetworkWidget.h"

NetworkWidget::NetworkWidget(QWidget *parent):
	QDockWidget(parent)
{
	setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable); //!This sets the features of the Network widget allowing it to be movalbe and floatable.

	setWindowTitle("Network");
	setFixedSize(400,200);

	// Initialize ip address input field
	ipInput = new QLineEdit(this);
	ipInput->setGeometry(50,40,100,30);
	
	// Initialize port input field
	portInput = new QLineEdit(this);
	portInput->setGeometry(50,70,100,30);

	// Initialize Connect button
	connectButton = new QPushButton("Connect",this);
	connectButton->setGeometry(50,100,100,30);

	// Initialize Disconnect button
	disconnectButton = new QPushButton("Disconnect",this);
	disconnectButton->setGeometry(150,80,100,30);

	//Assign button functions
	QObject::connect(connectButton, SIGNAL(clicked()), this, SLOT(setConnect()));
	QObject::connect(disconnectButton, SIGNAL(clicked()), this, SLOT(setDisconnect()));

}

//Event functions
// NOTE: Need network api for network functions!
void NetworkWidget::setConnect(){


}

void NetworkWidget::setDisconnect(){


}
