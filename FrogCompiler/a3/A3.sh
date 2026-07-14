#!/bin/bash
# A3 SCRIPT
echo '------------------------------------------------'
echo '-        ALGONQUIN COLLEGE - COM - 26S         -'
echo '------------------------------------------------'
echo '-                                              -'
echo '-     ====                                     -'
echo '-    =                                         -'
echo '-   =       ==   = =  ==  = =   =   ==  ==     -'
echo '-    =     =  = = = = = = = =   ==  =  ==      -'
echo '-     ====  ==  = = = =   = === === =    ==    -'
echo '-                                              -'
echo '------------------------------------------------'
echo '-[A3: Scanner - Andrei Cojocaru / Leo Paquette]-'
echo '------------------------------------------------'

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
CODE_DIR="$SCRIPT_DIR/../code"
INPUT_DIR="$SCRIPT_DIR/../input"
OUTPUT_DIR="$SCRIPT_DIR/../output"

src="${1:-FrogHello.txt}"
coded="$INPUT_DIR/CODED.txt"

gcc "$CODE_DIR/compilers.c" "$CODE_DIR/main1coder.c" "$CODE_DIR/step1coder.c" "$CODE_DIR/main2reader.c" "$CODE_DIR/step2reader.c" "$CODE_DIR/main3scanner.c" "$CODE_DIR/step3scanner.c" -o "$CODE_DIR/compilers"

"$CODE_DIR/compilers" 1 1 "$INPUT_DIR/$src" "$coded"

"$CODE_DIR/compilers" 3 "$coded" > "$OUTPUT_DIR/out.txt" 2> "$OUTPUT_DIR/err.txt"

ls -la "$OUTPUT_DIR/out.txt" "$OUTPUT_DIR/err.txt"
cat "$OUTPUT_DIR/out.txt"
