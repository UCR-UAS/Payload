#include "ImageViewer.h"

ImageViewer::ImageViewer(QWidget *parent):
	QDockWidget(parent)
{
	setWindowTitle("Image Viewer");
	setFixedSize(800,600);

	// Initialize play button
	play = new QPushButton("Play",this);
	play->setGeometry(0,500,200,30);

	// Initialize prev Button
	prev = new QPushButton("Previous",this);
	prev->setGeometry(200,500,200,30);

	//Initialize next Button
	next = new QPushButton("Next",this);
	next->setGeometry(400,500,200,30);
	
	//Image
	image = new QLabel("Dank Memes", this);
	image->setGeometry(0, 0, 800, 500);
	image->setPixmap(QPixmap("images/1.jpg"));
	
	//ImageName;
	imgName = "images/1.jpg";
	
	//Assign button functions
	QObject::connect(next, SIGNAL(clicked()), this, SLOT(nextImg()));
	QObject::connect(prev, SIGNAL(clicked()), this, SLOT(lastImg()));
	
}
