#include <QGraphicsView>

//! Screen : the game's screen
/*! Screen implements the QGraphicsView. At each frame, it redraws the sprites
of all GameObjects */
class fmpScreen : public QGraphicsView
{
  public :
    fmpScreen(QWidget * parent = NULL)  ;
    virtual ~fmpScreen() ;

    void update();
  protected:
    QGraphicsScene * scene; //!< The scene where objects are displayed
    int m_width;
    int m_height;
};
