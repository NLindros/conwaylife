#ifndef CONWAY_HPP
#define CONWAY_HPP

#include <set>

namespace conway
{
    struct Cell
    {
        int x;
        int y;
    };
    bool operator<(const Cell &a, const Cell &b)
    {
        return std::tie(a.x, a.y) < std::tie(b.x, b.y);
    }

    using Life = std::set<Cell>;
    Life getNeigbours(Life &life);

    bool keepAlive(Cell target, Life const &life);
    bool shouldSpawn(Cell target, Life const &life);

    bool isNeighbour(Cell a, Cell b);
    int count_neighbours(Cell ourCell, Life const &life);
}

#endif
