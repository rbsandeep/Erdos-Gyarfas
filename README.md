Here you can see two implementations (one serial and one parallel) of an algorithm 
to validate Erdős–Gyárfás conjecture on P_k-free graphs (graphs without any induced copies of a path on k vertices): 
every graph with minimum degree at least 3 has a cycle with length a power of 2.
The algorithm can be found at this link: 

To prove that the conjecture is true for P_t-free graphs: run the program with a command line argument k, for 3 <= k <= t.
If there is a counterexample of the required kind, the program will print the details.

Steps to compile:
`make clean && make`

Usage: ./out/a.out <t>
