# Overview

Here you can see two implementations (one serial and one parallel) of an algorithm
to validate Erdős–Gyárfás conjecture on P_k-free graphs (graphs without any induced copies of a path on k vertices):
every graph with minimum degree at least 3 has a cycle with length a power of 2.
The algorithm can be found at this link: http://arxiv.org/abs/2410.22842

# Special Graphs Generation

Additionally, this branch contains special graphs that do not have 4 to 8 cycles but contain 16 cycles. The modified algorithm successfully generated such graphs and reproduced four graphs from the paper that contains [Markstroem Graph](http://abel.math.umu.se/~klasm/Uppsatser/cycex.pdf).

These graphs a predominantly **24-node cubic graphs**, with one graph being **28-node cubic graph**, whose adj-matrix representaions are given in the `./special` directory

# Steps to run

1. Clone the git repository, and checkout `special-graphs` branch

```
git clone https://github.com/rbsandeep/Erdos-Gyarfas.git
cd Erdos-Gyarfas
git checkout special-graphs
```

2. Steps to compile the single threaded modified program:

```
cd cpp
make clean && make
```

3. Run the modified algorithm that generates **24-node cubic P18-free** graphs

```
./out/a.out 18
```

**NOTE**

```
To test for different number of nodes (N) and different Pk-free values (P):
    1. Update value of N in ./cpp/lib.cpp, cap_nodes variable (and re-compile)
    2. Update value of P as command line argument: ./out/a.out <P>

The graphs will be printed to stdout in adjacency matrix format, one after the other
```

# Current Analysis

The logs corresponding to **24-node cubic P-18 free** graphs are present in the file `./special/24-node-p18-free-logs.txt` and the line numbers corresponding to the first occurances of the targeted Graphs given by Markstroem are present in `./special/24-node-p18-free-capture.txt`.

The graphs can be verified using `graph_test.py` python file, usage is self-explanatory

# Contributors:

Anand Hegde, R. B. Sandeep, and P. Shashank.
