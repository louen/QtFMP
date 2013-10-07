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
        // Estimated distance from current to goal(heuristic h(x))
        unsigned int heuristics(const Hexagon& node, const Hexagon& goal);

};


#endif // !FMP_PATH_FINDER_h
