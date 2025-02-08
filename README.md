## Verification

This feature allows verbose output to track each step in the algorithm. The logs are printed on standard output in the following format:

```
k = 5
N 0
N 1
...
E 3 4
E 4 0
e 4 0
...
e 4 1
E 4 2
e 4 2
...
n 5
...
```

### Key:
- `N x`: Node `x` was added to the graph.
- `n x`: Node `x` was removed from the graph.
- `E x y`: Edge added between nodes `x` and `y`.
- `e x y`: Edge removed between nodes `x` and `y`.

## Steps to run
Create log file:
`make clean && make && ./out/a.out 6 >> <log_file>`

## Visualization
To facilitate visual representation of the generated graphs, the log output can be saved to a file and processed using the Python script `log_plot.py`.

### Dependencies
Install the required dependencies using pip:

```
pip install -r requirements.txt
```

### Usage
Run the script with the following command:

```
log_plot.py -l <log_file> -o <output_image>
```

This constructs the graphs generated at all stages of the algorithm. The script provides a way where users can navigate through the generated graphs using the up or down arrow keys, with the corresponding graphs saved as images to the specified output path.


Contributors: Anand Hegde, R. B. Sandeep, and P. Shashank.
