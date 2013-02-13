#include <map>
#include <cstdio>

class Weather
{
	public:
		enum Tide
		{
			LOW =0,
			NORMAL,
			HIGH,
		};

		Tide getCurrentTide() const;
		Tide getNextTide() const;

};

class Hexagon;
class Unit
{
		public:
		enum Type
		{
			SPACESHIP,
			TURRET,
			TANK,
			FATGUY,
			CRAB,
			LAYER,
			BOAT,
			BARGE,
			BRIDGE
		};

		virtual bool canMoveHere(const Hexagon& hex, const Weather& weather) const = 0;

		Type getType() const;
        
        class Hexagon * position ;

        Type m_type;
};

class Hexagon
{
    public:
		enum Type
		{
			MOUNTAIN = 0,
			GROUND,
			SWAMP,
			REEF,
			WATER
		};

		Type getType() const;
		Hexagon(int id, Type type): m_id(id), m_type (type) {}

	public:
		int m_id;
		Type m_type;
		// 0 N, 1 NE, 2 SE, 3 S, 4 SW, 5 NW
		Hexagon* m_neighbors[6];
};

class SeaUnit : public Unit
{
	bool canMoveHere(const Hexagon& hex, const Weather& weather)
	{
		switch (hex.getType())
		{
			case Hexagon::MOUNTAIN:
			case Hexagon::GROUND:
				return false;
			case Hexagon::SWAMP:
				return (weather.getCurrentTide() == Weather::HIGH);
			case Hexagon::REEF:
				return (weather.getCurrentTide() != Weather::LOW);
			case Hexagon::WATER:
				return true;
			default:
				return false;
		}
	}
};


class Board
{
	public:
		Board(int width, int length)
		{
			for (int i = 0 ; i < length ; ++i)
			{
				for (int j = 0 ; j < width ; ++j)
				{
					Hexagon* hexagon = new Hexagon(width * i + j, Hexagon::GROUND);
					
				}
			}	
		}
		Hexagon* getHexagon(int id);


		std::map<int, Hexagon*> board;
};


int main()
{
	Board * board = new Board(30,40);
	printf("Hello,world\n");

	


	delete board;
	return 0;
}