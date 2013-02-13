#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QMessageBox>

class fmpMainWindow : public QMainWindow
{
  Q_OBJECT

  public :

	  fmpMainWindow();
  public slots:
    void displayAbout();
  protected :
	  QMessageBox m_aboutBox;

};
#endif // MAINWINDOW_H
