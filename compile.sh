#!/usr/bin/bash

# chmod +x compile.sh

# check if the arguments are valid
if [ $# -ne 2 ] || [ $1 -lt 2 ] || [ $2 -lt 100 ] ; then
    echo "Usage: ./compile.sh [number of players >= 2] [number of trials >= 100]"
    exit
fi

# compile the programs
echo "Compiling pig..."
gcc ./pig/test_pig.c -o ./pig/test
gcc ./pig/piglatin.c -o ./pig/main

echo "Compiling riffle..."
gcc ./riffle/demo_shuffle.c -o ./riffle/test
gcc ./riffle/quality.c -o ./riffle/main

echo "Compiling byn..."
gcc ./byn/single.c -o ./byn/test
gcc ./byn/byn.c -o ./byn/main

echo "Compiling Success!"

# run the programs
echo "Running pig..."
./pig/test
./pig/main

echo "Running riffle..."
./riffle/test
./riffle/main

echo "Running byn..."
./byn/test $1
./byn/main $1 $2