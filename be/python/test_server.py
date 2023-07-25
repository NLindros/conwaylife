import requests
import json
import pytest
import server


LOCAL_HOST = "http://127.0.0.1:8000"


def test_serialize_grid():
    grid = {(1, 2), (-3, 4)}
    serialized = server.serialize_grid(grid)
    assert serialized["cells"] == [[1, 2], [-3, 4]]


def test_deserialize_grid():
    cells = [[2, 1], [-1, 0]]
    grid = server.Grid(cells=cells)
    result = server.deserialize_grid(grid)
    assert result == {(2, 1), (-1, 0)}


def test_that_reponse_can_be_used_as_new_input():
    init_grid = {"cells": [[-1, 0], [0, 0], [1, 0]]}
    mid_response = requests.post(LOCAL_HOST, json=init_grid)
    assert mid_response.json() == {"cells": [[0, 1], [0, -1], [0, 0]]}
    final_response = requests.post(LOCAL_HOST, json=mid_response.json())
    assert sorted(final_response.json()["cells"]) == sorted(init_grid["cells"])
