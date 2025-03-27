#include <algorithm>

#include "be/cpp/conway/conway.hpp"

namespace conway
{
    bool isNeighbour(const Cell &a, const Cell &b)
    {
        if (a.x == b.x && a.y == b.y)
        {
            return false;
        }
        bool x_cond = a.x == b.x || a.x - 1 == b.x || a.x + 1 == b.x;
        bool y_cond = a.y == b.y || a.y - 1 == b.y || a.y + 1 == b.y;
        return x_cond && y_cond;
    };

    bool keepAlive(const int numberOfNeighbours)
    {
        return numberOfNeighbours == 2 || numberOfNeighbours == 3;
    };

    bool shouldSpawn(const int numborOfNeighbours)
    {
        return numborOfNeighbours == 3;
    };

    bool isCellDead(const Cell &cell, const Life &life)
    {
        return life.find(cell) == life.end();
    }

    bool isAliveInNextLife(const Cell &queryCell, const Life &life)
    {
        auto nNeighbours = countNeighbours(queryCell, life);
        return isCellDead(queryCell, life) ? shouldSpawn(nNeighbours) : keepAlive(nNeighbours);
    }

    int countNeighbours(const Cell &ourCell, const Life &life)
    {
        int sum = 0;
        for (Cell const &lifeCell : life)
        {
            sum += (int)isNeighbour(ourCell, lifeCell);
        }
        return sum;
    };

    Life getNeigbours(const Cell &cell)
    {
        Life result{};
        for (int x = cell.x - 1; x <= cell.x + 1; x++)
        {
            for (int y = cell.y - 1; y <= cell.y + 1; y++)
            {
                if (x != cell.x || y != cell.y)
                {
                    result.insert({x, y});
                }
            }
        };
        return result;
    }

    Life stepLife(const Life &initLife)
    {
        Life afterLife{};
        std::pair<Cell, Cell> corner = getCornerCellsExpandedOnce(initLife);
        for (int x = corner.first.x; x <= corner.second.x; x++)
        {
            for (int y = corner.first.y; y <= corner.second.y; y++)
            {
                if (isAliveInNextLife(Cell({x, y}), initLife))
                {
                    afterLife.insert({x, y});
                }
            }
        }
        return afterLife;
    }

    std::pair<Cell, Cell> getCornerCellsExpandedOnce(const Life &life)
    {
        const auto y_edge = std::minmax_element(
            begin(life), end(life),
            [](const Cell &a, const Cell &b)
            { return a.y < b.y; });

        return std::pair<Cell, Cell>{
            {life.begin()->x - 1, y_edge.first->y - 1},
            {life.rbegin()->x + 1, y_edge.second->y + 1}};
    }
}
