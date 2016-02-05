#include "ImageViewer.h"

ImageViewer::ImageViewer(QWidget *parent):
	QDockWidget(parent),
	image(NULL),
	dirp(NULL),
	inFile(NULL),
	imageCounter(0),
	playFlag(false)
{
	// Initialize window atributes
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

	// Open directory and initialize first image
	dirp = opendir("images");
	do{
		inFile = readdir(dirp);
	}while(inFile->d_name[0]=='.');
	for(int i=0;i<20;++i)
		nameBuffer[imageCounter][i] = inFile->d_name[i];
	curImage = imageCounter++;
	sprintf(imagePath,"images/%s",inFile->d_name);

	// Initialize play timer 
	timer = new QTimer(this);
	QObject::connect(timer, SIGNAL(timeout()), this, SLOT(nextImg()));

	// Image
	image = new QLabel("Dank Memes", this);
	image->setGeometry(0, 0, 800, 500);
	image->setPixmap(QPixmap(imagePath));
	
	// Assign button functions
	QObject::connect(next, SIGNAL(clicked()), this, SLOT(nextImg()));
	QObject::connect(prev, SIGNAL(clicked()), this, SLOT(prevImg()));
	QObject::connect(play, SIGNAL(clicked()), this, SLOT(playImg()));
}

void ImageViewer::nextImg(){
	// If the current image is at the head of the dir pointer
	if(curImage == imageCounter-1){
		// Get file
		inFile = readdir(dirp);
		if(inFile == NULL) return;	
		// Coppy name over
		for(int i=0;i<20;++i)
			nameBuffer[imageCounter][i] = inFile->d_name[i];
		// Incriment counters
		curImage = imageCounter++;
		sprintf(imagePath,"images/%s",inFile->d_name);
		// Display image
		image->setPixmap(QPixmap(imagePath));
	}
	else{ // Else use the image name in the buffer
		sprintf(imagePath,"images/%s",nameBuffer[++curImage]);
		image->setPixmap(QPixmap(imagePath));
	}
}

void ImageViewer::prevImg(){
	if(curImage == 0) return;
		sprintf(imagePath,"images/%s",nameBuffer[--curImage]);
		image->setPixmap(QPixmap(imagePath));
}

void ImageViewer::playImg(){
	if(playFlag == false){
		timer->start(5000); //time specified in ms
		playFlag = true;
	}
	if(playFlag == true){
		timer->stop();
		playFlag = false;
	}
}
