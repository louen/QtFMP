#ifndef FMP_WEATHER_H
#define FMP_WEATHER_H
// This class is responsible to manage everything related to tides.
// There should be only one instance owned by the game.
class fmpWeather
{
public:
    enum Tide
    {
        LOW =0,
        NORMAL,
        HIGH,
    };

    // Tells you the current tide (information available to anyone)
    Tide getCurrentTide() const;

    // Tells you the state of the tide in numSteps turns (you have to have at least that number of layers).
    Tide getNextTide(int numSteps = 1) const;

    // Advance the state of the tide.
    void advance();

public:
    Tide m_currentTide;
};  
#endif // !FMP_WEATHER_H
