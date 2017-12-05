#ifndef ALIENHUNTING_H
#define ALIENHUNTING_H

#include "aliendecorator.h"


class AlienHunting : public AlienDecorator
{
public:
    AlienHunting(Alien& decorator);
    void move(char m);
    void resetCounter();
    QPixmap getImage() const;
private:
    unsigned shootCounter; // counter for defining when should we shoot
    unsigned shootAt; // we shoot when counter reaches this

    int delteX; // a delta x distance away from ship (so it wont bunuch up with the ship)
};

#endif // ALIENHUNTING_H
