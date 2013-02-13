#include <GUI/fmpMainWindow.h>
#include <GUI/fmpScreen.h>

#include <QMenuBar>
fmpMainWindow::fmpMainWindow() 
{
    m_screen = new fmpScreen(this);
    m_aboutBox = new QMessageBox(this);


    QMenuBar * menuBar = new QMenuBar();
    QMenu * gameMenu = menuBar->addMenu("Game");
    gameMenu->addAction("New Game",this,SLOT(diplayNewGame()));
    gameMenu->addSeparator();
    QMenu * helpMenu = menuBar->addMenu("Help");
    helpMenu->addAction("About fmp",this,SLOT(displayAbout()));
    setMenuBar(menuBar);

    setCentralWidget(m_screen);
    m_screen->update();
}

fmpMainWindow::~fmpMainWindow()
{
    delete m_aboutBox;
    delete m_screen;
}

void fmpMainWindow::displayAbout()
{
    m_aboutBox->setWindowTitle("Qt FMP v.0.0.1");
    m_aboutBox->setInformativeText("All your base are belong to us.");
    m_aboutBox->show() ;
}
