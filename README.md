# Erdős-Gyárfás conjecture on graphs without long induced paths

Here you can see two implementation of an algorithm
to validate Erdős–Gyárfás conjecture on P_k-free graphs (graphs without any induced copies of a path on k vertices):
every graph with minimum degree at least 3 has a cycle with length a power of 2.
The algorithm can be found at this link: http://arxiv.org/abs/2410.22842

To prove that the conjecture is true for P_t-free graphs: run the program with a command line argument k, for 3 <= k <= t.
If there is a counterexample of the required kind, the program will print the details.

Steps to compile:
`make clean && make`

Usage: `./out/a.out <k>`

The above steps will build the serial implementation. For cilk based parallel implementation, please see the branch [cilk](https://github.com/rbsandeep/Erdos-Gyarfas/tree/cilk).

Contributors: Anand Hegde, R. B. Sandeep, and P. Shashank.
