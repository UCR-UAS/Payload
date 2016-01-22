#ifndef _NETWORK_WIDGET_H
#define _NETWORK_WIDGET_H

#include <QPushButton>
#include <QDockWidget>
#include <QLineEdit>
#include <QString>

class NetworkWidget : public QDockWidget{
	public:
		explicit NetworkWidget(QWidget *parent=0);
	private:
		QString ipAddress;
		QLineEdit *ipInput;
		QPushButton *connectButton;
		QPushButton *disconnectButton;
};

#endif
