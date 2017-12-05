#include "spaceship.h"

namespace si {
//Constructor
SpaceShip::SpaceShip(){
    // create three energy orb for animating the spaceship
    m_orb1 = new energyOrb(1, 1, true); // top right to bottom left
    m_orb2 = new energyOrb(-1, 1, false); // top left to bottom right
    m_orb3 = new energyOrb(-1, 0, true); // middle
}

SpaceShip::~SpaceShip() {
    delete m_orb1;
    delete m_orb2;
    delete m_orb3;
}

void SpaceShip::setPixmap(QPixmap * pixmap){
    this->m_defender = pixmap; // main pixmap
    // update the size to each orb
    this->m_orb1->setSize(m_defender->width(), m_defender->height());
    this->m_orb2->setSize(m_defender->width(), m_defender->height());
    this->m_orb3->setSize(m_defender->width(), m_defender->height());
}
void SpaceShip::setSize(size s){
    this->m_size = s;
}
void SpaceShip::setColor(color c){
    this->m_color = c;
}

void SpaceShip::draw(QPainter* p) const{
    // update the location of orb
    m_orb1->update(m_x, m_y);
    m_orb2->update(m_x, m_y);
    m_orb3->update(m_x, m_y);
    // first draw all orbs that are on top of the spaceship
    if(m_orb1->m_drawOnTop)
        m_orb1->draw(p);
    if(m_orb2->m_drawOnTop)
        m_orb2->draw(p);
    if(m_orb3->m_drawOnTop)
        m_orb3->draw(p);

    // draw the space ship
    p->drawPixmap(m_x, m_y, *m_defender);

    // then draw all orbs that are behind the spaceship
    if(!m_orb1->m_drawOnTop)
        m_orb1->draw(p);
    if(!m_orb2->m_drawOnTop)
        m_orb2->draw(p);
    if(!m_orb3->m_drawOnTop)
        m_orb3->draw(p);
}

int SpaceShip::getX() const{
    return m_x;
}
int SpaceShip::getY() const{
    return m_y;
}
void SpaceShip::setX(int x){
    m_x = x;
}
void SpaceShip::setY(int y){
    m_y = y;
}
int SpaceShip::getWidth() const{
    return m_defender->width();
}
int SpaceShip::getHeight() const{
    return m_defender->height();
}
} // end namespace si
