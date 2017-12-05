#ifndef HELPERS_H
#define HELPERS_H

#include <QString>
#include "config.h"

namespace si {

class Helpers{
    // A pseudo implementation of random number generator (From intel)
public:
    static int randSeed; // seed
    static double rand(); // return a random number in between 0 and 1
    static void srand(int seed); // seed the random number generator

    // helper method to convert enum to string
    static QString enumToString(movement m);
    static QString enumToString(size s);
    static QString enumToString(color c);
    static QString enumToString(spaceShipShape s);
};

}

#endif // HELPERS_H
