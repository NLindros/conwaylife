const gridSize = 15;
let isRunning = false
const initCells = [[0, -1], [0, 0], [0, 1]];
let grid = { cells: initCells };
const gridTable = document.querySelector('.grid-base');

const scenarioElements = document.querySelector('.scenarios');

const cellId = (x, y) => `${x},${y}`;

let lifeTime = 500;
const lifeTimeSlider = document.querySelector("#life-time");
const lifeTimeValue = document.querySelector("#life-time-value");
lifeTimeSlider.addEventListener("input", event => {
    lifeTime = Number(event.currentTarget.value);
    lifeTimeValue.innerText = event.currentTarget.value;
});
lifeTimeSlider.value = lifeTime;

function isCellAmoungCells(cell, cells) {
    const [cell_x, cell_y] = cell;
    return cells.findIndex(([x, y]) => { return (x == cell_x) && (y == cell_y); });
}

const toogleCell = (event) => {
    if (isRunning == true)
        return
    const cell = event.currentTarget.id.split(',').map(Number);
    const cellIndex = isCellAmoungCells(cell, grid.cells);
    if (cellIndex >= 0) {
        grid.cells = grid.cells.filter((item, index) => index != cellIndex);
        event.currentTarget.classList.remove('active');
    } else {
        grid.cells = [...grid.cells, cell].sort(sort2DByRows).sort(sort2DByCols);
        event.currentTarget.classList.add('active');
    }
}

const clampToOne = val => { return val === 0 ? 0 : val > 0 ? 1 : -1 }

const sort2DByCols = (a, b) => { return clampToOne(a[0] - b[0]) };
const sort2DByRows = (a, b) => { return clampToOne(a[1] - b[1]) };

const saveButtonClick = () => {
    const now = new Date()
    const timeString = `Save: ${now.getHours()}:${now.getMinutes()}:${now.getSeconds()}`
    saveScenario(grid.cells, timeString)
}

const createMiniGrid = (cells) => {
    const scenarioTable = document.createElement('table');
    let row;
    for (let y = -gridSize; y < gridSize; y++) {
        row = document.createElement('tr');
        for (let x = -gridSize; x < gridSize; x++) {
            cellElement = document.createElement('td');
            cellElement.classList.add('cell');
            if (isCellAmoungCells([x, y], cells) >= 0) {
                cellElement.classList.add('active')
            }
            row.appendChild(cellElement)
        }
        scenarioTable.appendChild(row);
    }
    return scenarioTable;
}

const createGrid = () => {
    let row, cell;
    for (let y = -gridSize; y < gridSize; y++) {
        row = document.createElement('tr');
        for (let x = -gridSize; x < gridSize; x++) {
            cell = document.createElement('td');
            cell.classList.add('cell')
            cell.setAttribute('id', cellId(x, y));
            cell.addEventListener("click", toogleCell)
            row.appendChild(cell);
        }
        gridTable.appendChild(row);
    }
}

const clearBoard = () => {
    const cells = gridTable.getElementsByClassName('cell');
    for (let cell of cells) {
        cell.classList.remove("active");
    }
}

const drawBoard = cells => {
    cells.forEach(cell => {
        const cellElement = document.getElementById(cellId(...cell));
        if (cellElement) {
            cellElement.classList.add("active")
        }
    })
}

const collectPairs = flatCells => {
    return flatCells
        .split(",")
        .map(Number)
        .reduce((result, val, index, array) =>
            index % 2 === 0 ? [...result, array.slice(index, index + 2)] : result
            , [])
}

const loadScenario = (event) => {
    const scenario = event.currentTarget;
    grid.cells = collectPairs(scenario.dataset.cells);
    clearBoard();
    drawBoard(grid.cells);
}

const stepLife = async () => {
    grid.cells = await getNextGrid(grid.cells);
    clearBoard();
    drawBoard(grid.cells);
}

const stepButtonClick = async () => {
    await stepLife();
}

const runButtonClick = () => {
    const btn = document.querySelector('.buttons .run');
    isRunning = !isRunning;
    btn.innerText = isRunning ? "Pause" : "Run";
    if (isRunning) {
        saveLastRun(grid.cells)
        runLife()
    }
}

const clearButtonClick = () => {
    grid.cells = [];
    clearBoard();
}

const randomButtonClick = () => {
    const newGrid = []
    for (let y = -gridSize; y < gridSize; y++) {
        for (let x = -gridSize; x < gridSize; x++) {
            let active = Math.random() >= 0.7;
            if (active) {
                newGrid.push([x, y])
            }
        }
    }
    grid.cells = newGrid;
    clearBoard();
    drawBoard(grid.cells);
}

const runLife = async () => {
    if (isRunning == true) {
        await stepLife();
        setTimeout(runLife, lifeTime);
    }
}

const getNextGrid = async (cells) => {
    if (cells.length === 0) {
        return []
    }
    const url = "http://127.0.0.1:8000"
    const response = await fetch(url, {
        method: "POST",
        headers: {
            'Content-Type': 'application/json'
        },
        body: JSON.stringify({ cells: cells }),
    });
    const newGrid = await response.json();
    return newGrid.cells;
}

const saveScenario = (cells, title) => {
    const scenario = document.createElement('div')
    const titleElement = document.createElement('h3');
    titleElement.innerText = title
    scenario.appendChild(titleElement)

    scenario.addEventListener('click', loadScenario)
    scenario.classList.add('scenario')
    scenario.setAttribute('data-cells', cells)
    scenario.appendChild(createMiniGrid(cells))
    scenarioElements.appendChild(scenario)
}

const saveLastRun = (cells) => {
    const lastRunScenario = document.querySelector('.last-run')
    lastRunScenario.removeChild(lastRunScenario.lastChild)
    lastRunScenario.appendChild(createMiniGrid(cells))
    lastRunScenario.addEventListener('click', loadScenario)
    lastRunScenario.setAttribute('data-cells', cells)
}

createGrid();
drawBoard(grid.cells);
saveLastRun(initCells)
saveScenario([[-10, -8], [-9, -8], [-8, -8], [-8, -9], [-9, -10]], 'Glider');
saveScenario([
    [0, -5], [0, -4], [-1, -3], [1, -3], [0, -2], [0, -1],
    [0, 0], [0, 1], [-1, 2], [1, 2], [0, 3], [0, 4]
], 'Pentadecathlon');

