#ifndef ALIENDECORATOR_H
#define ALIENDECORATOR_H

#include "alien.h"

class AlienDecorator : public Alien
{
public:
    AlienDecorator(Alien& decorator);
    ~AlienDecorator();

    virtual int getX() const;
    virtual int getY() const;
    virtual int getWidth() const;
    virtual int getHeight() const;
    virtual QPixmap getImage() const;

    /************ other ***********************/
    virtual void draw(QPainter *p) const;
    virtual void move(char m);
    virtual void shoot(int xSpeed = 0, int ySpeed = 10);
    virtual bool isComposite() const;
    virtual void nextFrame();
    virtual void setShipPtr(Ship* ship);
    virtual bool beenShotAt(int topLeftX, int topLeftY, int botRightX, int botRightY,
                            std::vector<Explosion> &explosions, ExplosionFactory &factory);
    virtual void setDead();
    virtual bool isDead();

protected:
    Alien& decorator;
};







#endif // ALIENDECORATOR_H
