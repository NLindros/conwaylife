from fastapi import FastAPI
from fastapi.middleware.cors import CORSMiddleware
from typing import List
from pydantic import BaseModel
import conway


app = FastAPI()

origins = ["*"]

app.add_middleware(
    CORSMiddleware,
    allow_origins=origins,
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)


class Grid(BaseModel):
    cells: List[List[int]]


def serialize_grid(grid: conway.Grid) -> Grid:
    return {"cells": list(map(list, grid))}


def deserialize_grid(grid: Grid) -> conway.Grid:
    return set(map(tuple, grid.cells))


@app.get("/")
async def home():
    return "Hello"


@app.post("/")
async def step(grid: Grid):
    next_grid = conway.step(deserialize_grid(grid))
    return serialize_grid(next_grid)
