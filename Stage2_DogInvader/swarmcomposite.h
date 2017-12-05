#ifndef SWARMCOMPOSITE_H
#define SWARMCOMPOSITE_H

#include <vector>

#include "swarmcomponent.h"

class SwarmComposite : public SwarmComponent
{
public:
    SwarmComposite();
    virtual ~SwarmComposite();
    void move(char m);
    void draw(QPainter *p) const;
    void add(SwarmComponent *c);
    int getWidth() const;
    int getHeight() const;
    bool isComposite() const;
    virtual void nextFrame();
    void setShipPtr(Ship* ship);
    bool beenShotAt(int topLeftX, int topLeftY, int botRightX, int botRightY,
                    std::vector<Explosion> &explosions, ExplosionFactory &factory);
    std::vector<SwarmComponent*> aliens;
};

#endif // SWARMCOMPOSITE_H
