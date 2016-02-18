#pragma once

#include <QPushButton>
#include <QDockWidget>
#include "../../Resources/PayloadStatus.h"

class CameraWidget : public QDockWidget{
	public:
		explicit CameraWidget(QWidget *parent=0);
                explicit CameraWidget(PayloadStatus* payload_status, QWidget *parent=0);//ADDED 1/29
	private:
                //! The poiner to payload status owned by CameraWidget
                PayloadStatus *MyPayloadStatus;         //ADDED 1/29

		QPushButton *startButton;
		QPushButton *stopButton;
};
