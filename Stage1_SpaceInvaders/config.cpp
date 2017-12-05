#include "config.h"

namespace si {

config::config(QFile * file){
    loadConfig(file);
}
config::~config(){
    delete [] m_movements; // to store the set of movement/actions inside the config file
}
void config::loadConfig(QFile * file){
    QRegExp equalSign("(\\=)"); // we use equal size in the config file for each option

    // defines config keywords
    QString qs_spaceShipType = "SPACESHIPTYPE", qs_size = "SIZE", qs_startx = "STARTX", qs_color = "COLOR", qs_movement = "MOVEMENT";
    // boolean to keep track if all keywords are present within the config file
    bool opt_size = false, opt_spaceShipType = false, opt_startx = false, opt_color = false, opt_movement = false;

    // read the file
    QTextStream in(file);
    QString line = in.readLine();
    while (!line.isNull()) {
        QStringList args = line.split(equalSign);

        if (args.size() != 2){ //each option should have at least one equal sign
            qDebug("ERROR: Unknown config options in config file");
            throw;
        }
        // check if it is one of the defined keyword
        // currently if one setting was set twice, the latest will just overwrites it
        if (QString::compare(qs_spaceShipType, args[0], Qt::CaseInsensitive) == 0){
            loadSpaceShipType(args[1]);
            opt_spaceShipType = true;
        }
        else if (QString::compare(qs_size, args[0], Qt::CaseInsensitive) == 0){
            loadSize(args[1]);
            opt_size = true;
        }
        else if (QString::compare(qs_startx, args[0], Qt::CaseInsensitive) == 0){
            loadStartX(args[1]);
            opt_startx = true;
        }
        else if (QString::compare(qs_color, args[0], Qt::CaseInsensitive) == 0){
            loadColor(args[1]);
            opt_color = true;
        }
        else if (QString::compare(qs_movement, args[0], Qt::CaseInsensitive) == 0){
            line = in.readLine();
            QStringList list;
            // read all lines until end of line:
            while (!line.isNull() && line.size() > 0){
                list.append(line);
                line = in.readLine();
            }
            loadMovement(list);
            opt_movement = true;
            break; // we finished processing the file
        }
        else{ // none of the keyword were matched
            qDebug("ERROR: Unknown config options in config file");
            throw;
        }
        line = in.readLine(); //read next line
    }
    // check if all options had been set
    if (!(opt_size && opt_spaceShipType && opt_startx && opt_color && opt_movement)){
        qDebug("ERROR: Not all required options had been set in config file");
        throw;
    }
}

// helper method to match the 'SIZE' keyword within config file
void config::loadSize(QString str){
    // define key words
    QString qs_tiny = "TINY", qs_normal = "NORMAL", qs_large = "LARGE", qs_giant = "GIANT";
    if (QString::compare(qs_tiny, str, Qt::CaseInsensitive) == 0){
        m_size = TINY;
    }
    else if (QString::compare(qs_normal, str, Qt::CaseInsensitive) == 0){
        m_size = NORMAL;
    }
    else if (QString::compare(qs_large, str, Qt::CaseInsensitive) == 0){
        m_size = LARGE;
    }
    else if (QString::compare(qs_giant, str, Qt::CaseInsensitive) == 0){
        m_size = GIANT;
    }
    else{
        // raise error as none have been matched
        qDebug("ERROR: Unknown option of 'SIZE' in config file");
        throw;
    }
}
// helper method to match the 'COLOR' keyword within config file
void config::loadColor(QString str){
    // define key words
    QString qs_transparent = "TRANSPARENT", qs_red = "RED", qs_blue = "BLUE", qs_green = "GREEN", qs_yellow = "YELLOW";
    if (QString::compare(qs_transparent, str, Qt::CaseInsensitive) == 0){
        m_color = TRANSPARENT;
    }
    else if (QString::compare(qs_red, str, Qt::CaseInsensitive) == 0){
        m_color = RED;
    }
    else if (QString::compare(qs_blue, str, Qt::CaseInsensitive) == 0){
        m_color = BLUE;
    }
    else if (QString::compare(qs_green, str, Qt::CaseInsensitive) == 0){
        m_color = GREEN;
    }
    else if (QString::compare(qs_yellow, str, Qt::CaseInsensitive) == 0){
        m_color = YELLOW;
    }
    else{
        // raise error as none have been matched
        qDebug("ERROR: Unknown option of 'COLOR' in config file");
        throw;
    }
}
// helper method to match the 'STARTX' keyword within config file
void config::loadStartX(QString str){
    bool success; // denote if the given string is indeed a number
    m_startX = str.toInt(&success);
    if (!success){
        qDebug("ERROR: Non-numerical character in the option of 'StartX' in config file");
        throw;
    }
}
// helper method to match the 'SHAPE' keyword within config file
void config::loadSpaceShipType(QString str){
    // define key words
    QString qs_a = "A", qs_b = "B", qs_c = "c", qs_d = "D";
    if (QString::compare(qs_a, str, Qt::CaseInsensitive) == 0){
        m_shape = A;
    }
    else if (QString::compare(qs_b, str, Qt::CaseInsensitive) == 0){
        m_shape = B;
    }
    else if (QString::compare(qs_c, str, Qt::CaseInsensitive) == 0){
        m_shape = C;
    }
    else if (QString::compare(qs_d, str, Qt::CaseInsensitive) == 0){
        m_shape = D;
    }
    else{
        // raise error as none have been matched
        qDebug("ERROR: Unknown option of 'SPACESHIPTYPE' in config file");
        throw;
    }
}
// helper method to match the 'MOVEMENT' keyword within config file
void config::loadMovement(QStringList str){
    m_numMovements = str.size(); // get the total number of action
    m_movements = new movement[m_numMovements]; // list to store them
    // define keywords
    QString qs_left = "L", qs_right = "R", qs_shoot = "S";
    for (int i = 0; i < m_numMovements; ++i){
        if (QString::compare(qs_left, str[i], Qt::CaseInsensitive) == 0){
            m_movements[i] = LEFT;
        }
        else if (QString::compare(qs_right, str[i], Qt::CaseInsensitive) == 0){
            m_movements[i] = RIGHT;
        }
        else if (QString::compare(qs_shoot, str[i], Qt::CaseInsensitive) == 0){
            m_movements[i] = SHOOT;
        }
        else{
            // raise error as none have been matched
            qDebug("ERROR: Unknown option of 'MOVEMENT' in config file");
            throw;
        }
    }
}
} // end namespace si

