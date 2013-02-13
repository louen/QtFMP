#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QMessageBox>

class fmpScreen;

class fmpMainWindow : public QMainWindow
{
  Q_OBJECT
  public :
	  fmpMainWindow();
      virtual ~fmpMainWindow();
  public slots:
    void displayAbout();
  protected :
      fmpScreen* m_screen;
	  QMessageBox* m_aboutBox;

};
#endif // MAIN_WINDOW_H
