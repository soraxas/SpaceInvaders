#ifndef SWARMCOMPONENT_H
#define SWARMCOMPONENT_H

#include <QPainter>
#include "ship.h"
#include "explosionfactory.h"

/* Define the Composite Design pattern for component, in particular for component and swarms */
class SwarmComponent{
public:
    virtual ~SwarmComponent(){}
    virtual void move(char m) = 0;
    virtual void draw(QPainter *p) const = 0;
    virtual int getWidth() const = 0;
    virtual int getHeight() const = 0;
    virtual bool isComposite() const = 0;
    virtual void nextFrame() = 0;
    virtual void setShipPtr(Ship* ship) = 0;
    virtual bool beenShotAt(int topLeftX, int topLeftY, int botRightX, int botRightY,
                            std::vector<Explosion> &explosions, ExplosionFactory &factory) = 0;
};

#endif // SWARMCOMPONENT_H
