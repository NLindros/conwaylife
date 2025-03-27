#include <gtest/gtest.h>
#include <queue>
#include "be/cpp/conway/conway.hpp"

::testing::AssertionResult isSameLife(const conway::Life &a, const conway::Life &b)
{
    if (a == b)
    {
        return ::testing::AssertionSuccess();
    }
    else
    {
        return ::testing::AssertionFailure() << std::endl
                                             << a << " don't equal\n"
                                             << b;
    }
}

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

TEST(LifeConditions, TestThatCorrectNumberOfNeighboursKeepsItAlive)
{
    EXPECT_EQ(conway::keepAlive(0), false);
    EXPECT_EQ(conway::keepAlive(1), false);
    EXPECT_EQ(conway::keepAlive(2), true);
    EXPECT_EQ(conway::keepAlive(3), true);
    EXPECT_EQ(conway::keepAlive(4), false);
    EXPECT_EQ(conway::keepAlive(9), false);
    EXPECT_EQ(conway::keepAlive(-2), false);
}

TEST(SpawnCondition, TestThatCorrectNumberOfNeigboursSpawnACell)
{
    EXPECT_EQ(conway::shouldSpawn(0), false);
    EXPECT_EQ(conway::shouldSpawn(1), false);
    EXPECT_EQ(conway::shouldSpawn(2), false);
    EXPECT_EQ(conway::shouldSpawn(3), true);
    EXPECT_EQ(conway::shouldSpawn(4), false);
    EXPECT_EQ(conway::shouldSpawn(-2), false);
}

TEST(CheckNeigbours, TestThatWeCaGetAllNeigbours)
{
    conway::Cell cell{0, 0};
    conway::Life expectedNeigbours{
        {0, -1},
        {0, 1},
        {1, -1},
        {1, 0},
        {1, 1},
        {-1, -1},
        {-1, 0},
        {-1, 1}};
    conway::Life result = conway::getNeigbours(cell);
    EXPECT_TRUE(isSameLife(result, expectedNeigbours));
}

TEST(ShapeTests, TestBlinkerStep)
{
    conway::Life blinkerStageA{{-1, 0}, {0, 0}, {1, 0}};
    conway::Life blinkerStageB{{0, -1}, {0, 0}, {0, 1}};

    conway::Life afterLifeStep = conway::stepLife(blinkerStageA);
    EXPECT_TRUE(isSameLife(afterLifeStep, blinkerStageB));
}

TEST(ShapeTest, TestSameGliderShapeReappearAsMovedAfterFourSteps)
{
    conway::Life glider{{0, 0}, {1, 0}, {2, 0}, {2, -1}, {1, -2}};
    conway::Life expectedShapeMoved{};
    for (const auto &cell : glider)
    {
        expectedShapeMoved.insert({cell.x + 1, cell.y + 1});
    }

    std::vector<conway::Life> lifeStages{glider};
    for (int i = 0; i < 4; i++)
        lifeStages.push_back(conway::stepLife(lifeStages.at(i)));

    EXPECT_TRUE(isSameLife(lifeStages.back(), expectedShapeMoved));
}