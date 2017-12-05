#ifndef RAINBOWBULLET_H
#define RAINBOWBULLET_H

#include "bullet.h"

class RainbowBullet : public Bullet
{
public:
    RainbowBullet(int xSpeed, int ySpeed, int bx, int by, int windowWidth, int windowHeight,
                std::string path,
                std::list<Bullet*> *bullets);
public slots:
    virtual void nextFrame();
protected:
  virtual bool inFrame(int y);
private:
    QRect frameWindow;
    int xSpeed;
    int ySpeed;
};

#endif // RAINBOWBULLET_H
