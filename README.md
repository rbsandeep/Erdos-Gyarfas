# Cilk based parallel implementation

This program is a parallel implementation of the algorithm in the following paper
to prove that Erdős–Gyárfás conjecture is true for graphs without long induced paths.

Steps to run:
Please refer to https://cilk.mit.edu/download/ to install cilk.

Inside `lib.cpp`, change the path of `cilk.h` based on your installation.

`make clean && make && ./out/a.out <k>`
