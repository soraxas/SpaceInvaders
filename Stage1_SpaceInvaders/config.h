/* This class represent the config file, defines what a config file should have */

#ifndef CONFIG_H
#define CONFIG_H

#include <QTextStream>
#include <QFile>
#include <QDebug>

namespace si {

// define enum for each settings, note that the "END_OF_XXX" is to denote the end of enum, and used for cycling the settings
enum movement{LEFT, RIGHT, SHOOT};
enum size{TINY, NORMAL, LARGE, GIANT};
enum color{TRANSPARENT, RED, BLUE, GREEN, YELLOW, END_OF_COLOR};
enum spaceShipShape{A, B, C, D, END_OF_SPACESHIPSHAPE};

class config
{
public:
    config(QFile * file);
    virtual ~config();
    void loadConfig(QFile * file);
    void saveConfig();
    int m_startX;
    size m_size;
    color m_color;
    spaceShipShape m_shape;
    movement * m_movements;
    int m_numMovements;
private:
    void loadSize(QString str);
    void loadSpaceShipType(QString str);
    void loadColor(QString str);
    void loadStartX(QString str);
    void loadMovement(QStringList str);
};
}


#endif // CONFIG_H
