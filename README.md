For each input integer k >=3, the program checks whether there is a P_k-free, but having an induced P_{k-1}, 
graph with minimum degree at least 3 such that
every cycle of length a power of 2 has length at least 16 - i.e., there are no 4-cycle and no 8-cycle.
The refer: http://arxiv.org/abs/2410.22842

There are two implementations - sequential and parallel.

Steps to compile:
`make clean && make`

Usage: ./out/a.out <k>

Contributors: Anand Hegde, R. B. Sandeep, and P. Shashank.
