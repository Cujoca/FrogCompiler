/*
************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Summer, 2026
* Author: Leo Paquette and Andrei Cojocaru
* Professors: Paulo Sousa
************************************************************
#
# ECHO "=---------------------------------------="
# ECHO "|  COMPILERS - ALGONQUIN COLLEGE (S26)  |"
# ECHO "=---------------------------------------="
# ECHO "     -------------------------------	 "
# ECHO "	 |        o  o   o  o          |	 "
# ECHO "	 |        |\/ \^/ \/|          |	 "
# ECHO "	 |        |,-------.|          |	 "
# ECHO "	 |      ,-.(|)   (|),-.        |	 "
# ECHO "	 |      \_*._ ' '_.* _/        |	 "
# ECHO "	 |       /`-.`--' .-'\         |	 "
# ECHO "	 |  ,--./    `---'    \,--.    |	 "
# ECHO "	 |  \   |(  )     (  )|   /    |	 "
# ECHO "	 |   \  | ||       || |  /     |	 "
# ECHO "	 |    \ | /|\     /|\ | /      |	 "
# ECHO "	 |    /  \-._     _,-/  \      |	 "
# ECHO "	 |   //| \  `---'  // |\       |	 "
# ECHO "	 |  /,-.,-.\       /,-.,-.\    |	 "
# ECHO "	 |  o   o   o      o   o    o  |	 "
# ECHO "	 |                             |	 "
# ECHO "	 |  F       R       O       G  |	 "
# ECHO "	 -------------------------------     "
# ECHO "                                         "
# ECHO "[WRITER SCRIPT ..........................]"
# ECHO "                                         "
*/

/*
************************************************************
* File name: Writer.h
* Compiler: MS Visual Studio 2022
* Course: CST 8152 � Compilers, Lab Section: [011, 012]
* Assignment: A12.
* Date: Jan 01 2025
* Professor: Paulo Sousa
* Purpose: This file is the main header for Reader (.h)
************************************************************
*/

/*
 *.............................................................................
 * MAIN ADVICE:
 * Please check the "TODO" labels to develop your activity.
 *.............................................................................
 */

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef READER_H_
#include "Step2Reader.h"
#endif

#ifndef SCANNER_H_
#include "Step3Scanner.h"
#endif

#ifndef PARSER_H_
#include "Step4Parser.h"
#endif

#ifndef WRITER_H_
#define WRITER_H_

/*
 * NOTE: The Writer drives the same tokenizer()/Buffer machinery the Parser
 * (Step4Parser.c) uses instead of re-parsing the decoded source as raw text.
 * It walks the token stream with its own grammar-mirroring functions that
 * compute real values instead of just validating syntax.
 */

#define MAX_VARS 100
#define MAX_FUNCS 20
#define MAX_PARAMS 8

#define EOS '\0'
#define ZERO 0.0
#define STREMPTY ""

#define TRUE "true"
#define FALSE "false"

typedef enum { NUMERIC, STRING, BOOLEAN, CHAR } VarType;

typedef struct {
    frog_char name[VID_LEN + 1];
    VarType type;
    union {
        frog_doub num_value;
        frog_char str_value[256];
        frog_int bool_value; // For BOOLEAN type (1 for true, 0 for false)
        frog_char char_value; // For CHAR type
    } value;
} Variable;

/* An expression result is just a Variable that hasn't (necessarily) been
 * registered under a name in the variable table. */
typedef Variable Value;

/* A registered function definition: its parameter names and where its body
 * starts in the source buffer (right after the opening '{'), so runFunction()
 * can seek the buffer there and re-run it on every call. */
typedef struct {
    frog_char name[VID_LEN + 1];
    frog_int paramCount;
    frog_char paramNames[MAX_PARAMS][VID_LEN + 1];
    frog_int bodyPos;
} FuncEntry;

/* Entry point: registers all function definitions, then runs "main(".
 * Takes the already-loaded source Buffer (same one passed to startScanner())
 * so it can seek/rewind the token stream around function bodies. */
frog_void runProgram(BufferPointer buf);

#endif
