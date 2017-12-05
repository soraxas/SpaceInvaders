#ifndef NYANCAT_H
#define NYANCAT_H

#include "alien.h"

class NyanCat : public Alien
{
public:
    NyanCat(int startx, int starty, BulletFactory* bulletFactory, Ship* ship, std::string filename, int scaledToWidth);
    virtual ~NyanCat();
    QPixmap getImage() const;
    void move(char m);
    void shoot(int xSpeed = 0, int ySpeed = 10);

public slots:
    void nextFrame();

private:
    QPixmap * nyancatImage;
    int nyancatImageFrame;
    int nyancatImageFrameDelay;
};

#endif // NYANCAT_H
