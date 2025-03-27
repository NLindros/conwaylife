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


def serialize_grid(grid) -> Grid:
    return {"cells": list(map(list, grid))}


def deserialize_grid(grid: Grid):
    return set(map(tuple, grid.cells))


@app.get("/")
async def home():
    return "Hello"


@app.post("/")
async def step(grid: Grid):
    unpacked_grid = deserialize_grid(grid)
    print(unpacked_grid)
    next_grid = conway.step(unpacked_grid)
    payload = serialize_grid(next_grid)
    print("Payload:")
    print(payload)
    return payload
