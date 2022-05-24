from functools import reduce


def neighbours(cell, grid):
    x, y = cell
    possible_neighbours = (
        (x - 1, y),
        (x - 1, y - 1),
        (x - 1, y + 1),
        (x, y - 1),
        (x, y + 1),
        (x + 1, y - 1),
        (x + 1, y),
        (x + 1, y + 1),
    )
    return {cell for cell in possible_neighbours if cell in grid}


def step(grid):
    still_living = cull(grid)
    new_born = spawn(grid)
    return still_living | new_born


def cull(grid):
    good_population_size = (2, 3)
    still_living = {
        cell for cell in grid if len(neighbours(cell, grid)) in good_population_size
    }

    return still_living


def spawn(grid):
    new_born = set()
    for cell in expand_grid(grid):
        N = neighbours(cell, grid)
        if len(N) == 3:
            new_born.add(cell)
    return new_born


def expand_grid(grid):
    min_x, *_, max_x = sorted(cell[0] for cell in grid)
    min_y, *_, max_y = sorted(cell[1] for cell in grid)
    x_range = min_x - 1, max_x + 2
    y_range = min_y - 1, max_y + 2
    return {(x, y) for x in range(*x_range) for y in range(*y_range)}
