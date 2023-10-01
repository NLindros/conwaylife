#include <algorithm>
#include <tuple>

#include "conway.hpp"

namespace conway
{
    bool isNeighbour(Cell a, Cell b)
    {
        if (a.x == b.x && a.y == b.y)
        {
            return false;
        }
        bool x_cond = a.x == b.x || a.x - 1 == b.x || a.x + 1 == b.x;
        bool y_cond = a.y == b.y || a.y - 1 == b.y || a.y + 1 == b.y;
        return x_cond && y_cond;
    };

    bool keepAlive(Cell target, Life const &life)
    {
        auto n_neighbours = count_neighbours(target, life);
        return n_neighbours > 1 && n_neighbours < 4;
    };

    bool shouldSpawn(Cell target, Life const &life)
    {
        auto n_neighbours = count_neighbours(target, life);
        return n_neighbours == 3;
    };
    int count_neighbours(Cell ourCell, Life const &life)
    {
        int sum = 0;
        for (auto const &lifeCell : life)
        {
            sum += (int)isNeighbour(ourCell, lifeCell);
        }
        return sum;
    };

    // Life getNeigbours(Life &life)
    // {
    //     const auto [x_min, x_max] = std::minmax_element(
    //         begin(life), end(life),
    //         [](const Cell &a, const Cell &b)
    //         { return a.x < b.x; });

    //     const auto [y_min, y_max] = std::minmax_element(
    //         begin(life), end(life),
    //         [](const Cell &a, const Cell &b)
    //         { return a.y < b.y; });

    //     Life result{};
    //     for (int x = x_min->x; x <= x_max->x; x++)
    //     {
    //         for (int y = y_min->y; y <= y_max->y; y++)
    //         {
    //             result.insert({x, y});
    //         }
    //     };
    //     return result;
    // };
}
