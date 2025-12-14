#ifndef ENUM_H
#define ENUM_H

enum Arinc429type{
    BNR = 0,
    BCD = 1,
    DISCRETE = 2
};

enum Arinc429SSM{
    NORTH = 0,
    WEST = 1,
    EAST = 2,
    SOUTH = 3
};

enum Arinc429SDI{
    GLONASS_1 = 0,
    GLONASS_2 = 1,
    GLONASS_3 = 2,
    GLONASS_4 = 3
};

enum Arinc429Label{
    SPEED = 0,
    ALTITUDE = 1,
    ACCELERATION = 2,
    CAPTURE = 3,
    LONGITUDE = 4,
    LATITUDE = 5,
    DEPARTURE = 6,
    LANDING_GEAR = 7
};

#endif // ENUM_H
