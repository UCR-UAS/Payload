#pragma once

#include <QPushButton>
#include <QDockWidget>

class CameraWidget : public QDockWidget{
	public:
		explicit CameraWidget(QWidget *parent=0);
	private:
		QPushButton *startButton;
		QPushButton *stopButton;
};
