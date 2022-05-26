from itertools import groupby


def possible_neighbours(cell):
    x, y = cell
    return {
        (x - 1, y),
        (x - 1, y - 1),
        (x - 1, y + 1),
        (x, y - 1),
        (x, y + 1),
        (x + 1, y - 1),
        (x + 1, y),
        (x + 1, y + 1),
    }


def amount_of_neighbours(cell, grid):
    return len(possible_neighbours(cell) & grid)


def step(grid):
    still_living = cull(grid)
    new_born = spawn(grid)
    return still_living | new_born


def cull(grid):
    healthy_amount_of_neighbours = (2, 3)
    return {
        cell
        for cell in grid
        if amount_of_neighbours(cell, grid) in healthy_amount_of_neighbours
    }


def spawn(grid):
    perfect_breeding_population = 3
    return {
        cell
        for cell in expand_grid(grid)
        if amount_of_neighbours(cell, grid) == perfect_breeding_population
    }


def expand_grid(grid):
    min_x, *_, max_x = sorted(cell[0] for cell in grid)
    min_y, *_, max_y = sorted(cell[1] for cell in grid)
    x_range = range(min_x - 1, max_x + 2)
    y_range = range(min_y - 1, max_y + 2)
    return {(x, y) for x in x_range for y in y_range}
