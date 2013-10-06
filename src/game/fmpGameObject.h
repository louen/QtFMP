#ifndef FMP_GAME_OBJECT_H
#define GMP_GAME_OBJECT_H
#include <game/fmpWeather.h>

class Hexagon;



class fmpGameObject
{
public:
    const Hexagon& getPosition() const;

    void setPosition(const Hexagon& hex);

    // Tells you if a unit can be there or not, at the given tide. 
    virtual bool isPositionLegal(const Hexagon& hex, fmpWeather::Tide& tide ) = 0;

protected:
    Hexagon* m_position;

    // True if this object can be put 'inside' a transport.
    bool m_isTransportable; 
};


class fmpUnit : public fmpGameObject
{
public:
    // This enum should go away to be replaced by virtual calls ?
    enum Type
    {
        SPACESHIP = 0,
        TURRET,
        TANK,
        FATGUY,
        CRAB,
        LAYER,
        BOAT,
        BARGE,
        BRIDGE,
        // End of valid units types
        MAX_UNIT_TYPE,
        INVALID = MAX_UNIT_TYPE
    };

    Type getType() const;

    Type m_type;
};

#endif // !FMP_GAME_OBJECT_H

