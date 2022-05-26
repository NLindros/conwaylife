

const cellId = (x, y) => `${x}-${y}`

const createGrid = () => {
    const gridTable = document.querySelector('.grid-base');
    let row, cell;
    const gridSize = 15;
    for (y = -gridSize; y < gridSize; y++) {
        row = document.createElement('tr');
        for (x = -gridSize; x < gridSize; x++) {
            cell = document.createElement('td');
            cell.setAttribute('id', cellId(x, y));
            row.appendChild(cell);
        }
        gridTable.appendChild(row);
    }
}

const markActive = cell => {
    document.getElementById(cellId(...cell)).classList.add("active")
}

createGrid();

[[2, 3], [3, 3]].forEach(cell => markActive(cell))


