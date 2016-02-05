#pragma once
#include <iostream>
#include <string>
#include <dirent.h>
#include <QPushButton>
#include <QDockWidget>
#include <QLabel>
#include <QPixmap>
#include <QString>
#include <QTimer>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>

class ImageViewer : public QDockWidget
{
	Q_OBJECT
	public:
		explicit ImageViewer(QWidget *parent=0);
	private:
		QPushButton* play;
		QPushButton* next;
		QPushButton* prev;
		QLabel* image;
		DIR *dirp;
		struct dirent *inFile;
		char imagePath[60];
		char nameBuffer[1000][20];
		int imageCounter;
		int curImage;
		QTimer *timer;
		bool playFlag;
	signals:

	public slots:
		//! Next img function
		void nextImg();
		//! Prev image function
		void prevImg();
		//! Play image function
		void playImg();

};
