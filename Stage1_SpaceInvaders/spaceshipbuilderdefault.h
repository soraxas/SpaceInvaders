/* This Header defines the Concrete class for the builer pattern for spaceship
   current this concrete class load config directly from connfig file */

#ifndef SPACESHIPBUILDERDEFAULT_H
#define SPACESHIPBUILDERDEFAULT_H

#include <QPainter>
#include "spaceshipbuilder.h"

// default builder is to use settings from config file
namespace si {
class SpaceShipBuilderDefault : public SpaceShipBuilder{
public:
    SpaceShipBuilderDefault(config * con);
    virtual ~SpaceShipBuilderDefault();
    QPixmap * getDefenderPixmap() const;
    size getDefenderSize() const;
    color getDefenderColor() const;
    int getDefenderStartX() const;
private:
    config * m_config;
};
}// end namespace si

#endif // SPACESHIPBUILDERDEFAULT_H
