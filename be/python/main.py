import conway
import argparse


def cell_type(arg):
    try:
        x, y = arg.split(",")
        return int(x), int(y)
    except:
        raise argparse.ArgumentTypeError(f'Cell must be in format: "x,y", was "{arg}"')


def parse_arguments():
    parser = argparse.ArgumentParser()
    parser.add_argument("cell", nargs="+", type=cell_type)
    return parser.parse_args()


def to_cell_type(cell: tuple):
    return ",".join(map(str, cell))


def main():
    args = parse_arguments()
    grid = set(args.cell)
    new_grid = conway.step(grid)
    arg_formated_output = " ".join(map(to_cell_type, new_grid)) 
    print(arg_formated_output)


if __name__ == "__main__":
    main()

# conway.step()
