/* This Header defines the Abstract class for the builer pattern for spaceship */

#ifndef SPACESHIPBUILDER_H
#define SPACESHIPBUILDER_H

#include <QPixmap>
#include "spaceship.h"

namespace si {

class SpaceShipBuilder{
public:
    SpaceShipBuilder(){}
    virtual ~SpaceShipBuilder(){}
    virtual QPixmap * getDefenderPixmap() const = 0;
    virtual size getDefenderSize() const = 0;
    virtual color getDefenderColor() const = 0;
    virtual int getDefenderStartX() const = 0;
protected:
    QPixmap * m_spaceShipPixmap;
};

}


#endif // SPACESHIPBUILDER_H
