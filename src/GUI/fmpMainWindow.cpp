#include <QMenuBar>


#include "fmpMainWindow.h"


fmpMainWindow::fmpMainWindow() 
{

  QMenuBar * menuBar = new QMenuBar();
  QMenu * gameMenu = menuBar->addMenu("Game");
  gameMenu->addAction("New Game",this,SLOT(diplayNewGame()));
  gameMenu->addSeparator();
  QMenu * helpMenu = menuBar->addMenu("Help");
  helpMenu->addAction("About fmp",this,SLOT(displayAbout()));
  setMenuBar(menuBar);

}


void fmpMainWindow::displayAbout()
{
    m_aboutBox.setWindowTitle("Qt FMP v.0.0.1");
    m_aboutBox.setInformativeText("All your base are belong to us.");
    m_aboutBox.show() ;
}
