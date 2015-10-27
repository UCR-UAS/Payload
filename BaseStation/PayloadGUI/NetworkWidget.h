#pragma once

#include <QPushButton>
#include <QDockWidget>

class NetworkWidget : public QDockWidget{
	public:
		explicit NetworkWidget(QWidget *parent=0);
	private:
		QPushButton *startButton;
		QPushButton *stopButton;
};
