#include <QGraphicsView>

//! Screen : the game's screen
/*! Screen implements the QGraphicsView. At each frame, it redraws the sprites
of all GameObjects */

class Board;
class fmpScreen : public QGraphicsView
{
    Q_OBJECT
    public :
        fmpScreen(QWidget * parent = NULL)  ;
        virtual ~fmpScreen() ;

        void update(Board* board);

    public slots:
        void toggleCoords();

    signals:
        void updated();

    protected:

        void drawHex(QGraphicsScene* scene, int scale, int centerX, int centerY, QColor color);
        void drawBoard(QGraphicsScene* scene, Board* board);

    protected:
        QGraphicsScene * scene; //!< The scene where objects are displayed


        int m_width;
        int m_height;

        bool m_displayCoords;
};
