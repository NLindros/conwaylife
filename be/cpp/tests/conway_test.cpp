#include <gtest/gtest.h>

#include "be/cpp/conway/conway.hpp"

TEST(CheckNeighbour, TestThatSurroundingCellsAreIdentifiedAsNeighbours)
{
    conway::Cell refCell = {0, 0};
    EXPECT_EQ(conway::isNeighbour(refCell, {0, -1}), true);
    EXPECT_EQ(conway::isNeighbour(refCell, {0, 1}), true);
    EXPECT_EQ(conway::isNeighbour(refCell, {1, -1}), true);
    EXPECT_EQ(conway::isNeighbour(refCell, {1, 0}), true);
    EXPECT_EQ(conway::isNeighbour(refCell, {1, 1}), true);
    EXPECT_EQ(conway::isNeighbour(refCell, {-1, -1}), true);
    EXPECT_EQ(conway::isNeighbour(refCell, {-1, 0}), true);
    EXPECT_EQ(conway::isNeighbour(refCell, {-1, 1}), true);
}

TEST(CheckNeighbour, TestThatDistantCellsAreNotNeighbours)
{
    conway::Cell refCell{1, 0};
    EXPECT_EQ(conway::isNeighbour(refCell, {3, 0}), false);
    EXPECT_EQ(conway::isNeighbour(refCell, {-2, 0}), false);
    EXPECT_EQ(conway::isNeighbour(refCell, {-2, 2}), false);
}

TEST(CheckNeighbour, TestThatSameCellAreNotNeighbours)
{
    EXPECT_EQ(conway::isNeighbour({0, 0}, {0, 0}), false);
    EXPECT_EQ(conway::isNeighbour({1, 1}, {1, 1}), false);
}

TEST(LifeConditions, TestThatCellDiesIfNotEnoughtNeighbourCells)
{
    conway::Life noLife{};
    EXPECT_EQ(conway::keepAlive({0, 0}, noLife), false);

    conway::Life singleNeighbour{{1, 0}};
    EXPECT_EQ(conway::keepAlive({0, 0}, singleNeighbour), false);

    conway::Life tooCrowded{{1, 0}, {-1, 0}, {0, -1}, {0, 1}};
    EXPECT_EQ(conway::keepAlive({0, 0}, tooCrowded), false);
}

TEST(LifeConditions, TestThatCellStaysAliveIfCorrectNumberOfNeighbours)
{
    conway::Life twoNeighbours{{1, 0}, {-1, 0}};
    EXPECT_EQ(conway::keepAlive({0, 0}, twoNeighbours), true);

    conway::Life threeNeighbours{{1, 0}, {-1, 0}, {0, 1}};
    EXPECT_EQ(conway::keepAlive({0, 0}, threeNeighbours), true);
}

TEST(SpawnCondition, TestThatNewCellIsSpawnIfThreeNeigbours)
{
    conway::Life liveCells{{-1, 0}, {0, 0}, {1, 0}};
    EXPECT_EQ(conway::shouldSpawn({0, 1}, liveCells), true);
    EXPECT_EQ(conway::shouldSpawn({1, 1}, liveCells), false);
}

// TEST(GridTests, GetExpendedGrid)
// {
//     conway::Life initLife{{0, 0}};
//     conway::Life expectedNeigbours{
//         {0, -1},
//         {0, 1},
//         {1, -1},
//         {1, 0},
//         {1, 1},
//         {-1, -1},
//         {-1, 0},
//         {-1, 1}};
//     conway::Life result = conway::getNeigbours(initLife);
// }
