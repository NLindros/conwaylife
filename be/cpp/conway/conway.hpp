#ifndef CONWAY_HPP
#define CONWAY_HPP

#include <iostream>
#include <set>
#include <tuple>

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
    bool operator==(const Cell &a, const Cell &b)
    {
        return a.x == b.x && a.y == b.y;
    }
    std::ostream &operator<<(std::ostream &stream, const Cell &cell)
    {
        stream << "{" << cell.x << "," << cell.y << "}";
        return stream;
    }

    using Life = std::set<Cell>;

    Life getNeigbours(const Cell &cell);
    std::pair<Cell, Cell> getCornerCellsExpandedOnce(const Life &life);
    Life stepLife(const Life &initLife);

    std::ostream &operator<<(std::ostream &stream, const Life &life)
    {
        stream << "[ ";
        for (const auto &cell : life)
        {
            stream << cell << " ";
        }

        stream << "]";
        return stream;
    }
    bool keepAlive(int numberOfNeighbours);
    bool shouldSpawn(int numberOfNeighbours);

    bool isNeighbour(const Cell &a, const Cell &b);
    int countNeighbours(const Cell &ourCell, const Life &life);
}

#endif
