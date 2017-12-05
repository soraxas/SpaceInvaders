#ifndef SPACESHIP_H
#define SPACESHIP_H

#include <QPixmap>
#include <QPainter>
#include "config.h"
#include "energyorb.h"

namespace si {

// interface for spaceship
class SpaceShip
{
public:
    SpaceShip();
    virtual ~SpaceShip();
    void setPixmap(QPixmap * pixmap);
    void setColor(color c);
    void setSize(size s);
    void draw(QPainter* p) const;

    int getX() const;
    int getY() const;
    void setX(int x);
    void setY(int y);
    int getWidth() const;
    int getHeight() const;
private:
    QPixmap * m_defender;
    size m_size;
    color m_color;
    int m_x;
    int m_y;
    energyOrb * m_orb1;
    energyOrb * m_orb2;
    energyOrb * m_orb3;
};

} // end namespace si

#endif // SPACESHIP_H
