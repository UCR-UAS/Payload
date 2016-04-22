#ifndef _NETWORK_WIDGET_H
#define _NETWORK_WIDGET_H

#include <QPushButton>
#include <QDockWidget>
#include <QLineEdit>
#include <QString>
#include <QLabel>

class NetworkWidget : public QDockWidget{
	public:
		explicit NetworkWidget(QWidget *parent=0);
	private:
		QString ipAddress;
		QLineEdit *ipInput;
		QLineEdit *portInput;
		QLabel *ipLabel;
		QLabel *portLabel;
		QPushButton *connectButton;
		QPushButton *disconnectButton;

	signals:

	public slots:
		//Connect function
		void setConnect();
		//Disconnect function
		void setDisconnect();
};

#endif
