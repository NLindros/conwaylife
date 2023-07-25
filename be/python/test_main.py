import subprocess
from pathlib import Path

ROOT_DIR = Path(__file__).parent


def test_that_output_can_be_used_as_input():
    grid = "2,3 3,3 1,3"
    input_args = grid.split(" ")
    fut = ROOT_DIR / "main.py"
    result = subprocess.run(["python", "main.py", *input_args], stdout=subprocess.PIPE)
    output = result.stdout.decode("utf-8").strip()
    assert output != ""
    subprocess.run(["python", "main.py", *output.split(" ")])
