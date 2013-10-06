#include <GUI/fmpMainWindow.h>

#include <game/fmpWeather.h>


// A class representing any object that may be on the board.
class Hexagon
{
    public:
        enum Type
        {
            MOUNTAIN = 0,
            GROUND,
            SWAMP,
            REEF,
            WATER,
            // End of valid terrain types
            MAX_TERRAIN_TYPE,
            INVALID = MAX_TERRAIN_TYPE
        };

        Type getType() const { return m_type ;}
        Hexagon(int line, int column, Type type): m_line(line),m_column(column), m_type (type) {}


        static int distance(const Hexagon& hex1, const Hexagon& hex2)
        {
            return (abs(hex2.m_line - hex1.m_line) + abs (hex2.m_column - hex1.m_column)) / 2;
        }

    public:
        int m_line;
        int m_column;
        Type m_type;
        // 0 N, 1 NE, 2 SE, 3 S, 4 SW, 5 NW
        Hexagon* m_neighbors[6];
};

class Board
{
    public:
        Board(char* filename);
        ~Board();

        Hexagon*& getHexPtr(int line, int column);
        Hexagon& getHex(int line, int column);

        Hexagon& getHex(int num) { return *m_hexStorage[num];}

        void print();
        void checkConsistency();



        int getNumHexs() { return m_numHexagons;}
    protected:
        int m_linMax;
        int m_colMax;
        int m_numHexagons;
        Hexagon** m_hexStorage;
};