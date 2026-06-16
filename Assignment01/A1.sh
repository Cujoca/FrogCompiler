#!/bin/bash
# A1 SCRIPT

echo '--------------------------------------------'
echo '-      ALGONQUIN COLLEGE - COM - 26W       -'
echo '--------------------------------------------'
echo '-                                          -'
echo '-    ====                                  -'
echo '-   =                                      -'
echo '-  =       ==   = =  ==  = =   =   ==  ==  -'
echo '-   =     =  = = = = = = = =   ==  =  ==   -'
echo '-    ====  ==  = = = =   = === === =   ==  -'
echo '-                                          -'
echo '--------------------------------------------'
echo '-  [A1: Coder - Team: Paulo Sousa / God]   -'
echo '--------------------------------------------'

arg="${1:-../input/CODED.txt}"

cd "$(dirname "$0")/a1files/code"

rm -f ../input/CODED.txt ../input/RESTORED.txt

gcc Compilers.c Main1Coder.c Step1Coder.c -o compilers

sleep 1
./compilers 1 1 ../input/README.txt "$arg" > out.txt 2> err.txt

sleep 1
./compilers 1 0 "$arg" ../input/ORIGINAL.txt >> out.txt 2>> err.txt

sleep 1
ls out.txt err.txt
cat out.txt
