#include <game/fmpPathFinder.h>

#include <game/fmp.h>

// standard containers for open and closed lists
#include <queue>
#include <set>
#include <unordered_map>
#include <stack>


struct OpenSetEntry
{
    unsigned int cost() const
    {
        return m_pastCost + m_futureCost;
    }
    
    const Hexagon* m_hex;
    unsigned int m_pastCost;
    unsigned int m_futureCost;
};

struct ComparisonFunction
{
    // returns true if lhs is worse than rhs
    bool operator() ( const OpenSetEntry& lhs, const OpenSetEntry& rhs)
    {
        return lhs.cost() > rhs.cost();
    }
};

// Maybe a deque instead of vector ?
class OpenSet : public std::priority_queue<OpenSetEntry, std::vector<OpenSetEntry>, ComparisonFunction >
{
    public:
    std::vector<OpenSetEntry>::const_iterator find(const Hexagon* hex) const
    {
        for (auto it = c.begin(); it != c.end() ; ++it)
        {
            if (it->m_hex == hex)
            {
                return it;
            }
        }
        return c.end();
    }

    bool pushOrReplace(const OpenSetEntry& entry)
    {
        auto it = find(entry.m_hex);

        // If the entry is not in the open list, put it immediately.
        if (it == c.end())
        {
            push(entry);
            return true ;

        }
        //  If the entry is in the list, but has a better value, replace it.
        else if (comp(*it, entry))
        {
            c.erase(it);
            std::sort_heap(c.begin(), c.end(), comp);
            push(entry);
            return true;
        }

        // Entry was in the list with a better cost (unlikely).
        return false;
    }

};

void reconstructPath(const Hexagon & start, const Hexagon& goal, const std::unordered_map<const Hexagon*, const Hexagon*>parents, std::vector<const Hexagon*>& path)
{
    std::stack<const Hexagon*> pathStack;
    const Hexagon* current = &goal;

    while (current != &start)
    {
        pathStack.push(current);
        current = parents.at(current);
    }
    
    // Start is not in the path stack so we add it in the path directly
    path.push_back(&start);
    while (!pathStack.empty())
    {
        path.push_back(pathStack.top());
        pathStack.pop();
    }
}



bool fmpAStarPathFinder::findPath(const Hexagon& start, const Hexagon& goal, std::vector<const Hexagon*>& path)
{
    // A* implementation
    // assert path.clear();

    // Trivial early out
    if (&start == &goal)
    {
        path.push_back(&start);
        return true;
    }

    OpenSet open;
    std::set<const Hexagon*> closed;
    // Allows for reconstruction of the path at the end.
    std::unordered_map<const Hexagon*, const Hexagon*> parents;

    OpenSetEntry startEntry = {&start, 0, heuristics(start, goal)};
    open.push(startEntry);
    path.push_back(&start);


    while( !open.empty() )
    {
        OpenSetEntry currentEntry = open.top();
        
        if (currentEntry.m_hex == &goal)
        {
            reconstructPath(start, goal, parents, path);
            return true;
        }
        
        open.pop();
        closed.insert(currentEntry.m_hex);

        for (int i = 0 ; i < 6 ; ++i)
        {
            const Hexagon* neighbor = currentEntry.m_hex->m_neighbors[i];
            if (neighbor)
            {
                auto neighborPosClosed = closed.find(neighbor);
                if (neighborPosClosed != closed.end())
                {
                    OpenSetEntry neighborEntry = {
                                        neighbor, 
                                        currentEntry.m_pastCost + 1,
                                        heuristics(*neighbor,goal)
                                        };

                    if (open.pushOrReplace(neighborEntry))
                    {
                        parents.insert(std::pair<const Hexagon*, const Hexagon*>(neighbor, currentEntry.m_hex));
                    }
                }
            }
        }
    }
    return false;
}


unsigned int fmpAStarPathFinder::heuristics(const Hexagon& node, const Hexagon& goal)
{
    return Hexagon::distance(node,goal);
}