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
# ECHO "[PARSER SCRIPT ..........................]"
# ECHO "                                         "
*/


/*
************************************************************
* File name: Parser.h
* Compiler: MS Visual Studio 2022
* Course: CST 8152 � Compilers, Lab Section: [011, 012]
* Assignment: A32.
* Date: May 01 2023
* Professor: Paulo Sousa
* Purpose: This file is the main header for Parser (.h)
************************************************************
*/

#ifndef PARSER_H_
#define PARSER_H_

/* Inclusion section */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif
#ifndef READER_H_
#include "Reader.h"
#endif
#ifndef SCANNER_H_
#include "Scanner.h"
#endif

/* Global vars */
static Token			lookahead;
extern BufferPointer	stringLiteralTable;
extern frog_int		line;
extern Token			tokenizer(frog_void);
extern frog_str		keywordTable[KWT_SIZE];

#define LANG_WRTE		"print("
#define LANG_READ		"input("
#define LANG_MAIN		"main("

/* Keyword token attribute codes - the value of each MUST match the index
 * of the corresponding keyword in Step3Scanner.h's keywordTable, since
 * funcKEY() sets codeType to that index directly. */
enum KEYWORDS {
	NO_ATTR = -1,
	KW_tadpole,	// 0
	KW_lilypad,	// 1
	KW_croak,	// 2
	KW_if,		// 3
	KW_then,	// 4
	KW_else,	// 5
	KW_hop,		// 6
	KW_do,		// 7
	KW_leap,	// 8
	KW_ribbit	// 9
};

/* TO_DO: Define the number of BNF rules */
#define NUM_BNF_RULES 34

/* Parser */
typedef struct parserData {
	frog_int parsHistogram[NUM_BNF_RULES];	/* Number of BNF Statements */
} ParserData, * pParsData;

/* Number of errors */
extern frog_int numParserErrors;

/* Scanner data */
extern ParserData psData;

/* Function definitions */
frog_void startParser();
frog_void matchToken(frog_int, frog_int);
frog_void syncErrorHandler(frog_int, frog_int);
frog_void printError();
frog_void printBNFData(ParserData psData);

/* List of BNF statements */
enum BNF_RULES {
	BNF_error,										/*  0: Error token */
	BNF_comment,									/*  1 */
	BNF_varDeclaration,								/*  2 */
	BNF_optionalStatements,							/*  3 */
	BNF_outputStatement,							/*  4 */
	BNF_outputVariableList,							/*  5 */
	BNF_program,									/*  6 */
	BNF_statement,									/*  7 */
	BNF_statements,									/*  8 */
	BNF_statementsPrime,							/*  9 */
	BNF_optParams,									/* 10 */
	BNF_returnStatement,							/* 11 */
	BNF_paramList,									/* 12 */
	BNF_paramListPrime,								/* 13 */
	BNF_assignOrExprStatement,						/* 14 */
	BNF_expression,									/* 15 */
	BNF_notStatement,								/* 16 */
	BNF_doWhileStatement,							/* 17 */
	BNF_andExpr,									/* 18 */
	BNF_relExpr,									/* 19 */
	BNF_addExpr,									/* 20 */
	BNF_mulExpr,									/* 21 */
	BNF_unary,										/* 22 */
	BNF_ifStatement,								/* 23 */
	BNF_optElse,									/* 24 */
	BNF_whileStatement,								/* 25 */
	BNF_inputStatement,								/* 26 */
	BNF_functionDefs,								/* 27 */
	BNF_functionDef,								/* 28 */
	BNF_call,										/* 29 */
	BNF_callStatement,								/* 30 */
	BNF_argList,									/* 31 */
	BNF_argListPrime,								/* 32 */
	BNF_optReturnValue								/* 33 */
};


/* TO_DO: Define the list of keywords */
static frog_str BNFStrTable[NUM_BNF_RULES] = {
	"BNF_error",
	"BNF_comment",
	"BNF_varDeclaration",
	"BNF_optionalStatements",
	"BNF_outputStatement",
	"BNF_outputVariableList",
	"BNF_program",
	"BNF_statement",
	"BNF_statements",
	"BNF_statementsPrime",
	"BNF_optParams",
	"BNF_returnStatement",
	"BNF_paramList",
	"BNF_paramListPrime",
	"BNF_assignOrExprStatement",
	"BNF_expression",
	"BNF_notStatement",
	"BNF_doWhileStatement",
	"BNF_andExpr",
	"BNF_relExpr",
	"BNF_addExpr",
	"BNF_mulExpr",
	"BNF_unary",
	"BNF_ifStatement",
	"BNF_optElse",
	"BNF_whileStatement",
	"BNF_inputStatement",
	"BNF_functionDefs",
	"BNF_functionDef",
	"BNF_call",
	"BNF_callStatement",
	"BNF_argList",
	"BNF_argListPrime",
	"BNF_optReturnValue"
};

/* TO_DO: Place ALL non-terminal function declarations */
frog_void comment();
frog_void varDeclaration();
frog_void optionalStatements();
frog_void outputStatement();
frog_void outputVariableList();
frog_void program();
frog_void statement();
frog_void statements();
frog_void statementsPrime();
frog_void optParams();
frog_void paramList();
frog_void paramListPrime();
frog_void assignOrExprStatement();
frog_void andExpr();
frog_void relExpr();
frog_void addExpr();
frog_void mulExpr();
frog_void unary();
frog_void ifStatement();
frog_void optElse();
frog_void whileStatement();
frog_void expression();
frog_void notStatement();
frog_void doWhileStatement();
frog_void inputStatement();
frog_void functionDefs();
frog_void functionDef();
frog_void call();
frog_void callStatement();
frog_void argList();
frog_void argListPrime();
frog_void returnStatement();
frog_void optReturnValue();

#endif
