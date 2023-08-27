This repository contains the codes to run simulations in

Nakata S, Masumi A, and Toya G. (in prep.) Computational modelling of prestige-biased social learning: Differences between models with first-order cues and second-order cues.


Description of files:


"main.c", "prestigebias.c" and "prestigebias.h" contain codes of simulation described in the Results section. To run the simulation, the codes needs inputs of parameters as command-line arguments: p_bias, mutation_prob, mutation_interval, TIME, TRANSIENT, SEED. In the paper, we set mutation_interval is equal to 1. All parameter combinations reported in the paper.

"mt19937ar.c"and "mt19937ar.h" contain codes of pseudorandom number generator.

"Makefie" contains the codes for compiling the simulation codes with gcc by "make" command.


Execution:

At the command line, execute "make" command to compile the simulation codes. Then executing the executable file with inputs of parameters mentioned above as command-line arguments.

