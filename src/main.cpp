#include <QApplication.h>

#include "fmpMainWindow.h"

int main( int argc, char** argv) 
{
    QApplication myApp(argc,argv);
    myApp.setApplicationName("Qt FMP v 0.0.1");

    fmpMainWindow mainWindow;
	mainWindow.show();
    
    return myApp.exec();
}
