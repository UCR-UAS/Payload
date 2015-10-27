
#include <QApplication>
#include "MainWindow.h"

int main(int argc, char *argv[ ]){
	QApplication app(argc, argv);
	
	// Show window
	MainWindow window;
	window.show();
	return app.exec();
}
