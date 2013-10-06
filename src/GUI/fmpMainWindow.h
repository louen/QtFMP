#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QDebug>

class fmpScreen;
class Board;

class fmpMainWindow : public QMainWindow
{
  Q_OBJECT
  public :
      fmpMainWindow();
      virtual ~fmpMainWindow();

      

  public slots:
    void displayAbout();
    void update();
  protected :
      fmpScreen* m_screen;
      QMessageBox* m_aboutBox;
      Board* m_board;

};


class fmpDebugOutput
{
    public:
        static fmpDebugOutput& getInstance()
        {
            if (s_instance == nullptr)
            {
                s_instance = new fmpDebugOutput;
            }	
            return  *s_instance;
        }

        void printf(char* format, ...)
        {
            QString string;
            va_list argp;
            va_start(argp, format);
            string.vsprintf( format, argp);
            va_end(argp);
            qDebug()<< string;
        }

        void print(char* debugStr)
        {
            qDebug() << debugStr ;
        }
    private:
        static fmpDebugOutput * s_instance;

};
#endif // MAIN_WINDOW_H
