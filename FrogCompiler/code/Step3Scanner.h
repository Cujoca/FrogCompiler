/*
************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Spring, 2026
* Author: Andrei Cojocaru and Leo Paquette
* Professor: Paulo Soussa
************************************************************
#
# ECHO "=---------------------------------------="
# ECHO "|  COMPILERS - ALGONQUIN COLLEGE (S26)  |"
# ECHO "=---------------------------------------="
# ECHO "     -------------------------------	Â”
# ECHO "	 |        o  o   o  o          |	Â”
# ECHO "	 |        |\/ \^/ \/|          |	Â”
# ECHO "	 |        |,-------.|          |	Â”
# ECHO "	 |      ,-.(|)   (|),-.        |	Â”
# ECHO "	 |      \_*._ ' '_.* _/        |	Â”
# ECHO "	 |       /`-.`--' .-'\         |	Â”
# ECHO "	 |  ,--./    `---'    \,--.    |	Â”
# ECHO "	 |  \   |(  )     (  )|   /    |	Â”
# ECHO "	 |   \  | ||       || |  /     |	Â”
# ECHO "	 |    \ | /|\     /|\ | /      |	Â”
# ECHO "	 |    /  \-._     _,-/  \      |	Â”
# ECHO "	 |   //| \  `---'  // |\       |	Â”
# ECHO "	 |  /,-.,-.\       /,-.,-.\    |	Â”
# ECHO "	 |  o   o   o      o   o    o  |	Â”
# ECHO "	 |                             |	Â”
# ECHO "	 |  F       R       O       G  |	Â”
# ECHO "	 -------------------------------    Â”
# ECHO "                                         "
# ECHO "[SCANNER SCRIPT ........................]"
# ECHO "                                         "
*/

/*
************************************************************
* File name: Scanner.h
* Compiler: MS Visual Studio 2022
* Course: CST 8152 ï¿½ Compilers, Lab Section: [011, 012]
* Assignment: A22, A32.
* Date: May 01 2024
* Purpose: This file is the main header for Scanner (.h)
* Function list: (...).
*************************************************************/

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef READER_H_
#include "Step2Reader.h"
#endif

#ifndef SCANNER_H_
#define SCANNER_H_

#ifndef NULL
#include <_null.h> /* NULL pointer constant is defined there */
#endif

/*#pragma warning(1:4001) */	/*to enforce C89 type comments  - to make //comments an warning */

/*#pragma warning(error:4001)*/	/* to enforce C89 comments - to make // comments an error */

/* Constants */
#define VID_LEN 20  /* variable identifier length */
#define ERR_LEN 40  /* error message length */
#define NUM_LEN 5   /* maximum number of digits for IL */

#define RTE_CODE 1  /* Value for run-time error */

/* TO_DO: Define the number of tokens */
#define NUM_TOKENS 21

/* TO_DO: Define Token codes - Create your token classes */
enum TOKENS {
	ERR_T,		/*  0: Error token */
	MNID_T,		/*  1: Method name identifier token (start: '(') */
	INL_T,		/*  2: Integer literal token */
	FPL_T,		/*  3: Floating-point (real) literal token */
	STR_T,		/*  4: String literal token */
	VID_T,		/*  5: Variable identifier token */
	LPR_T,		/*  6: Left parenthesis token */
	RPR_T,		/*  7: Right parenthesis token */
	LBR_T,		/*  8: Left brace token */
	RBR_T,		/*  9: Right brace token */
	KW_T,		/* 10: Keyword token */
	EOS_T,		/* 11: End of statement (semicolon) */
	ARI_OP_T,	/* 12: Arithmetic operator token (+ - * /) */
	REL_OP_T,	/* 13: Relational operator token (== != > <) */
	LOG_OP_T,	/* 14: Logical operator token (&& || !) */
	ASN_T,		/* 15: Assignment operator token (=) */
	RTE_T,		/* 16: Run-time error token */
	SEOF_T,		/* 17: Source end-of-file token */
	CMT_T,		/* 18: Comment token */
	COM_T,		/* 19: Comma token (,) */
	CHR_T		/* 20: Character literal token (e.g. 'Z') */
};

/* TO_DO: Define the list of keywords */
static frog_str tokenStrTable[NUM_TOKENS] = {
	"ERR_T",
	"MNID_T",
	"INL_T",
	"FPL_T",
	"STR_T",
	"VID_T",
	"LPR_T",
	"RPR_T",
	"LBR_T",
	"RBR_T",
	"KW_T",
	"EOS_T",
	"ARI_OP_T",
	"REL_OP_T",
	"LOG_OP_T",
	"ASN_T",
	"RTE_T",
	"SEOF_T",
	"CMT_T",
	"COM_T",
	"CHR_T"
};

/* TO_DO: Operators token attributes */
typedef enum ArithmeticOperators { OP_ADD, OP_SUB, OP_MUL, OP_DIV } AriOperator;
typedef enum RelationalOperators { OP_EQ, OP_NE, OP_GT, OP_LT } RelOperator;
typedef enum LogicalOperators { OP_AND, OP_OR, OP_NOT } LogOperator;
typedef enum SourceEndOfFile { SEOF_0, SEOF_255 } EofOperator;

/* TO_DO: Data structures for declaring the token and its attributes */
typedef union TokenAttribute {
	frog_int codeType;      /* integer attributes accessor */
	AriOperator arithmeticOperator;		/* arithmetic operator attribute code */
	RelOperator relationalOperator;		/* relational operator attribute code */
	LogOperator logicalOperator;		/* logical operator attribute code */
	EofOperator seofType;				/* source-end-of-file attribute code */
	frog_int intValue;				/* integer literal attribute (value) */
	frog_int keywordIndex;			/* keyword index in the keyword table */
	frog_int contentString;			/* string literal offset from the beginning of the string literal buffer (stringLiteralTable->content) */
	frog_float floatValue;				/* floating-point literal attribute (value) */
	frog_char idLexeme[VID_LEN + 1];	/* variable identifier token attribute */
	frog_char errLexeme[ERR_LEN + 1];	/* error token attribite */
	frog_char charValue;				/* character literal attribute (value), e.g. 'Z' */
} TokenAttribute;

/* TO_DO: Should be used if no symbol table is implemented */
typedef struct idAttibutes {
	frog_byte flags;			/* Flags information */
	union {
		frog_int intValue;				/* Integer value */
		frog_float floatValue;			/* Float value */
		frog_str stringContent;		/* String value */
	} values;
} IdAttibutes;

/* Token declaration */
typedef struct Token {
	frog_int code;				/* token code */
	TokenAttribute attribute;	/* token attribute */
	IdAttibutes   idAttribute;	/* not used in this scanner implementation - for further use */
} Token;

/* Scanner */
typedef struct scannerData {
	frog_int scanHistogram[NUM_TOKENS];	/* Statistics of chars */
} ScannerData, * pScanData;

///////////////////////////////////////////////////////////////////////////////////////////////////////

/* TO_DO: Define lexeme FIXED classes */
/* EOF definitions */
#define EOS_CHR '\0'	// CH00
#define EOF_CHR (frog_char)0xFF	// CH01
#define UND_CHR '_'		// CH02
#define AMP_CHR '&'		// CH03
#define QUT_CHR '\"'	// CH04
#define HST_CHR '#'		// CH05
#define TAB_CHR '\t'	// CH06
#define SPC_CHR ' '		// CH07
#define NWL_CHR '\n'	// CH08
#define SCL_CHR ';'		// CH09
#define LPR_CHR '('		// CH10
#define RPR_CHR ')'		// CH11
#define LBR_CHR '{'		// CH12
#define RBR_CHR '}'		// CH13
#define DOT_CHR '.'		// CH14
#define PLS_CHR '+'		// CH15
#define MIN_CHR '-'		// CH16
#define MUL_CHR '*'		// CH17
#define DIV_CHR '/'		// CH18
#define GRT_CHR '>'		// CH19
#define LSS_CHR '<'		// CH20
#define EQL_CHR '='		// CH21
#define NOT_CHR '!'		// CH22
#define PIP_CHR '|'		// CH23
#define COM_CHR ','		// CH24
#define QUO_CHR '\''	// CH25 (char literal delimiter, e.g. 'Z')

/*  Special case tokens processed separately one by one in the token-driven part of the scanner:
 *  LPR_T, RPR_T, LBR_T, RBR_T, COM_T, EOS_T, SEOF_T, operator tokens (ARI_OP_T, REL_OP_T, LOG_OP_T, ASN_T),
 *  CHR_T (a single-quoted character literal, e.g. 'Z' - handled directly, not through the DFA below)
 *  and special chars used for tokens include _, & and " */


/* TO_DO: Error states and illegal state */
#define ESNR	8		/* Error state with no retract */
#define ESWR	9		/* Error state with retract */
#define FS		16		/* Illegal state (sentinel - must stay >= NUM_STATES) */

 /* TO_DO: State transition table definition */
#define NUM_STATES		16
#define CHAR_CLASSES	10

/* TO_DO: Transition table - type of states defined in separate table */
static frog_int transitionTable[NUM_STATES][CHAR_CLASSES] = {
/*    [A-z],[0-9],    _,    (,   \", SEOF,    *, other,    .,    /
	   L(0), D(1), U(2), M(3), Q(4), E(5), A(6),  O(7), P(8), S(9) */
	{     1,   10, ESNR, ESNR,    4, ESWR, ESNR, ESNR, ESNR, ESNR},	// S0: NOAS
	{     1,    1,    1,    2,	 3,    3,    3,    3,    3,    3},	// S1: NOAS (identifier body)
	{    FS,   FS,   FS,   FS,   FS,   FS,   FS,   FS,   FS,   FS},	// S2: ASNR (MNID)
	{    FS,   FS,   FS,   FS,   FS,   FS,   FS,   FS,   FS,   FS},	// S3: ASWR (KEY/VID)
	{     4,    4,    4,    4,    5, ESWR,    4,    4,    4,    4},	// S4: NOAS (string body)
	{    FS,   FS,   FS,   FS,   FS,   FS,   FS,   FS,   FS,   FS},	// S5: ASNR (SL)
	{     6,    6,    6,    6,    6, ESWR,   15,    6,    6,    6},	// S6: NOAS (comment body)
	{    FS,   FS,   FS,   FS,   FS,   FS,   FS,   FS,   FS,   FS},	// S7: ASNR (COM)
	{    FS,   FS,   FS,   FS,   FS,   FS,   FS,   FS,   FS,   FS},	// S8: ASNR (ES)
	{    FS,   FS,   FS,   FS,   FS,   FS,   FS,   FS,   FS,   FS},	// S9: ASWR (ER)
	{    11,   10,   11,   11,   11,   11,   11,   11,   12,   11},	// S10: NOAS (IL digit run)
	{    FS,   FS,   FS,   FS,   FS,   FS,   FS,   FS,   FS,   FS},	// S11: ASWR (IL)
	{  ESNR,   13, ESNR, ESNR, ESNR, ESWR, ESNR, ESNR, ESNR, ESNR},	// S12: NOAS (post '.', needs 1st fraction digit)
	{    14,   13,   14,   14,   14,   14,   14,   14,   14,   14},	// S13: NOAS (fraction digit run)
	{    FS,   FS,   FS,   FS,   FS,   FS,   FS,   FS,   FS,   FS},	// S14: ASWR (FPL)
	{     6,    6,    6,    6,    6, ESWR,   15,    6,    6,    7}	// S15: NOAS (comment body, saw '*', awaiting '/')
};

/* Define accepting states types */
#define NOFS	0		/* not accepting state */
#define FSNR	1		/* accepting state with no retract */
#define FSWR	2		/* accepting state with retract */

/* TO_DO: Define list of acceptable states */
static frog_int stateType[NUM_STATES] = {
	NOFS, /* 00 */
	NOFS, /* 01 */
	FSNR, /* 02 (MNID) - Methods */
	FSWR, /* 03 (KEY/VID) */
	NOFS, /* 04 */
	FSNR, /* 05 (SL) */
	NOFS, /* 06 */
	FSNR, /* 07 (COM) */
	FSNR, /* 08 (Err1 - no retract) */
	FSWR, /* 09 (Err2 - retract) */
	NOFS, /* 10 (IL digit run) */
	FSWR, /* 11 (IL) */
	NOFS, /* 12 (post '.', needs 1st fraction digit) */
	NOFS, /* 13 (fraction digit run) */
	FSWR, /* 14 (FPL) */
	NOFS  /* 15 (comment body, saw '*', awaiting '/') */
};

/*
-------------------------------------------------
TO_DO: Adjust your functions'definitions
-------------------------------------------------
*/

/* Static (local) function  prototypes */
frog_int			startScanner(BufferPointer psc_buf);
static frog_int	nextClass(frog_char c);					/* character class function */
static frog_int	nextState(frog_int, frog_char);		/* state machine function */
frog_void			printScannerData(ScannerData scData);
Token				tokenizer(frog_void);

/*
-------------------------------------------------
Automata definitions
-------------------------------------------------
*/

/* TO_DO: Pointer to function (of one char * argument) returning Token */
typedef Token(*PTR_ACCFUN)(frog_str lexeme);

/* Declare accepting states functions */
Token funcSL	(frog_str lexeme);
Token funcIL	(frog_str lexeme);
Token funcFPL	(frog_str lexeme);
Token funcID	(frog_str lexeme);
Token funcCMT   (frog_str lexeme);
Token funcKEY	(frog_str lexeme);
Token funcErr	(frog_str lexeme);

/* 
 * Accepting function (action) callback table (array) definition 
 * If you do not want to use the typedef, the equvalent declaration is:
 */

/* TO_DO: Define final state table */
static PTR_ACCFUN finalStateTable[NUM_STATES] = {
	NULL,		/* -    [00] */
	NULL,		/* -    [01] */
	funcID,		/* MNID	[02] */
	funcKEY,	/* KEY/VID [03] */
	NULL,		/* -    [04] */
	funcSL,		/* SL   [05] */
	NULL,		/* -    [06] */
	funcCMT,	/* COM  [07] */
	funcErr,	/* ERR1 [08] */
	funcErr,	/* ERR2 [09] */
	NULL,		/* -    [10] */
	funcIL,		/* IL   [11] */
	NULL,		/* -    [12] */
	NULL,		/* -    [13] */
	funcFPL,	/* FPL  [14] */
	NULL		/* -    [15] */
};

/*
-------------------------------------------------
Language keywords
-------------------------------------------------
*/

/* TO_DO: Define the number of Keywords from the language */
#define KWT_SIZE 11

/* TO_DO: Define the list of keywords */
static frog_str keywordTable[KWT_SIZE] = {
	"tadpole",	/* KW00 - integer type (was: int) */
	"lilypad",	/* KW01 - real/float type (was: real) */
	"croak",	/* KW02 - string type (was: string) */
	"if",		/* KW03 */
	"then",		/* KW04 */
	"else",		/* KW05 */
	"hop",		/* KW06 - loop keyword (was: while) */
	"do",		/* KW07 */
	"leap",		/* KW08 - return keyword (was: return) */
	"ribbit",	/* KW09 - char type */
	"bullfrog"	/* KW10 - boolean type (was: bool) */
};

/* NEW SECTION: About indentation */

/*
 * Scanner attributes to be used (ex: including: intendation data
 */

#define INDENT TAB_CHR  /* Tabulation */

/* TO_DO: Should be used if no symbol table is implemented */
typedef struct languageAttributes {
	frog_char indentationCharType;
	frog_int indentationCurrentPos;
	/* TO_DO: Include any extra attribute to be used in your scanner (OPTIONAL and FREE) */
} LanguageAttributes;

/* Number of errors */
extern frog_int numScannerErrors;

/* Scanner data */
extern ScannerData scData;

#endif
