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
    // returns true if lhs is worse than rhs
    bool operator() ( const OpenSetEntry& lhs, const OpenSetEntry& rhs)
    {
        return lhs.cost > rhs.cost;
    }
};

class OpenSet : public std::priority_queue<OpenSetEntry, std::vector<OpenSetEntry>, ComparisonFunction >
{
    public:
    std::vector<OpenSetEntry>::const_iterator find(const Hexagon* hex) const
    {
        for (auto it = c.begin(); it != c.end() ; ++it)
        {
            if (it->hex == hex)
            {
                return it;
            }
        }
        return c.end();
    }

    void pushOrReplace(const OpenSetEntry& entry)
    {
        auto it = find(entry.hex);

        // If the entry is not in the open list, put it immediately.
        if (it == c.end())
        {
            push(entry);

        }
        //  If the entry is in the list, but has a better value, replace it.
        else if (comp(*it, entry))
        {
            c.erase(it);
            std::sort_heap(c.begin(), c.end(), comp);
            push(entry);
        }
    }

};

bool fmpAStarPathFinder::findPath(const Hexagon& start, const Hexagon& goal, std::vector<const Hexagon*>& path)
{
    // A* implementation

    // Open set is based on a std vector.
    OpenSet open;
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
            // construct path
            return true;
        }
        
        open.pop();
        closed.insert(currentEntry.hex);

        for (int i = 0 ; i < 6 ; ++i)
        {
            const Hexagon* neighbor = currentEntry.hex->m_neighbors[i];
            if (neighbor)
            {
                auto neighborPosClosed = closed.find(neighbor);
                if (neighborPosClosed != closed.end())
                {
                    unsigned int neighborCost = cost(start, *neighbor, goal);
                    OpenSetEntry neighborEntry = {neighbor, neighborCost};

                    open.pushOrReplace(neighborEntry);
                }

            }

        }

    }


    return false;
}