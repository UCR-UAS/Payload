#pragma once
#include <iostream>
#include <string>
#include <dirent.h>
#include <QPushButton>
#include <QDockWidget>
#include <QLabel>
#include <QPixmap>
#include <QString>
#include "../../Resources/PayloadStatus.h"

class ImageViewer : public QDockWidget
{
	Q_OBJECT
	public:
		explicit ImageViewer(QWidget *parent=0);
                explicit ImageViewer(PayloadStatus* payload_status, QWuidget *parent=0;)
	private:
                PayloadStatus *MyPayloadStatus;

		QPushButton* play;
		QPushButton* next;
		QPushButton* prev;
		QLabel* image;
		QString imgName;

	signals:

	public slots:
		//next img function
		void nextImg() {
			if(imgName[7].unicode() == '3') {
				imgName.replace("3", "1");
			}
			else {
				imgName[7].unicode()++;
				image->setPixmap(imgName);
			}
		}
		//prev image function
		void lastImg() {
			if(imgName[7].unicode() == '1') {
				imgName.replace("1", "3");
			}
			else {
				imgName[7].unicode()--;
				image->setPixmap(imgName);
			}
		}
		//play image function
		void playImg() {
			if(imgName[7].unicode() == '1') {
				imgName.replace("1", "3");
			}
			else {
				imgName[7].unicode()++;
				image->setPixmap(imgName);
			}
		}

};
