#!/bin/bash
# A2 SCRIPT

echo '-----------------------------------------------'
echo '-        ALGONQUIN COLLEGE - COM - 26S        -'
echo '-----------------------------------------------'
echo '-                                             -'
echo '-     ====                                    -'
echo '-    =                                        -'
echo '-   =       ==   = =  ==  = =   =   ==  ==    -'
echo '-    =     =  = = = = = = = =   ==  =  ==     -'
echo '-     ====  ==  = = = =   = === === =    ==   -'
echo '-                                             -'
echo '-----------------------------------------------'
echo '-[A2: Reader - Andrei Cojocaru / Leo Paquette]-'
echo '-----------------------------------------------'

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
arg="${1:-$SCRIPT_DIR/../input/CODED.txt}"

cd "$SCRIPT_DIR/../code"

gcc Compilers.c Main1Coder.c Step1Coder.c Main2Reader.c Step2Reader.c -o compilers

sleep 1
./compilers 1 1 ../input/README.txt "$arg"

sleep 1
./compilers 2 "$arg" > ../output/out.txt 2> ../output/err.txt

sleep 1
ls ../output/out.txt ../output/err.txt
cat ../output/out.txt
