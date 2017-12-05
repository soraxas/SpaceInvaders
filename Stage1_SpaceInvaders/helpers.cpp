#include "helpers.h"

namespace si {

// initialise seed
int Helpers::randSeed = 484829581;
// return a random number in between 0 and 1
double Helpers::rand() {
    randSeed = (214013*randSeed+2531011);
    return (double)((randSeed>>16)&0x7FFF) / 32767.0;
}
// seed the random number generator
void Helpers::srand(int seed){
    Helpers::randSeed = seed;
}

// helpers method to convert enum to string
QString Helpers::enumToString(color c){
    switch(c){
    case(TRANSPARENT):
        return "TRANSPARENT";
    case(RED):
        return "RED";
    case(YELLOW):
        return "YELLOW";
    case(GREEN):
        return "GREEN";
    case(BLUE):
        return "BLUE";
    default:
        qDebug("ERROR: Unknown 'color' option");
    }
    throw;
}

QString Helpers::enumToString(movement m){
    switch(m){
    case(LEFT):
        return "L";
    case(RIGHT):
        return "R";
    case(SHOOT):
        return "S";
    }
    throw;
}
QString Helpers::enumToString(spaceShipShape s){
    switch(s){
    case(A):
        return "A";
    case(B):
        return "B";
    case(C):
        return "C";
    case(D):
        return "D";
    default:
        qDebug("ERROR: Unknown 'spaceShipType' option");
    }
    throw;
}
QString Helpers::enumToString(size s){
    switch(s){
    case(TINY):
        return "TINY";
    case(NORMAL):
        return "NORMAL";
    case(LARGE):
        return "LARGE";
    case(GIANT):
        return "GIANT";
    }
    throw;
}

}// end namespace si
