#ifndef ALIENRED_H
#define ALIENRED_H

#include "aliendecorator.h"
#include <QPixmap>
#include <QPainter>

// decorator to tint the alien to red

class AlienRed : public AlienDecorator
{
public:
    AlienRed(Alien& decorator);
    void draw(QPainter *p) const;
    virtual QPixmap getImage() const;
};

#endif // ALIENRED_H
