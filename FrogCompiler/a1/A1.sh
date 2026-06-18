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

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
arg="${1:-$SCRIPT_DIR/../input/CODED.txt}"

cd "$SCRIPT_DIR/../code"

rm -f ../input/CODED.txt ../input/RESTORED.txt

gcc Compilers.c Main1Coder.c Step1Coder.c Main2Reader.c Step2Reader.c -o compilers

sleep 1
./compilers 1 1 ../input/README.txt "$arg" > ../output/out.txt 2> ../output/err.txt

sleep 1
./compilers 1 0 "$arg" ../input/ORIGINAL.txt >> ../output/out.txt 2>> ../output/err.txt

sleep 1
ls ../output/out.txt ../output/err.txt
cat ../output/out.txt
