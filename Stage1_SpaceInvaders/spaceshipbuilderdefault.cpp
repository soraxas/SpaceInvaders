#include "spaceshipbuilderdefault.h"

// SpaceShip builder that build based on config file settings.
namespace si{

SpaceShipBuilderDefault::SpaceShipBuilderDefault(config * con){
    // load the config file
    m_config = con;

    // load pixmap based on the config file
    m_spaceShipPixmap = new QPixmap;
    switch(con->m_shape){
    case(A):
        m_spaceShipPixmap->load(":/resources/defender_A.png");
        break;
    case(B):
        m_spaceShipPixmap->load(":/resources/defender_B.png");
        break;
    case(C):
        m_spaceShipPixmap->load(":/resources/defender_C.png");
        break;
    case(D):
        m_spaceShipPixmap->load(":/resources/defender_D.png");
        break;
    default:
        qDebug("ERROR: Unsupported shape");
        throw;
    }

    // resize the image
    int newWidth = m_spaceShipPixmap->width();
    switch(con->m_size){
    case(TINY):
        newWidth *= 0.5;
        break;
    case(NORMAL):
        newWidth *= 0.75;
        break;
    case(LARGE):
        newWidth *= 1.0;
        break;
    case(GIANT):
        newWidth *= 1.2;
        break;
    }
    *m_spaceShipPixmap = m_spaceShipPixmap->scaledToWidth((int)(newWidth * 1.5));

    // tint the pixmap based on the config
    QPainter p;
    QImage img(m_spaceShipPixmap->toImage());
    QImage mask(img);
    // draw the tinted color
    p.begin(&mask);
    p.setCompositionMode(QPainter::CompositionMode_SourceIn);
    switch(m_config->m_color){
    case(TRANSPARENT):
        break;
    case(RED):
        p.fillRect(0,0,mask.width(),mask.height(),Qt::red);
        break;
    case(YELLOW):
        p.fillRect(0,0,mask.width(),mask.height(),Qt::yellow);
        break;
    case(BLUE):
        p.fillRect(0,0,mask.width(),mask.height(),Qt::blue);
        break;
    case(GREEN):
        p.fillRect(0,0,mask.width(),mask.height(),Qt::green);
        break;
    default:
        qDebug("ERROR: Unsupported color");
        throw;
    }
    p.end();
    // draw the original image as overlay
    p.begin(&img);
    p.setCompositionMode(QPainter::CompositionMode_Overlay);
    p.drawImage(0,0,mask);
    p.end();
    // set the final image
    *m_spaceShipPixmap = QPixmap::fromImage(img);
}
SpaceShipBuilderDefault::~SpaceShipBuilderDefault(){
    delete m_spaceShipPixmap;
}
QPixmap * SpaceShipBuilderDefault::getDefenderPixmap() const{
    return m_spaceShipPixmap;
}
color SpaceShipBuilderDefault::getDefenderColor() const{
    return m_config->m_color;
}
size SpaceShipBuilderDefault::getDefenderSize() const{
    return m_config->m_size;
}

int SpaceShipBuilderDefault::getDefenderStartX() const{
    return m_config->m_startX;
}
}//end namespace si
