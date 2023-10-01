#ifndef CONWAY_HPP
#define CONWAY_HPP

#include <vector>

namespace conway
{
    struct Cell
    {
        int x;
        int y;
    };
    using Life = std::vector<Cell>;

    Life getNeigbours(Life &life);

    bool keepAlive(Cell target, Life const &life);
    bool shouldSpawn(Cell target, Life const &life);

    bool isNeighbour(Cell a, Cell b);
    int count_neighbours(Cell ourCell, Life const &life);
}

#endif
