/* This Header defines the Abstract class for the builer pattern for bullet */

#ifndef BULLETBUILDER_H
#define BULLETBUILDER_H

#include <QPixmap>
#include <QSound>

namespace si {

class BulletBuilder{
public:
    BulletBuilder(){}
    virtual ~BulletBuilder(){}
    virtual QPixmap * getBulletPixmap() const = 0;
    virtual QSound * getBulletSound() const = 0;
    virtual int getBulletSpeed() const = 0;
protected:
    QPixmap * m_bulletPixmap;
    QSound * m_bulletSound;
};

}//end namespace si

#endif // BULLETBUILDER_H
