#include <GUI/fmpScreen.h>

#include <QPen>
#include <QGraphicsItem>

fmpScreen::fmpScreen (QWidget * parent ) :
QGraphicsView (parent)
{
    scene = new QGraphicsScene(this) ;
    m_width = 300;
    m_height = 300;
}

fmpScreen::~fmpScreen()
{
    delete scene ;
}

void fmpScreen::update()
{
    QPen pen;
    QBrush bgBrush(Qt::black);
    scene->clear();
    // sets black background
    scene->setSceneRect(0,0,m_width,m_height);
    scene->addRect(0,0,m_width,m_height,pen,bgBrush);

    setScene(scene);
}
