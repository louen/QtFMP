#include <GUI/fmpScreen.h>

#include <game/fmp.h>

#include <QPen>
#include <QGraphicsItem>

fmpScreen::fmpScreen (QWidget * parent ) :
QGraphicsView (parent)
{
    scene = new QGraphicsScene(this) ;
    m_width = 1200;
    m_height = 1000;
    m_displayCoords = false;
}

fmpScreen::~fmpScreen()
{
    delete scene ;
}


    // sin pi/3
    static const float sinangle = 0.8660254f;

    static const float vertices[6][2] =
    {
        { 0.5f,	  sinangle  },
        { 1.f,	  0.f },
        { 0.5f,	-sinangle },
        { -0.5f,-sinangle  },
        { -1.f,		0.f },
        { -0.5f, sinangle } 
    };


void fmpScreen::drawHex(QGraphicsScene* scene, int scale, int centerX, int centerY, QColor color)
{
    
    QPen hexaPen(Qt::black);
    QBrush hexaBrush(color);
    QPolygon hexagon;
    for (int i = 0 ; i < 6 ; ++i)
    {

        int x0 = int (vertices[i][0] * float(scale)) + centerX;
        int y0 = int (vertices[i][1] * float(scale)) + centerY;
        hexagon.append(QPoint(x0,y0));

        /*int x1 = int (vertices[(i+1)%6][0] * float(scale)) + centerX;
        int y1 = int (vertices[(i+1)%6][1] * float(scale)) + centerY;

        scene->addLine(x0, y0, x1, y1, hexaPen);*/
        scene->addPolygon(hexagon,hexaPen,hexaBrush);


        
    }
}

const int SCALE = 20;
const int STARTX  = 40;
const int STARTY = 40;

void fmpScreen::drawBoard(QGraphicsScene* scene, Board* board)
{
    int strideX = int (1.5f * float(SCALE));
    int strideY = int (sinangle * float(SCALE));
    for (int i =0 ; i < board->getNumHexs() ; ++i)
    {
        int line = board->getHex(i).m_line;
        int col = board->getHex(i).m_column;
        
        int x = STARTX + (strideX * col);
        int y = STARTY + (strideY * line);

     

        QColor color = Qt::red;
        const Hexagon& hex = board->getHex(i);
        switch(hex.getType())
        {
            case Hexagon::GROUND:
                color = QColor(190,140,100); 
                break;
            case Hexagon::MOUNTAIN:
                color = QColor(42,42,42);
                break;
            case Hexagon::SWAMP:
                color = QColor(137,162,100);
                break;
            case Hexagon::REEF:
                color = Qt::darkCyan;
                break;
            case Hexagon::WATER:
                color = QColor(80,80,110);
                break;	
        }
        drawHex(scene, SCALE, x,y, color);
        if (m_displayCoords)
        {
            QPen pen;
            pen.setColor(Qt::red);
            QString str;
            str.sprintf("%i %i", hex.m_line, hex.m_column);
            QGraphicsSimpleTextItem*  text = scene->addSimpleText(str);
            QPoint textpos(x - SCALE/2,y-SCALE/2);

            text->setPos(textpos);


        }

        //scene->addRect(x-(strideX/3),y-strideY,SCALE, 2* strideY, pen, brush);
    }
}

void fmpScreen::toggleCoords()
{
    m_displayCoords = ! m_displayCoords;
    emit (updated());
}

void fmpScreen::update(Board* board)
{
    QPen pen;
    QBrush bgBrush(Qt::black);


    scene->clear();
    // sets black background
    scene->setSceneRect(0,0,m_width,m_height);
    scene->addRect(0,0,m_width,m_height,pen,bgBrush);


    drawBoard(scene, board);

    setScene(scene);
}
