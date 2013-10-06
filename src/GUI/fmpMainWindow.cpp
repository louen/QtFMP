#include <GUI/fmpMainWindow.h>
#include <GUI/fmpScreen.h>

#include <game/fmp.h>

fmpDebugOutput * fmpDebugOutput::s_instance = nullptr;

#include <QMenuBar>

fmpMainWindow::fmpMainWindow() 
{
    m_screen = new fmpScreen(this);
    m_aboutBox = new QMessageBox(this);
    connect(m_screen,SIGNAL(updated()), this, SLOT(update()));

    QMenuBar * menuBar = new QMenuBar();
    QMenu * gameMenu = menuBar->addMenu("Game");
 //   gameMenu->addAction("New Game",this,SLOT(diplayNewGame()));
 //   gameMenu->addSeparator();
    QMenu * helpMenu = menuBar->addMenu("Help");
    QMenu * debugMenu = menuBar->addMenu("Debug");
    debugMenu->addAction("Display coordinates", m_screen, SLOT(toggleCoords()));

    helpMenu->addAction("About fmp",this,SLOT(displayAbout()));
    setMenuBar(menuBar);

    m_board = new Board("map_basic.txt");

    setCentralWidget(m_screen);
    m_screen->update(m_board);
}

void fmpMainWindow::update()
{
    m_screen->update(m_board);
    fmpDebugOutput::getInstance().print("a");
}

fmpMainWindow::~fmpMainWindow()
{
    delete m_aboutBox;
    delete m_screen;
    delete m_board;
}

void fmpMainWindow::displayAbout()
{
    m_aboutBox->setWindowTitle("Qt FMP v.0.0.1");
    m_aboutBox->setInformativeText("All your base are belong to us.");
    m_aboutBox->show() ;
}
