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
* File name: Parser.c
* Compiler: MS Visual Studio 2022
* Course: CST 8152 – Compilers, Lab Section: [011, 012]
* Assignment: A32.
* Date: May 01 2023
* Purpose: This file contains all functionalities from Parser.
* Function list: (...).
************************************************************
*/

/* TO_DO: Adjust the function header */

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef SCANNER_H_
#include "Step3Scanner.h"
#endif

#ifndef PARSER_H_
#include "Step4Parser.h"
#endif

/* Parser data */
ParserData psData; /* BNF statistics */
frog_int numParserErrors; /* Number of syntax errors reported by the parser */
static frog_bool sawMainFunction = FROG_FALSE; /* set by functionDef() when it sees "main(" */

/* Forward declarations for static helpers used before their definition below */
static frog_void matchType();
static frog_bool tokenMatches(frog_int tokenCode, frog_int tokenAttribute);

/*
************************************************************
 * Process Parser
 ***********************************************************
 */
/* TO_DO: This is the function to start the parser - check your program definition */

frog_void startParser() {
	/* TO_DO: Initialize Parser data */
	frog_int i = 0;
	for (i = 0; i < NUM_BNF_RULES; i++) {
		psData.parsHistogram[i] = 0;
	}
	/* Proceed parser */
	lookahead = tokenizer();
	if (lookahead.code != SEOF_T) {
		program();
	}
	matchToken(SEOF_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Source file parsed");
}


/*
 ************************************************************
 * Token Matches
 * Shared match-check used by both matchToken() and syncErrorHandler():
 * a KW_T token must match on code AND keyword attribute (codeType), any
 * other token code only needs to match on code.
 ***********************************************************
 */
static frog_bool tokenMatches(frog_int tokenCode, frog_int tokenAttribute) {
	if (lookahead.code == KW_T && lookahead.attribute.codeType != tokenAttribute)
		return FROG_FALSE;
	return lookahead.code == tokenCode;
}

/*
 ************************************************************
 * Match Token
 ***********************************************************
 */
/* TO_DO: This is the main code for match - check your definition */
frog_void matchToken(frog_int tokenCode, frog_int tokenAttribute) {
	frog_int matchFlag = tokenMatches(tokenCode, tokenAttribute);
	if (matchFlag && lookahead.code == SEOF_T)
		return;
	if (matchFlag) {
		lookahead = tokenizer();
		while (lookahead.code == ERR_T) {
			printError();
			lookahead = tokenizer();
			numParserErrors++;
		}
	}
	else
		syncErrorHandler(tokenCode, tokenAttribute);
}

/*
 ************************************************************
 * Syncronize Error Handler
 ***********************************************************
 */
/* TO_DO: This is the function to handler error - adjust basically datatypes */
frog_void syncErrorHandler(frog_int syncTokenCode, frog_int syncTokenAttribute) {
	printError();
	numParserErrors++;
	while (!tokenMatches(syncTokenCode, syncTokenAttribute)) {
		if (lookahead.code == SEOF_T)
			exit(numParserErrors);
		lookahead = tokenizer();
	}
	if (lookahead.code != SEOF_T)
		lookahead = tokenizer();
}

/*
 ************************************************************
 * Print Error
 ***********************************************************
 */
/* TO_DO: This is the function to error printing - adjust basically datatypes */
frog_void printError() {
	Token t = lookahead;
	psData.parsHistogram[BNF_error]++;
	printf("%s%s%3d\n", STR_LANGNAME, ": Syntax error:  Line:", line);
	printf("*****  Token code:%3d Attribute: ", t.code);
	switch (t.code) {
	case ERR_T:
		printf("*ERROR*: %s\n", t.attribute.errLexeme);
		break;
	case SEOF_T:
		printf("SEOF_T\t\t%d\t\n", t.attribute.seofType);
		break;
	case MNID_T:
		printf("MNID_T:\t\t%s\t\n", t.attribute.idLexeme);
		break;
	case STR_T:
		printf("STR_T: %s\n", readerGetContent(stringLiteralTable, t.attribute.contentString));
		break;
	case CHR_T:
		printf("CHR_T: '%c'\n", t.attribute.charValue);
		break;
	case KW_T:
		printf("KW_T: %s\n", keywordTable[t.attribute.codeType]);
		break;
	case LPR_T:
		printf("LPR_T\n");
		break;
	case RPR_T:
		printf("RPR_T\n");
		break;
	case LBR_T:
		printf("LBR_T\n");
		break;
	case RBR_T:
		printf("RBR_T\n");
		break;
	case COM_T:
		printf("COM_T\n");
		break;
	case CMT_T:
		printf("CMT_T\n");
		break;
	case VID_T:
		printf("VID_T:\t\t%s\n", t.attribute.idLexeme);
		break;
	case INL_T:
		printf("INL_T:\t\t%d\n", t.attribute.intValue);
		break;
	case FPL_T:
		printf("FPL_T:\t\t%f\n", t.attribute.floatValue);
		break;
	case ARI_OP_T:
		printf("ARI_OP_T\n");
		break;
	case REL_OP_T:
		printf("REL_OP_T\n");
		break;
	case LOG_OP_T:
		printf("LOG_OP_T\n");
		break;
	case ASN_T:
		printf("ASN_T\n");
		break;
	case EOS_T:
		printf("NA\n");
		break;
	default:
		printf("%s%s%d\n", STR_LANGNAME, ": Scanner error: invalid token code: ", t.code);
	}
}

/*
 ************************************************************
 * Program statement
 * BNF: <program> -> <opt_comment> <functionDefs>
 * FIRST(<program>) = { CMT_T, KW_T (tadpole/lilypad/croak/ribbit) }
 * Checks (after the fact) that at least one of the parsed function
 * definitions was literally named "main(" - not a grammar rule, just
 * a lightweight sanity check, same spirit as the original hardcoded
 * single-main design this replaced.
 ***********************************************************
 */
frog_void program() {
	psData.parsHistogram[BNF_program]++;
	while (lookahead.code == CMT_T) {
		comment();
	}
	sawMainFunction = FROG_FALSE;
	functionDefs();
	if (!sawMainFunction) {
		printError();
		numParserErrors++;
	}
	printf("%s%s\n", STR_LANGNAME, ": Program parsed");
}

/*
 ************************************************************
 * functionDefs
 * BNF: <functionDefs> -> <opt_comment> <functionDef> <functionDefs> | e
 * FIRST(<functionDefs>) = { e, CMT_T, KW_T (tadpole/lilypad/croak/ribbit) }
 * Zero or more function definitions, in any order/position - "main"
 * is not structurally special, it's just whichever <functionDef>
 * happens to be named "main(". A leading comment is tolerated before
 * every function, not just the first (that one's handled by program()).
 ***********************************************************
 */
frog_void functionDefs() {
	psData.parsHistogram[BNF_functionDefs]++;
	while (lookahead.code == CMT_T) {
		comment();
	}
	if (lookahead.code == KW_T &&
		(lookahead.attribute.codeType == KW_tadpole ||
		 lookahead.attribute.codeType == KW_lilypad ||
		 lookahead.attribute.codeType == KW_croak ||
		 lookahead.attribute.codeType == KW_ribbit)) {
		functionDef();
		functionDefs();
	}
	printf("%s%s\n", STR_LANGNAME, ": Function definitions parsed");
}

/*
 ************************************************************
 * functionDef
 * BNF: <functionDef> -> <type> MNID_T <optParams> ) { <opt_statements> }
 * FIRST(<functionDef>) = { KW_T (tadpole/lilypad/croak/ribbit) }
 * Note: MNID_T's lexeme already includes the trailing '(' (see funcID),
 * so there is no separate LPR_T to match after it.
 ***********************************************************
 */
frog_void functionDef() {
	psData.parsHistogram[BNF_functionDef]++;
	matchType();
	if (lookahead.code == MNID_T && strncmp(lookahead.attribute.idLexeme, LANG_MAIN, strlen(LANG_MAIN)) == 0) {
		sawMainFunction = FROG_TRUE;
	}
	matchToken(MNID_T, NO_ATTR);
	optParams();
	matchToken(RPR_T, NO_ATTR);
	matchToken(LBR_T, NO_ATTR);
	optionalStatements();
	matchToken(RBR_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Function definition parsed");
}

/*
 ************************************************************
 * comment
 * BNF: comment
 * FIRST(<comment>)= {CMT_T}.
 ***********************************************************
 */
frog_void comment() {
	psData.parsHistogram[BNF_comment]++;
	matchToken(CMT_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Comment parsed");
}


/*
 ************************************************************
 * optParams
 * BNF: <optParams> -> <paramList> | e
 * FIRST(<optParams>) = { e, KW_T (tadpole), KW_T (lilypad), KW_T (croak), KW_T (ribbit) }
 ***********************************************************
 */
frog_void optParams() {
	psData.parsHistogram[BNF_optParams]++;
	while (lookahead.code == CMT_T) {
		comment();
	}
	if (lookahead.code == KW_T &&
		(lookahead.attribute.codeType == KW_tadpole ||
		 lookahead.attribute.codeType == KW_lilypad ||
		 lookahead.attribute.codeType == KW_croak ||
		 lookahead.attribute.codeType == KW_ribbit)) {
		paramList();
	}
	printf("%s%s\n", STR_LANGNAME, ": Optional param list parsed");
}

/*
 ************************************************************
 * matchType
 * Consumes a KW_T token whose attribute is tadpole/lilypad/croak/ribbit.
 * Callers must only invoke this when they already know (via FIRST)
 * that the lookahead is a type keyword.
 ***********************************************************
 */
static frog_void matchType() {
	if (lookahead.code == KW_T &&
		(lookahead.attribute.codeType == KW_tadpole ||
		 lookahead.attribute.codeType == KW_lilypad ||
		 lookahead.attribute.codeType == KW_croak ||
		 lookahead.attribute.codeType == KW_ribbit)) {
		matchToken(KW_T, lookahead.attribute.codeType);
	}
	else {
		printError();
		numParserErrors++;
	}
}

/*
 ************************************************************
 * isStatementStart
 * Checks whether the lookahead can begin a <statement>:
 * a declaration (tadpole/lilypad/croak/ribbit), an identifier-led
 * assignment/expression (VID_T), a call statement (MNID_T: print(/input(/
 * a user-defined function), a unary-not expression (! - LOG_OP_T with OP_NOT),
 * a do-while loop (do), a pre-test while loop (hop), an if statement (if),
 * or a return (leap).
 ***********************************************************
 */
static frog_bool isStatementStart() {
	if (lookahead.code == VID_T || lookahead.code == MNID_T)
		return FROG_TRUE;
	if (lookahead.code == LOG_OP_T && lookahead.attribute.logicalOperator == OP_NOT)
		return FROG_TRUE;
	if (lookahead.code == KW_T &&
		(lookahead.attribute.codeType == KW_tadpole ||
		 lookahead.attribute.codeType == KW_lilypad ||
		 lookahead.attribute.codeType == KW_croak ||
		 lookahead.attribute.codeType == KW_ribbit ||
		 lookahead.attribute.codeType == KW_do ||
		 lookahead.attribute.codeType == KW_hop ||
		 lookahead.attribute.codeType == KW_if ||
		 lookahead.attribute.codeType == KW_leap))
		return FROG_TRUE;
	return FROG_FALSE;
}

/*
 ************************************************************
 * isExpressionStart
 * Checks whether the lookahead can begin an <expression>, i.e. FIRST(<unary>):
 * !, unary minus, VID_T, INL_T, FPL_T, STR_T, CHR_T, ( , or a call (MNID_T).
 * Used by argList() to decide between an argument and the empty production.
 ***********************************************************
 */
static frog_bool isExpressionStart() {
	if (lookahead.code == VID_T || lookahead.code == INL_T || lookahead.code == FPL_T ||
		lookahead.code == STR_T || lookahead.code == CHR_T || lookahead.code == LPR_T || lookahead.code == MNID_T)
		return FROG_TRUE;
	if (lookahead.code == LOG_OP_T && lookahead.attribute.logicalOperator == OP_NOT)
		return FROG_TRUE;
	if (lookahead.code == ARI_OP_T && lookahead.attribute.arithmeticOperator == OP_SUB)
		return FROG_TRUE;
	return FROG_FALSE;
}

/*
 ************************************************************
 * Expression grammar (precedence climbing, low to high):
 *   expression -> || -> && -> relational -> +/- -> star/slash -> unary
 * BNF:
 *   <expression> -> <andExpr> <expressionTail>
 *   <expressionTail> -> || <andExpr> <expressionTail> | e
 *   <andExpr>    -> <relExpr> <andExprTail>
 *   <andExprTail>-> && <relExpr> <andExprTail> | e
 *   <relExpr>    -> <addExpr> <relExprTail>
 *   <relExprTail>-> (> | < | == | !=) <addExpr> | e     (single, non-chaining)
 *   <addExpr>    -> <mulExpr> <addExprTail>
 *   <addExprTail>-> (+ | -) <mulExpr> <addExprTail> | e
 *   <mulExpr>    -> <unary> <mulExprTail>
 *   <mulExprTail>-> (* | /) <unary> <mulExprTail> | e
 *   <unary>      -> ! <unary> | - <unary> | VID_T | INL_T | FPL_T | STR_T | CHR_T | ( <expression> )
 *
 * Each level parses the next-higher-precedence level first, then loops
 * on its own operators via a static "Tail" helper. The Tail helpers are
 * not BNF-tracked non-terminals of their own (like matchType()/isStatementStart(),
 * they're just the repetition mechanism) - they're also what lets
 * assignOrExprStatement() resume the climb after already consuming the
 * leading VID_T itself (to check for '=' first).
 ***********************************************************
 */
static frog_void mulExprTail() {
	while (lookahead.code == ARI_OP_T &&
		(lookahead.attribute.arithmeticOperator == OP_MUL || lookahead.attribute.arithmeticOperator == OP_DIV)) {
		matchToken(ARI_OP_T, NO_ATTR);
		unary();
	}
}

static frog_void addExprTail() {
	while (lookahead.code == ARI_OP_T &&
		(lookahead.attribute.arithmeticOperator == OP_ADD || lookahead.attribute.arithmeticOperator == OP_SUB)) {
		matchToken(ARI_OP_T, NO_ATTR);
		mulExpr();
	}
}

static frog_void relExprTail() {
	if (lookahead.code == REL_OP_T) {
		matchToken(REL_OP_T, NO_ATTR);
		addExpr();
	}
}

static frog_void andExprTail() {
	while (lookahead.code == LOG_OP_T && lookahead.attribute.logicalOperator == OP_AND) {
		matchToken(LOG_OP_T, NO_ATTR);
		relExpr();
	}
}

static frog_void expressionTail() {
	while (lookahead.code == LOG_OP_T && lookahead.attribute.logicalOperator == OP_OR) {
		matchToken(LOG_OP_T, NO_ATTR);
		andExpr();
	}
}

/*
 * unary -> ! <unary> | - <unary> | VID_T | INL_T | FPL_T | STR_T | CHR_T | <call> | ( <expression> )
 * FIRST(<unary>) = { LOG_OP_T (!), ARI_OP_T (-), VID_T, INL_T, FPL_T, STR_T, CHR_T, MNID_T, LPR_T }
 */
frog_void unary() {
	psData.parsHistogram[BNF_unary]++;
	switch (lookahead.code) {
	case LOG_OP_T:
		if (lookahead.attribute.logicalOperator == OP_NOT) {
			matchToken(LOG_OP_T, NO_ATTR);
			unary();
		}
		else {
			printError();
			numParserErrors++;
		}
		break;
	case ARI_OP_T:
		if (lookahead.attribute.arithmeticOperator == OP_SUB) {
			matchToken(ARI_OP_T, NO_ATTR);
			unary();
		}
		else {
			printError();
			numParserErrors++;
		}
		break;
	case VID_T:
		matchToken(VID_T, NO_ATTR);
		break;
	case INL_T:
		matchToken(INL_T, NO_ATTR);
		break;
	case FPL_T:
		matchToken(FPL_T, NO_ATTR);
		break;
	case STR_T:
		matchToken(STR_T, NO_ATTR);
		break;
	case CHR_T:
		matchToken(CHR_T, NO_ATTR);
		break;
	case MNID_T:
		call();
		break;
	case LPR_T:
		matchToken(LPR_T, NO_ATTR);
		expression();
		matchToken(RPR_T, NO_ATTR);
		break;
	default:
		printError();
		numParserErrors++;
	}
	printf("%s%s\n", STR_LANGNAME, ": Unary parsed");
}

/*
 ************************************************************
 * call
 * BNF: <call> -> MNID_T <argList> )
 * FIRST(<call>) = { MNID_T }
 * A function call used as a <unary> atom (to get its return value)
 * or as the shared core of callStatement() (call for side effect only).
 * Note: MNID_T's lexeme already includes the trailing '(' (see funcID),
 * so there is no separate LPR_T to match after it.
 ***********************************************************
 */
frog_void call() {
	psData.parsHistogram[BNF_call]++;
	matchToken(MNID_T, NO_ATTR);
	argList();
	matchToken(RPR_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Call parsed");
}

/*
 ************************************************************
 * argList
 * BNF: <argList> -> <expression> <argListPrime> | e
 * FIRST(<argList>) = { e } U FIRST(<expression>)
 ***********************************************************
 */
frog_void argList() {
	psData.parsHistogram[BNF_argList]++;
	if (isExpressionStart()) {
		expression();
		argListPrime();
	}
	printf("%s%s\n", STR_LANGNAME, ": Argument list parsed");
}

/*
 ************************************************************
 * argListPrime
 * BNF: <argListPrime> -> , <expression> <argListPrime> | e
 * FIRST(<argListPrime>) = { e, COM_T (,) }
 ***********************************************************
 */
frog_void argListPrime() {
	psData.parsHistogram[BNF_argListPrime]++;
	if (lookahead.code == COM_T) {
		matchToken(COM_T, NO_ATTR);
		expression();
		argListPrime();
	}
	printf("%s%s\n", STR_LANGNAME, ": Argument list prime parsed");
}

/* mulExpr -> <unary> <mulExprTail> */
frog_void mulExpr() {
	psData.parsHistogram[BNF_mulExpr]++;
	unary();
	mulExprTail();
	printf("%s%s\n", STR_LANGNAME, ": Mul expression parsed");
}

/* addExpr -> <mulExpr> <addExprTail> */
frog_void addExpr() {
	psData.parsHistogram[BNF_addExpr]++;
	mulExpr();
	addExprTail();
	printf("%s%s\n", STR_LANGNAME, ": Add expression parsed");
}

/* relExpr -> <addExpr> <relExprTail> */
frog_void relExpr() {
	psData.parsHistogram[BNF_relExpr]++;
	addExpr();
	relExprTail();
	printf("%s%s\n", STR_LANGNAME, ": Relational expression parsed");
}

/* andExpr -> <relExpr> <andExprTail> */
frog_void andExpr() {
	psData.parsHistogram[BNF_andExpr]++;
	relExpr();
	andExprTail();
	printf("%s%s\n", STR_LANGNAME, ": And expression parsed");
}

/*
 * expression -> <andExpr> <expressionTail>
 * FIRST(<expression>) = FIRST(<unary>) = { LOG_OP_T (!), VID_T, INL_T, FPL_T, LPR_T }
 * Top-level entry point - used as a bare expression statement, a loop
 * condition (hop <expression>), an if-condition, and inside parens.
 */
frog_void expression() {
	psData.parsHistogram[BNF_expression]++;
	andExpr();
	expressionTail();
	printf("%s%s\n", STR_LANGNAME, ": Expression parsed");
}

/*
 ************************************************************
 * paramList
 * BNF: <paramList> -> <type> VID_T <paramListPrime>
 * FIRST(<paramList>) = { KW_T (tadpole), KW_T (lilypad), KW_T (croak), KW_T (ribbit) }
 ***********************************************************
 */
frog_void paramList() {
	psData.parsHistogram[BNF_paramList]++;
	matchType();
	matchToken(VID_T, NO_ATTR);
	paramListPrime();
	printf("%s%s\n", STR_LANGNAME, ": Param list parsed");
}

/*
 ************************************************************
 * paramListPrime
 * BNF: <paramListPrime> -> , <type> VID_T <paramListPrime> | e
 * FIRST(<paramListPrime>) = { e, COM_T (,) }
 ***********************************************************
 */
frog_void paramListPrime() {
	psData.parsHistogram[BNF_paramListPrime]++;
	if (lookahead.code == COM_T) {
		matchToken(COM_T, NO_ATTR);
		matchType();
		matchToken(VID_T, NO_ATTR);
		paramListPrime();
	}
	printf("%s%s\n", STR_LANGNAME, ": Param list prime parsed");
}

/*
 ************************************************************
 * varDeclaration
 * BNF: <varDeclaration> -> <type> VID_T <optInit> ;
 *      <optInit> -> = <expression> | e
 * FIRST(<varDeclaration>) = { KW_T (tadpole), KW_T (lilypad), KW_T (croak), KW_T (ribbit) }
 * A variable declaration statement, with an optional initializer
 * (e.g. "tadpole count;" or "tadpole count = 0;").
 * Called by statement() when the lookahead is a type keyword.
 ***********************************************************
 */
frog_void varDeclaration() {
	psData.parsHistogram[BNF_varDeclaration]++;
	matchType();
	matchToken(VID_T, NO_ATTR);
	if (lookahead.code == ASN_T) {
		matchToken(ASN_T, NO_ATTR);
		expression();
	}
	matchToken(EOS_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Variable declaration parsed");
}

/*
 ************************************************************
 * Optional statement
 * BNF: <opt_statements> -> <statements> | e
 * FIRST(<opt_statements>) = { e, VID_T, MNID_T, KW_T (tadpole), KW_T (lilypad),
 *				KW_T (croak), KW_T (if), KW_T (hop), KW_T (do), KW_T (leap) }
 ***********************************************************
 */
frog_void optionalStatements() {
	psData.parsHistogram[BNF_optionalStatements]++;
	while (lookahead.code == CMT_T) {
		comment();
	}
	if (isStatementStart()) {
		statements();
	}
	printf("%s%s\n", STR_LANGNAME, ": Optional statements parsed");
}

/*
 ************************************************************
 * Statements
 * BNF: <statements> -> <statement><statementsPrime>
 * Single alternative (no FIRST-set branching needed) - statement()
 * is only ever called once FIRST(statement) has already been checked
 * by the caller (e.g. optionalStatements()).
 ***********************************************************
 */
frog_void statements() {
	psData.parsHistogram[BNF_statements]++;
	statement();
	statementsPrime();
	printf("%s%s\n", STR_LANGNAME, ": Statements parsed");
}

/*
 ************************************************************
 * Statements Prime
 * BNF: <statementsPrime> -> <opt_comment> <statement><statementsPrime> | e
 * FIRST(<statementsPrime>) = { e, VID_T, MNID_T, KW_T (tadpole), KW_T (lilypad),
 *		KW_T (croak), KW_T (if), KW_T (hop), KW_T (do), KW_T (leap) }
 ***********************************************************
 */
frog_void statementsPrime() {
	psData.parsHistogram[BNF_statementsPrime]++;
	while (lookahead.code == CMT_T) {
		comment();
	}
	if (isStatementStart()) {
		statement();
		statementsPrime();
	}
	printf("%s%s\n", STR_LANGNAME, ": Statements prime parsed");
}

/*
 ************************************************************
 * OptionalReturnValue
 * BNF: <optReturnValue> -> <expression> | e
 * FIRST(<optReturnValue>) = { e } U FIRST(<expression>)
 * Any expression can be returned (a literal, a variable, a computed
 * expression, or a call), e.g. "leap x + y;" or "leap add(1, 2);".
 ***********************************************************
 */
frog_void optReturnValue() {
	psData.parsHistogram[BNF_optReturnValue]++;
	if (isExpressionStart()) {
		expression();
	}
	printf("%s%s\n", STR_LANGNAME, ": Optional return value parsed");
}

/*
 ************************************************************
 * Return Statement
 * BNF: <returnStatement> -> leap <optReturnValue> ;
 * FIRST(<returnStatement>) = { KW_T (leap) }
 ***********************************************************
 */
frog_void returnStatement() {
	psData.parsHistogram[BNF_returnStatement]++;
	matchToken(KW_T, KW_leap);
	optReturnValue();
	matchToken(EOS_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Return statement parsed");
}

/*
 ************************************************************
 * assignOrExprStatement
 * BNF: <assignOrExprStatement> -> VID_T = <rhs> ; | VID_T <exprTail> ;
 * FIRST(<assignOrExprStatement>) = { VID_T }
 * Covers both a real assignment (count = 42;) and a bare expression
 * statement, including a plain unadorned variable reference (count;),
 * since <exprTail> allows the empty production.
 ***********************************************************
 */
frog_void assignOrExprStatement() {
	psData.parsHistogram[BNF_assignOrExprStatement]++;
	matchToken(VID_T, NO_ATTR);
	if (lookahead.code == ASN_T) {
		matchToken(ASN_T, NO_ATTR);
		expression();
	}
	else {
		/* The VID_T just consumed above IS the <unary> atom, so resume the
		 * precedence climb directly from the Tail helpers instead of calling
		 * expression() (which would try to parse a brand-new <unary>). */
		mulExprTail();
		addExprTail();
		relExprTail();
		andExprTail();
		expressionTail();
	}
	matchToken(EOS_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Assignment or expression statement parsed");
}

/*
 ************************************************************
 * notStatement
 * BNF: <notStatement> -> ! VID_T ;
 * FIRST(<notStatement>) = { LOG_OP_T (!) }
 ***********************************************************
 */
frog_void notStatement() {
	psData.parsHistogram[BNF_notStatement]++;
	matchToken(LOG_OP_T, NO_ATTR);
	matchToken(VID_T, NO_ATTR);
	matchToken(EOS_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Not statement parsed");
}

/*
 ************************************************************
 * doWhileStatement
 * BNF: <doWhileStatement> -> do { <opt_statements> } hop <expression> ;
 * FIRST(<doWhileStatement>) = { KW_T (do) }
 * A do-while loop: body runs first, then "hop <expr>" is the
 * loop-continuation condition (hop plays the role of "while").
 ***********************************************************
 */
frog_void doWhileStatement() {
	psData.parsHistogram[BNF_doWhileStatement]++;
	matchToken(KW_T, KW_do);
	matchToken(LBR_T, NO_ATTR);
	optionalStatements();
	matchToken(RBR_T, NO_ATTR);
	matchToken(KW_T, KW_hop);
	expression();
	matchToken(EOS_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Do-while statement parsed");
}

/*
 ************************************************************
 * whileStatement
 * BNF: <whileStatement> -> hop <expression> { <opt_statements> }
 * FIRST(<whileStatement>) = { KW_T (hop) }
 * A pre-test loop: reuses "hop" (the same keyword doWhileStatement()
 * uses as its trailing condition), disambiguated purely by position -
 * "do {...} hop expr;" is post-test, a bare leading "hop expr {...}" is pre-test.
 ***********************************************************
 */
frog_void whileStatement() {
	psData.parsHistogram[BNF_whileStatement]++;
	matchToken(KW_T, KW_hop);
	expression();
	matchToken(LBR_T, NO_ATTR);
	optionalStatements();
	matchToken(RBR_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": While statement parsed");
}

/*
 ************************************************************
 * optElse
 * BNF: <optElse> -> else { <opt_statements> } | e
 * FIRST(<optElse>) = { e, KW_T (else) }
 ***********************************************************
 */
frog_void optElse() {
	psData.parsHistogram[BNF_optElse]++;
	if (lookahead.code == KW_T && lookahead.attribute.codeType == KW_else) {
		matchToken(KW_T, KW_else);
		matchToken(LBR_T, NO_ATTR);
		optionalStatements();
		matchToken(RBR_T, NO_ATTR);
	}
	printf("%s%s\n", STR_LANGNAME, ": Optional else parsed");
}

/*
 ************************************************************
 * ifStatement
 * BNF: <ifStatement> -> if <expression> then { <opt_statements> } <optElse>
 * FIRST(<ifStatement>) = { KW_T (if) }
 ***********************************************************
 */
frog_void ifStatement() {
	psData.parsHistogram[BNF_ifStatement]++;
	matchToken(KW_T, KW_if);
	expression();
	matchToken(KW_T, KW_then);
	matchToken(LBR_T, NO_ATTR);
	optionalStatements();
	matchToken(RBR_T, NO_ATTR);
	optElse();
	printf("%s%s\n", STR_LANGNAME, ": If statement parsed");
}

/*
 ************************************************************
 * Single statement
 * BNF: <statement> -> <varDeclaration> | <returnStatement> | <doWhileStatement> |
 *	<whileStatement> | <ifStatement> | <assignOrExprStatement> |
 *	<notStatement> | <outputStatement>
 * FIRST(<statement>) = { KW_T (tadpole/lilypad/croak/ribbit/do/hop/if/leap), VID_T,
 *			LOG_OP_T (!), MNID_T (print(/input() }
 * Any recognized-but-unhandled keyword/call still consumes at least one
 * statement's worth of tokens via syncErrorHandler(), so a construct this
 * grammar doesn't support yet can't stall the statementsPrime() recursion.
 ***********************************************************
 */
frog_void statement() {
	psData.parsHistogram[BNF_statement]++;
	switch (lookahead.code) {
	case KW_T:
		switch (lookahead.attribute.codeType) {
		case KW_tadpole:
		case KW_lilypad:
		case KW_croak:
		case KW_ribbit:
			varDeclaration();
			break;
		case KW_leap:
			returnStatement();
			break;
		case KW_do:
			doWhileStatement();
			break;
		case KW_hop:
			whileStatement();
			break;
		case KW_if:
			ifStatement();
			break;
		default:
			syncErrorHandler(EOS_T, NO_ATTR);
		}
		break;
	case VID_T:
		assignOrExprStatement();
		break;
	case LOG_OP_T:
		if (lookahead.attribute.logicalOperator == OP_NOT) {
			notStatement();
		}
		else {
			syncErrorHandler(EOS_T, NO_ATTR);
		}
		break;
	case MNID_T:
		if (strncmp(lookahead.attribute.idLexeme, LANG_WRTE, strlen(LANG_WRTE)) == 0) {
			outputStatement();
		}
		else if (strncmp(lookahead.attribute.idLexeme, LANG_READ, strlen(LANG_READ)) == 0) {
			inputStatement();
		}
		else {
			callStatement();
		}
		break;
	default:
		syncErrorHandler(EOS_T, NO_ATTR);
	}
	printf("%s%s\n", STR_LANGNAME, ": Statement parsed");
}

/*
 ************************************************************
 * Output Statement
 * BNF: <output statement> -> print( <outputVariableList> ) ;
 * FIRST(<output statement>) = { MNID_T (print() }
 * Note: MNID_T's lexeme already includes the trailing '(' (see funcID),
 * so there is no separate LPR_T to match after it.
 ***********************************************************
 */
frog_void outputStatement() {
	psData.parsHistogram[BNF_outputStatement]++;
	matchToken(MNID_T, NO_ATTR);
	outputVariableList();
	matchToken(RPR_T, NO_ATTR);
	matchToken(EOS_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Output statement parsed");
}

/*
 ************************************************************
 * Output Variable List
 * BNF: <outputVariableList> -> STR_T | VID_T | e
 * FIRST(<outputVariableList>) = { STR_T, VID_T, e }
 * print(...) can print a string literal or a variable's value.
 ***********************************************************
 */
frog_void outputVariableList() {
	psData.parsHistogram[BNF_outputVariableList]++;
	switch (lookahead.code) {
	case STR_T:
		matchToken(STR_T, NO_ATTR);
		break;
	case VID_T:
		matchToken(VID_T, NO_ATTR);
		break;
	default:
		;
	}
	printf("%s%s\n", STR_LANGNAME, ": Output variable list parsed");
}

/*
 ************************************************************
 * Input Statement
 * BNF: <inputStatement> -> input( VID_T ) ;
 * FIRST(<inputStatement>) = { MNID_T (input() }
 * Unlike output, input reads into a variable, so the argument must be
 * a VID_T (an lvalue) - a string or numeric literal can't be read into.
 ***********************************************************
 */
frog_void inputStatement() {
	psData.parsHistogram[BNF_inputStatement]++;
	matchToken(MNID_T, NO_ATTR);
	matchToken(VID_T, NO_ATTR);
	matchToken(RPR_T, NO_ATTR);
	matchToken(EOS_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Input statement parsed");
}

/*
 ************************************************************
 * callStatement
 * BNF: <callStatement> -> <call> ;
 * FIRST(<callStatement>) = { MNID_T }
 * A user-defined function called as its own statement, result discarded
 * (any MNID_T that isn't print(/input(, which have their own dedicated
 * statement handling above).
 ***********************************************************
 */
frog_void callStatement() {
	psData.parsHistogram[BNF_callStatement]++;
	call();
	matchToken(EOS_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Call statement parsed");
}

/*
 ************************************************************
 * The function prints statistics of BNF rules
 * Param:
 *	- Parser data
 * Return:
 *	- Void (procedure)
 ***********************************************************
 */
/*
frog_void printBNFData(ParserData psData) {
}
*/
frog_void printBNFData(ParserData psData) {
	/* Print Parser statistics */
	printf("Statistics:\n");
	printf("----------------------------------\n");
	int cont = 0;
	for (cont = 0; cont < NUM_BNF_RULES; cont++) {
		if (psData.parsHistogram[cont] > 0)
			printf("%s%s%s%d%s", "Token[", BNFStrTable[cont], "]=", psData.parsHistogram[cont], "\n");
	}
	printf("----------------------------------\n");
}
