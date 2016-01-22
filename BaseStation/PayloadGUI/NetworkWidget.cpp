#include "NetworkWidget.h"

NetworkWidget::NetworkWidget(QWidget *parent):
	QDockWidget(parent)
{
	setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable); //!This sets the features of the Network widget allowing it to be movalbe and floatable.

	setWindowTitle("Network");
	setFixedSize(400,200);

	// Initialize ip address input field
	ipInput = new QLineEdit(this);
	ipInput->setGeometry(50,40,200,30);

	// Initialize Connect button
	connectButton = new QPushButton("Connect",this);
	connectButton->setGeometry(50,80,100,30);

	// Initialize Disconnect button
	disconnectButton = new QPushButton("Disconnect",this);
	disconnectButton->setGeometry(150,80,100,30);


}
