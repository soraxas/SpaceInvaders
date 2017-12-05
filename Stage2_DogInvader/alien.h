#ifndef ALIEN_H
#define ALIEN_H

#include <QBitmap>
#include <QObject>
#include <QPixmap>
#include <QString>
#include <QTimer>

#include <string>
#include "ship.h"
#include "bulletfactory.h"
#include "swarmcomponent.h"
#include "explosionfactory.h"

class Alien : public SwarmComponent
{
public:
    Alien(int startx, int starty, BulletFactory *bulletFactory, Ship* ship, std::string filename, int scaledToWidth);
    virtual ~Alien();

    /************* GETTERS *********************/
    virtual int getX() const;
    virtual int getY() const;
    virtual int getWidth() const;
    virtual int getHeight() const;
    virtual QPixmap getImage() const;

    /************ other ***********************/
    virtual void draw(QPainter *p) const;
    virtual void move(char m) = 0;
    virtual void shoot(int xSpeed = 0, int ySpeed = 10) = 0;
    virtual bool isComposite() const;
    virtual void nextFrame() = 0;
    void setShipPtr(Ship* ship);
    bool beenShotAt(int topLeftX, int topLeftY, int botRightX, int botRightY,
                    std::vector<Explosion> &explosions, ExplosionFactory &factory); // set itself as dead if the given point overlap itself

    virtual void setDead();
    virtual bool isDead();
    int ax; // for current level use
    int ay;
    Ship* ship; // reference to ship (for tracking)
protected:
    /************ VARIABLES ********************/
    bool dead;
    QPixmap alienImage;
    QString path; //original image path
    BulletFactory* bulletFactory;
};

#endif // ALIEN_H
