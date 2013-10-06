#ifndef FMP_PATH_FINDER_H
#define FMP_PATH_FINDER_H
#include <vector>

class Hexagon;
class fmpGameObject;

class fmpPathFinder
{
    public:
        virtual bool findPath(const Hexagon& start, const Hexagon& goal, std::vector<const Hexagon*>& path) = 0; 
};


class fmpAStarPathFinder
{
    public:
        virtual bool findPath(const Hexagon& start, const Hexagon& goal, std::vector<const Hexagon*>& path);


    protected:
        // Estimated distance from current to goal
        unsigned int futureCost(const Hexagon& node, const Hexagon& goal);

        // Distance from start to current
        unsigned int pastCost(const Hexagon& start, const Hexagon& node);

        // Total cost
        unsigned int cost(const Hexagon& start, const Hexagon& node, const Hexagon& goal) {return 0;}
};


#endif // !FMP_PATH_FINDER_h
