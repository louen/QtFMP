#include <game/fmpPathFinder.h>

#include <game/fmp.h>

#include <queue>
#include <set>


struct OpenSetEntry
{
    const Hexagon* hex;
    unsigned int cost;
};


struct ComparisonFunction
{
    // returns true if lhs is less good than rhs
    bool operator() ( const OpenSetEntry& lhs, const OpenSetEntry& rhs)
    {
        return lhs.cost > rhs.cost;
    }
};

bool fmpAStarPathFinder::findPath(const Hexagon& start, const Hexagon& goal, std::vector<const Hexagon*>& path)
{
    // A* implementation

    // Open set is based on a std vector.
    std::priority_queue<OpenSetEntry, std::vector<OpenSetEntry>, ComparisonFunction > open;
    std::set<const Hexagon*> closed;

    path.clear();
    OpenSetEntry startEntry = {&start,cost(start,start,goal)};
    open.push(startEntry);
    path.push_back(&start);


    while( !open.empty() )
    {
        OpenSetEntry currentEntry = open.top();
        
        if (currentEntry.hex == &goal)
        {
            
            return true;
        }
        
        open.pop();
        closed.insert(currentEntry.hex);

        for (int i = 0 ; i < 6 ; ++i)
        {
            const Hexagon* neighbor = currentEntry.hex->m_neighbors[i];
            if (neighbor)
            {
                std::set<const Hexagon*>::const_iterator neighborPos = closed.find(neighbor);
                if (neighborPos != closed.end())
                {
                    unsigned int neighborCost = cost(start, *neighbor, goal);
                    OpenSetEntry neighborEntry = {neighbor, neighborCost};

                    open.push(neighborEntry);
                }

            }

        }

    }


    return false;
}