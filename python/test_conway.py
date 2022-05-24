from unittest import result
import pytest
import conway


def test_that_all_neighbours_is_found():

    a_cell = (1, 1)
    surrounding = {(x, y) for x in range(0, 3) for y in range(0, 3)} ^ {a_cell}
    not_neighbour = (4, 3)
    grid = {*surrounding, not_neighbour}
    neighbours = conway.neighbours(a_cell, grid)
    assert neighbours == surrounding


def test_that_cells_with_2_neighbours_lives():
    input_grid = {(0, 0), (0, 1), (0, 2)}
    output_grid = conway.cull(input_grid)
    assert (0, 1) in output_grid


def test_that_cells_with_3_neighbours_lives():
    input_grid = {(0, 0), (0, 1), (0, 2), (1, 1)}
    output_grid = conway.cull(input_grid)
    assert (0, 1) in output_grid


def test_new_cell_is_born_with_exact_3_neighbours():
    input_grid = {(0, 0), (0, 2), (1, 1)}
    output_grid = conway.spawn(input_grid)
    assert (0, 1) in output_grid


def test_to_expand_search_grid_one_step_outside_cells():
    input_grid = {(1, 0), (2, 1)}
    expected_grid = {(x, y) for x in range(0, 4) for y in range(-1, 3)}
    expended_grid = conway.expand_grid(input_grid)
    assert expected_grid == expended_grid


def test_that_a_blinker_iterates_positions():
    first_pos = {(-1, 0), (0, 0), (1, 0)}
    second_pos = {(0, -1), (0, 0), (0, 1)}
    assert conway.step(first_pos) == second_pos
    assert conway.step(second_pos) == first_pos


def test_toad_iterates_positions():
    first_pos = {(1, 1), (2, 1), (3, 1), (0, 0), (1, 0), (2, 0)}
    second_pos = {(0, 0), (0, 1), (1, -1), (3, 0), (3, 1), (2, 2)}
    assert conway.step(first_pos) == second_pos
    assert conway.step(second_pos) == first_pos


def test_that_a_block_does_not_change():
    block = {(0, 0), (0, 1), (1, 0), (1, 1)}
    assert conway.step(block) == block
