/* This Header defines the interface for the bullet class */

#ifndef BULLET_H
#define BULLET_H

#include <QPixmap>
#include <QSound>
#include <QPainter>

namespace si {

class bullet
{
public:
    bullet();
    virtual ~bullet();
    void setPixmap(QPixmap * pixmap);
    void setSound(QSound * sound);
    void setSpeed(int speed);
    void draw(QPainter* p);
    void update();
    void playSound();

    int getX();
    int getY();
    void setX(int x);
    void setY(int y);
    int getWidth();
    int getHeight();
private:
    QPixmap * m_bulletPixmap;
    QSound * m_bulletSound;
    int m_x;
    int m_y;
    int m_speed; // define the speed of bullet
};

}//end namespace si

#endif // BULLET_H
