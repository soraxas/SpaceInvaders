/* This Header defines the Concrete class for the builer pattern for bullet
   current this concrete class load config directly from connfig file */

#ifndef BULLETBUILDERDEFAULT_H
#define BULLETBUILDERDEFAULT_H

#include "bulletbuilder.h"
#include "config.h"

namespace si {

class BulletBuilderDefault : public BulletBuilder
{
public:
    BulletBuilderDefault();
    virtual ~BulletBuilderDefault();
    QPixmap * getBulletPixmap() const;
    QSound * getBulletSound() const;
    int getBulletSpeed() const;
};

}
#endif // BULLETBUILDERDEFAULT_H
