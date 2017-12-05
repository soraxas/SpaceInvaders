#include "configreader.h"

#include <iostream>

ConfigReader::ConfigReader() :
    // initialise default settings
    colors{"Red", "Orange", "Yellow", "Green", "Blue"},
    defaultKeys{"color", "size", "move", "coord"},
    defaultValues{"Red", "Large", "LSLSLSLSRSRSRSRSRSRRLLLS", "400"},
    defaultAliens{"7x3 x=250 y=65 __LLL__SRRRS",
                    "1 x=210 y=145 UUDLLLL_____S_____S_________SRRRRRRRRLS____H__DSDDUU_S",
                    "1x1 x=225 y=315 ___ULDRS",
                    "3x2 x=455 y=245 DDUDUUS__UUDDRRRRRR___SLLLLLL",
                    "2x2 x=90 y=100 ______H",
                    "1x3 x=650 y=70 ___LLLL___RRRR____H"}
{}

ConfigReader::~ConfigReader() {
    // NOTE: We must save the new map first!
    writeFile();
}

// constructor, loads file / makes default file
void ConfigReader::setup(QString fileName, QString filePath,
                         std::vector<std::tuple<SwarmComponent *, std::string, unsigned>> &aliens,
                         AlienFactory &alienFactory) {
    aliensConfig.clear();
    path = QString::fromStdString(filePath.toStdString() + fileName.toStdString());
    QFile config(path);

    // test if it actually exists, if not make a default config.
    if (!config.exists()) {
        createDefault();
    }
    config.open(QIODevice::ReadOnly | QIODevice::Text);
    // keep track which section of config are we in
    ConfigSection section = SpaceShip; // default
    // until EOF, read the next lines, put in Map.
    while (!config.atEnd()) {
        std::string str(config.readLine().constData());
        if (str.empty())
            continue;
        // try to see what section it is, length = 1 including the new line character
        if (std::abs(str.compare("[SpaceShip]")) <= 1) {
            section = SpaceShip;
            continue;
        } else if (std::abs(str.compare("[Aliens]")) <= 1) {
            section = Aliens;
            continue;
        }
        // see which section (SpaceShip or Aliens) are we in
        switch (section) {
        case (SpaceShip):
            extractSpaceShipConfig(str);
            break;
        case (Aliens):
            if (extractAliensConfig(str, aliens, alienFactory)) {
                // wrong config for aliens, show dialog of ignoring line
                QMessageBox ignoringLine;
                ignoringLine.setText("Invalid config line in [Aliens] section:\r\n\r\n" +
                                     QString::fromStdString(str) + "\r\nIgnoring this line.");
                ignoringLine.exec();
            } else {
                // store the config to vector
                aliensConfig.push_back(str);
            }
            break;
        }
    }
    config.close();
    // fill in anything missed out
    fixMap();
}

/************************** GETTERS ***********************/
std::string ConfigReader::getColor() const {
    return spaceShipConfig.find("color")->second;
}

std::string ConfigReader::getSize() const {
    return spaceShipConfig.find("size")->second;
}

std::string ConfigReader::getMove() const {
    return spaceShipConfig.find("move")->second;
}

int ConfigReader::getCoord() const { return this->coord; }

/************************ SETTERS *************************/
// reads the map value and then saves it
void ConfigReader::setColor(std::string newColor) {
    spaceShipConfig["color"] = newColor;
}
void ConfigReader::setSize(std::string newSize) {
    spaceShipConfig["size"] = newSize;
}

/****************** HELPER (CHECK) FUNCTIONS *************/
bool ConfigReader::checkSize(std::string isize) {
    return (isize == "Tiny" || isize == "Normal" || isize == "Large" ||
            isize == "Giant");
}
// checks if it is one of the colours we offer
bool ConfigReader::checkColor(std::string cname) {
    return (std::find(colors.begin(), colors.end(), cname) != colors.end());
}
// Ships should move
bool ConfigReader::checkMove(std::string move) {
    if (move.empty()) {
        return false;
    }
    for (unsigned i = 0; i < move.length(); i++) {
        char a = move.at(i);
        if (a != 'L' && a != 'S' && a != 'R' && a != '_') {
            return false;
        }
    }
    return true;
}
// checks the coord if it is a POSITIVE INT and sets int_coord variable.
// will cut off bad characters e.g., 900asdfasdf becomes 900.
// does not accept negative numbers, however.
bool ConfigReader::checkCoord(std::string coord) {
    // check if empty. coords need a letter.
    if (coord.empty() || coord.at(0) == '-') {
        return false;
    }
    std::istringstream stream(coord);
    int number = 0;
    if (stream >> number) {
        // now check if it failed or not, save it
        if (!stream.fail()) {
            this->coord = number;
            return true;
        }
    }
    return false;
}

// returns the number of the index in the default key array
int ConfigReader::goodKey(std::string key) {
    for (unsigned i = 0; i < defaultKeys.size(); i++) {
        if (defaultKeys.at(i) == key) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

// returns if the value is a valid one... I think there's a nicer way to do
// this.
bool ConfigReader::goodValue(std::string key, std::string value) {
    // at this point we already know the key is valid
    if (key == "color") {
        value[0] = static_cast<char>(toupper(value[0]));
        return checkColor(value);
    } else if (key == "size") {
        return checkSize(value);
    } else if (key == "move") {
        return checkMove(value);
    } else if (key == "coord") {
        return checkCoord(value);
    }
    return false;
}

/********************* MAPPING FUNCTIONS *******************/
// This is a hotfix for the extensions >_>;;
void ConfigReader::fixName() {
    // get the actual value and change it
    std::string fixed = spaceShipConfig["color"];
    fixed[0] = static_cast<char>(toupper(fixed[0]));
    spaceShipConfig["color"] = fixed;

    fixed = spaceShipConfig["size"];
    fixed[0] = static_cast<char>(toupper(fixed[0]));
    spaceShipConfig["size"] = fixed;
}

// finds any missing items and fills a default value
void ConfigReader::fixMap() {
    // if the key does not exist, add default values :
    for (unsigned i = 0; i < defaultKeys.size(); i++) {
        std::string key = defaultKeys.at(i);
        if (spaceShipConfig.find(key) == spaceShipConfig.end()) {
            std::string value = defaultValues.at(i);
            spaceShipConfig.insert(std::pair<std::string, std::string>(key, value));
            alertUsingDefault(key);
        }
    }
    // init the 'coord' int variable
    checkCoord(spaceShipConfig.find("coord")->second);

    // fixes color to be Capital ie., "Red" not "red"..
    fixName();
}

void ConfigReader::writeFile(bool usingDefault) {
    // save it to a new file.
    QFile file(path);
    file.open(QFile::WriteOnly);
    QTextStream write(&file);
    // write Space Ship section
    write << "[SpaceShip]\r\n";
    // loop through the created map; if we have different ships
    std::map<std::string, std::string>::iterator it;
    for (it = spaceShipConfig.begin(); it != spaceShipConfig.end(); it++) {
        // write to file
        QString key = QString::fromStdString(it->first);
        QString value = QString::fromStdString(it->second);
        write << key << " " << value << "\r\n";
    }
    write << "\r\n";

    // write Aliens section
    write << "[Aliens]\r\n";
    // if no valid config for aliens, use default
    if (usingDefault) {
        for (auto &&a : defaultAliens)
            write << a.c_str() << "\r\n";
    } else { // use the input config
        for (auto &&a : aliensConfig)
            write << a.c_str();
    }
}

// it just runs 'fixMap()' and saves a folder.
void ConfigReader::createDefault() {
    fixMap();
    writeFile(true);
}
void ConfigReader::alertUsingDefault(std::string key) {
    QMessageBox badValue;
    badValue.setText("Appropriate " + QString::fromStdString(key) +
                     " not found. Default value used.");
    badValue.exec();
}

// does what it says. Won't map anything that isn't an expected header or value.
void ConfigReader::extractSpaceShipConfig(std::string str) {
    std::stringstream list(str);
    std::string key, value;
    list >> key >> value;

    // find the index of this key from the 'default keys' list
    int keyIndex = goodKey(key);
    if (keyIndex != -1) {
        // if the value is not good, then replace with default value.
        if (!goodValue(key, value)) {
            value = defaultValues.at(static_cast<unsigned>(keyIndex));
            alertUsingDefault(key);       }

        spaceShipConfig.insert(std::pair<std::string, std::string>(key, value));
    } // ignore bad keys.
}

/* helper method to split string */
template <typename Out>
static void split(const std::string &s, char delim, Out result) {
    std::stringstream ss;
    ss.str(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        *(result++) = item;
    }
}
static std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}

int ConfigReader::extractAliensConfig(
        std::string str,
        std::vector<std::tuple<SwarmComponent *, std::string, unsigned>> &aliens,
        AlienFactory &alienFactory) {
    // remove newline
    while (!str.empty() &&
           (str[str.length() - 1] == '\n' || str[str.length() - 1] == '\r'))
        str.erase(str.length() - 1);
    // to upper letter
    for (auto &c : str)
        c = static_cast<char>(std::toupper(c));

    // split the line to 4 parts
    std::vector<std::string> vstrings = split(str, ' ');
    if (vstrings.size() != 4)
        return -1;

    try {
        // check second & third as x & y:
        std::vector<std::string> x_vec = split(vstrings[1], '=');
        std::vector<std::string> y_vec = split(vstrings[2], '=');

        if (x_vec.size() != 2 || y_vec.size() != 2 || x_vec[0] != "X" ||
                y_vec[0] != "Y")
            return -1;
        int x = std::stoi(x_vec[1]);
        int y = std::stoi(y_vec[1]);

        // check fourth as valid input
        for (char &c : vstrings[3]) {
            switch (c) {
            case ('_'):
            case ('U'):
            case ('D'):
            case ('L'):
            case ('R'):
            case ('S'):
            case ('H'):
                break;
            default: // invalid char
                return -1;
            }
        }

        // check first arg must be AxB or 1 by itself. A, B must be int
        std::vector<std::string> AxB = split(vstrings[0], 'X');
        if (AxB.size() == 1) {
            int A = std::stoi(AxB[0]);
            if (A != 1)
                return -1;
            aliens.push_back(std::tuple<SwarmComponent *, std::string, unsigned>(
                                   alienFactory.createAlien(x, y, Normal), vstrings[3], 0));
        } else if (AxB.size() == 2) {
            int A = std::stoi(AxB[0]);
            int B = std::stoi(AxB[1]);
            int alienWidth = 0;
            int alienHeight = 0;

            // create a new swarm composite (composite design pattern)
            SwarmComposite *swarm = new SwarmComposite;
            for (int i = 0; i < A; ++i) {
                for (int j = 0; j < B; ++j) {
                    if (i == 0 && j == 0) {
                        swarm->add(alienFactory.createAlien(x, y, Normal));
                        // retrieve alien width & height
                        alienHeight = swarm->getHeight();
                        alienWidth = swarm->getWidth();
                    }else{
                        swarm->add(alienFactory.createAlien(x + i * alienWidth,
                                                            y + j * alienHeight, Normal));
                    }
                }
            }
            aliens.push_back(std::tuple<SwarmComponent *, std::string, unsigned>(
                                   swarm, vstrings[3], 0));
        }
    } catch (std::invalid_argument) { // error in stoi
        return -1;
    }
    return 0;
}
