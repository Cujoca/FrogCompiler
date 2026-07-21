#!/bin/bash
# A4 SCRIPT
echo '------------------------------------------------'
echo '-        ALGONQUIN COLLEGE - COM - 26S         -'
echo '------------------------------------------------'
echo '-                                              -'
echo '-     ====                                     -'
echo '-    =                                         -'
echo '-   =       ==   = =  ==  = =   =   ==  ==     -'
echo '-    =     =  = = = = = = =   ==  =  ==      -'
echo '-     ====  ==  = = = =   = === === =    ==    -'
echo '-                                              -'
echo '------------------------------------------------'
echo '-[A4: Parser - Andrei Cojocaru / Leo Paquette] -'
echo '------------------------------------------------'

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
CODE_DIR="$SCRIPT_DIR/../code"
INPUT_DIR="$SCRIPT_DIR/../input"
OUTPUT_DIR="$SCRIPT_DIR/../output"

# Parameter is the plaintext Frog source file (in INPUT_DIR) to encode and parse.
# Defaults to the Frog sample program if none is given.
# Set the src file to FrogHello.txt/FrogControlFlow.txt/FrogFunctions.txt for valid input and FrogErrors.txt for invalid input.
src="${1:-FrogHello.txt}"
coded="$INPUT_DIR/CODED.txt"

gcc "$CODE_DIR/compilers.c" "$CODE_DIR/main1coder.c" "$CODE_DIR/step1coder.c" "$CODE_DIR/main2reader.c" "$CODE_DIR/step2reader.c" "$CODE_DIR/main3scanner.c" "$CODE_DIR/step3scanner.c" "$CODE_DIR/main4parser.c" "$CODE_DIR/step4parser.c" -o "$CODE_DIR/compilers"

"$CODE_DIR/compilers" 1 1 "$INPUT_DIR/$src" "$coded"

"$CODE_DIR/compilers" 4 "$coded" > "$OUTPUT_DIR/out.txt" 2> "$OUTPUT_DIR/err.txt"

ls -l "$OUTPUT_DIR/out.txt" "$OUTPUT_DIR/err.txt"
cat "$OUTPUT_DIR/out.txt"
