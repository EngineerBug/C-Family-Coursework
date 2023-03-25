# C-Family Coursework - student number - exam number

### Compiling and Executing

There are three ways to compile the code in this directory.
- Manually use gcc to compile and link every file.
- Use the 'make' command in each dir to compile all the files in that dir.
- Use './compile.sh x y' to compile and run all programs in the project.
    - Use the command 'chmod +x compile.sh' to be able to execute the script
    - x: the number of players in the byn/test and byn/main
    - y: the number of games to play in the byn/main

In addition the command 'valgrind --leak-check=yes ./executable_name' will check for memory leaks.

### Reading

The project is split into the following structure.

Files are organised into the order from most seperated from the user to least (i.e. the user would call Makefile, which calls byn.c and single.c which both call beggar.c ect. Folders are organised by the order they were completed

C-CARD-GAME
- pig
    - pig.h (contains .h files)
    - pig.c (contains code for translating one english word into piglatin)
    - test_pig.c (executes tests on code in pig.c)
    - piglatin.c (executes a user-input version of pig.c)
    - Makefile (used to compile and link the programs)
- riffle
    - riffle.h (contains .h files)
    - riffle.c (contains all the code required to riffle shuffle an array)
    - demo_shuffle.c (executes tests on code in riffle.c)
    - quality.c (executes a 1..30 shuffles on a deck of 50 cards and writes the quality to quality.txt)
    - Makefile (used to compile and link the programs)
    - quality.txt (stores the conclusion of quality.c)
- byn
    - beggar.h (contains structs and .h files)
    - queue.c (contains a linked-list style queue structure)
    - beggar.c (contains code to simulate one game of byn)
    - single.c (executes one game of byn)
    - byn.c (executes y games of byn to calculate the average number of turns with 1-x players)
    - Makefile (used to compile and link the programs)
- compile.sh (used ot compile and run all the code in one go)
- (quality.txt) (the output from quality.c when run by compile.sh)