#ifndef _NETWORK_WIDGET_H
#define _NETWORK_WIDGET_H

#include <QPushButton>
#include <QDockWidget>
#include <QLineEdit>
#include <QString>
#include "../../Resources/PayloadStatus.h"

class NetworkWidget : public QDockWidget{
	public:
		explicit NetworkWidget(QWidget *parent=0);
                explicit NetworkWidget(PayloadStatus *payload_status, QWidget * parent=0);
	private:
                //! The pointer to payload status owned by NetworkWidget
                PayloadStatus *MyPayloadStatus;         
                
		QString ipAddress;
		QLineEdit *ipInput;
		QPushButton *connectButton;
		QPushButton *disconnectButton;
};

#endif
