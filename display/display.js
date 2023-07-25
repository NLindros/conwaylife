let isRunning = false
const initCells = [[0, -1], [0, 0], [0, 1]];
let grid = { cells: initCells };

const cellId = (x, y) => `${x},${y}`;

let lifeTime = 500;
const lifeTimeSlider = document.querySelector("#life-time");
const lifeTimeValue = document.querySelector("#life-time-value");
lifeTimeSlider.addEventListener("input", event => {
    lifeTime = Number(event.target.value);
    lifeTimeValue.innerText = event.target.value;
});
lifeTimeSlider.value = lifeTime;

const toogleCell = (event) => {
    if (isRunning == true)
        return
    const cell = event.target.id.split(',').map(Number);
    const [cell_x, cell_y] = cell
    const cellIndex = grid.cells.findIndex(([x, y]) => { return (x == cell_x) && (y == cell_y) });
    if (cellIndex >= 0) {
        grid.cells = grid.cells.filter((item, index) => index != cellIndex);
        event.target.classList.remove('active');
    } else {
        grid.cells = [...grid.cells, cell];
        event.target.classList.add('active');
    }
}


const resetButtonClick = () => {
    grid.cells = initCells;
    clearBoard();
    drawBoard(grid);
}

const createGrid = () => {
    const gridTable = document.querySelector('.grid-base');
    let row, cell;
    const gridSize = 15;
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
    const cells = document.getElementsByClassName('cell');
    for (let cell of cells) {
        cell.classList.remove("active");
    }
}

const drawBoard = grid => {
    grid.cells.forEach(cell =>
        document.getElementById(cellId(...cell)).classList.add("active")
    )
}

const runButtonClick = () => {
    const btn = document.querySelector('.buttons .run');
    isRunning = !isRunning;
    const btnText = isRunning ? "Pause" : "Run";
    btn.innerText = btnText;
    lifeStep()
}

const lifeStep = async () => {
    if (isRunning == true) {
        grid = await getNextGrid(grid)
        clearBoard();
        drawBoard(grid);
        setTimeout(lifeStep, lifeTime)
    }
}

const getNextGrid = async (data) => {
    const url = "http://127.0.0.1:8000"
    const response = await fetch(url, {
        method: "POST",
        headers: {
            'Content-Type': 'application/json'
        },
        body: JSON.stringify(data),
    });
    return response.json();
}

createGrid();
drawBoard(grid);
