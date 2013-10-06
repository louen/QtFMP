#include "fmp.h"
#include <cstdio>
#include <cassert>

#define FMP_LOG( level, message) (fmpDebugOutput::getInstance().printf(message))
#define FMP_ASSERT( cond, message ) do { if (!(cond)) { FMP_LOG(0,message); assert(cond);}} while (0)

Board::Board (char* filename)
{
    FILE* f = fopen(filename, "r");
    // first line is X  and Y
    m_linMax = 0;
    m_colMax = 0;
    fscanf(f,"%i %i\n", &m_linMax, &m_colMax);
            
    // number of hexes in an odd column : linmax+1 /2
    // number of hexes in an even column : (linmax -1) /2
    // number of odd colums : colmax + 1 /2
    // number of even columns : colmax -1 /2 
    m_numHexagons = ((m_linMax * m_colMax) +1) /2;
    m_hexStorage = new Hexagon* [m_numHexagons];
    
    // Load the hexes types.
    {
        char c = 0;
        int line = 0;
        int column = 0;
        while ( (c = fgetc(f)) != EOF) 
        {
            Hexagon::Type toCreate = Hexagon::INVALID;
            switch (c)
            {
                // Next line
                case '\n':
                    line++;
                    column = 0;
                    // ignore the column++
                    continue;

                case 'G':
                    toCreate = Hexagon::GROUND;
                    break;

                case 'W':
                    toCreate = Hexagon::WATER;
                    break;

                case 'S':
                    toCreate = Hexagon::SWAMP;
                    break;

                case 'R':
                    toCreate = Hexagon::REEF;
                    break;
                    
                case 'M':
                    toCreate = Hexagon::MOUNTAIN;
                    break;
                case ' ': // do nothing
                    break;

                default:
                    fmpDebugOutput::getInstance().printf("ERROR : invalid map file");
            }
            if (toCreate != Hexagon::INVALID)
            {
                //fmpDebugOutput::getInstance().printf("creating %i %i", line, column);
                getHexPtr(line, column) = new Hexagon(line, column, toCreate);
            }
            ++column;
        }

    }
    // Now fixup the links in the hexagons.
    for (int i = 0 ; i < getNumHexs(); ++i)
    {
        Hexagon* hex = m_hexStorage[i];
        int line = hex->m_line;
        int column = hex->m_column;

        hex->m_neighbors[0] = ( (line > 1) ?
                        getHexPtr(line - 2, column) : nullptr);

        hex->m_neighbors[1] = ( (line > 0 && column < m_colMax - 1 ) ?
                        getHexPtr(line - 1, column + 1) : nullptr);

        hex->m_neighbors[2] = ( (line < m_linMax - 1 && column < m_colMax -1 )?
                         getHexPtr(line + 1, column + 1 ) : nullptr);

        hex->m_neighbors[3] = ( (line <  m_linMax - 2) ? 
                        getHexPtr(line + 2, column) : nullptr);
        
        hex->m_neighbors[4] = ( (line < m_linMax - 1 && column > 0 )?
                        getHexPtr(line + 1, column - 1) : nullptr);

        hex->m_neighbors[5] = ( (line > 0 && column > 0)?
                        getHexPtr(line - 1, column - 1) : nullptr);


    }


    checkConsistency();
    //print();

}

Board::~Board()
{
    for (int i = 0; i  < m_numHexagons; ++i)
    {
        delete m_hexStorage[i];
    }
    delete[] m_hexStorage;
}

Hexagon*& Board::getHexPtr(int line, int column)
{
    if ((line %2) != (column %2)) 
    {
        fmpDebugOutput::getInstance().printf("ERROR line : %i, col %i", line, column); 
    }

    int numOdd = (line+1) /2;
    int numEven = line/2;
    
    int index = (numOdd *  ((m_colMax + 1) / 2))
              + (numEven * ((m_colMax    ) / 2)) 
              + (column/2);
    
    return m_hexStorage[index];
}

Hexagon& Board::getHex(int line, int column)
{
    if ((line %2) != (column %2)) 
    { 
        fmpDebugOutput::getInstance().printf("ERROR line : %i, col %i", line, column); 
    }
    return *getHexPtr(line,column);
}	

void Board::print()
{

    char* lineBuf = new char[m_colMax+3];


    for (int line = 0 ; line < m_linMax; ++line)
    {
        memset(lineBuf, 0x0 , m_colMax+3);
        if(line %2)
        {
            lineBuf[0] = ' ';	
        } 
        for (int col = line %2 ; col < m_colMax ; col +=2)
        {
            char& repr = lineBuf[col];
            repr = '?';

            switch (getHex(line,col).getType())
            {
                case Hexagon::GROUND:
                    repr = 'G';
                break;

                case Hexagon::WATER:
                    repr = 'W';
                break;

                case Hexagon::SWAMP:
                    repr = 'S';
                break;

                case Hexagon::REEF:
                    repr = 'R';
                break;
                    
                case Hexagon::MOUNTAIN:
                    repr = 'M';
                break;
            }
            lineBuf[col + 1] = ' ';			
        }

        fmpDebugOutput::getInstance().print(lineBuf);
    }
}

void Board::checkConsistency()
{
    for (int i = 0 ; i < m_numHexagons; ++i)
    {
        Hexagon* hex = m_hexStorage[i];
        FMP_ASSERT(hex == getHexPtr(hex->m_line, hex->m_column), "Inconsistent hex coordinates");
        for (int side = 0 ; side < 6 ; ++side)
        {
            if (hex->m_neighbors[side])
            {
                FMP_ASSERT(hex->m_neighbors[side]->m_neighbors[ (side+3) % 6] == hex, "Inconsistent neighbors");
            }		
        }
    }
}

/*
int main()
{
    Board * board = new Board(30,40);
    printff("Hello,world\n");

    


    delete board;
    return 0;
}*/