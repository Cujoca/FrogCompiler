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
 * Match Token
 ***********************************************************
 */
/* TO_DO: This is the main code for match - check your definition */
frog_void matchToken(frog_int tokenCode, frog_int tokenAttribute) {
	frog_int matchFlag = FROG_TRUE;
	switch (lookahead.code) {
	case KW_T:
		if (lookahead.attribute.codeType != tokenAttribute)
			matchFlag = FROG_FALSE;
	default:
		if (lookahead.code != tokenCode)
			matchFlag = FROG_FALSE;
	}
	if (matchFlag && lookahead.code == SEOF_T)
		return;
	if (matchFlag) {
		lookahead = tokenizer();
		if (lookahead.code == ERR_T) {
			printError();
			lookahead = tokenizer();
			syntaxErrorNumber++;
		}
	}
	else
		syncErrorHandler(tokenCode);
}

/*
 ************************************************************
 * Syncronize Error Handler
 ***********************************************************
 */
/* TO_DO: This is the function to handler error - adjust basically datatypes */
frog_void syncErrorHandler(frog_int syncTokenCode) {
	printError();
	syntaxErrorNumber++;
	while (lookahead.code != syncTokenCode) {
		if (lookahead.code == SEOF_T)
			exit(syntaxErrorNumber);
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
	extern frog_int numParserErrors;			/* link to number of errors (defined in Parser.h) */
	Token t = lookahead;
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
	case EOS_T:
		printf("NA\n");
		break;
	default:
		printf("%s%s%d\n", STR_LANGNAME, ": Scanner error: invalid token code: ", t.code);
		numParserErrors++; // Updated parser error
	}
}

/*
 ************************************************************
 * Program statement
 * BNF: <program> -> <opt_comment> tadpole MNID(main() { <opt_statements> }
 * FIRST(<program>) = {CMT_T, KW_T (tadpole)}.
 * Note: MNID_T's lexeme already includes the trailing '(' (see funcID),
 * so "main(" is matched as a single MNID_T token - there is no separate
 * LPR_T to match afterwards.
 ***********************************************************
 */
frog_void program() {
	psData.parsHistogram[BNF_program]++;
	if (lookahead.code == CMT_T) {
		comment();
	}
	matchToken(KW_T, KW_tadpole);
	if (lookahead.code == MNID_T && strncmp(lookahead.attribute.idLexeme, LANG_MAIN, strlen(LANG_MAIN)) == 0) {
		matchToken(MNID_T, NO_ATTR);
		optParams();
		matchToken(RPR_T, NO_ATTR);
		matchToken(LBR_T, NO_ATTR);
		optionalStatements();
		matchToken(RBR_T, NO_ATTR);
	}
	else {
		printError();
	}
	printf("%s%s\n", STR_LANGNAME, ": Program parsed");
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
 * FIRST(<optParams>) = { e, KW_T (tadpole), KW_T (lilypad), KW_T (croak) }
 ***********************************************************
 */
frog_void optParams() {
	psData.parsHistogram[BNF_optParams]++;
	if (lookahead.code == CMT_T) {
		comment();
	}
	if (lookahead.code == KW_T &&
		(lookahead.attribute.codeType == KW_tadpole ||
		 lookahead.attribute.codeType == KW_lilypad ||
		 lookahead.attribute.codeType == KW_croak)) {
		paramList();
	}
	printf("%s%s\n", STR_LANGNAME, ": Optional param list parsed");
}

/*
 ************************************************************
 * matchType
 * Consumes a KW_T token whose attribute is tadpole/lilypad/croak.
 * Callers must only invoke this when they already know (via FIRST)
 * that the lookahead is a type keyword.
 ***********************************************************
 */
static frog_void matchType() {
	if (lookahead.code == KW_T &&
		(lookahead.attribute.codeType == KW_tadpole ||
		 lookahead.attribute.codeType == KW_lilypad ||
		 lookahead.attribute.codeType == KW_croak)) {
		matchToken(KW_T, lookahead.attribute.codeType);
	}
	else {
		printError();
	}
}

/*
 ************************************************************
 * paramList
 * BNF: <paramList> -> <type> VID_T <paramListPrime>
 * FIRST(<paramList>) = { KW_T (tadpole), KW_T (lilypad), KW_T (croak) }
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
 * Optional Var List Declarations
 * BNF: <opt_varlist_declarations> -> <varlist_declarations> | e
 * FIRST(<opt_varlist_declarations>) = { e, KW_T (KW_int), KW_T (KW_real), KW_T (KW_string)}.
 ***********************************************************
 */
frog_void optVarListDeclarations() {
	psData.parsHistogram[BNF_optVarListDeclarations]++;
	switch (lookahead.code) {
	default:
		; // Empty
	}
	printf("%s%s\n", STR_LANGNAME, ": Optional Variable List Declarations parsed");
}

/* TO_DO: Continue the development (all non-terminal functions) */

/*
 ************************************************************
 * Optional statement
 * BNF: <opt_statements> -> <statements> | ϵ
 * FIRST(<opt_statements>) = { ϵ , IVID_T, FVID_T, SVID_T, KW_T(KW_if),
 *				KW_T(KW_while), MNID_T(print&), MNID_T(input&) }
 ***********************************************************
 */
frog_void optionalStatements() {
	psData.parsHistogram[BNF_optionalStatements]++;
	switch (lookahead.code) {
	case CMT_T:
		comment();
	case MNID_T:
		if ((strncmp(lookahead.attribute.idLexeme, LANG_WRTE, 6) == 0) ||
			(strncmp(lookahead.attribute.idLexeme, LANG_READ, 6) == 0)) {
			statements();
			break;
		}
	default:
		; // Empty
	}
	printf("%s%s\n", STR_LANGNAME, ": Optional statements parsed");
}

/*
 ************************************************************
 * Statements
 * BNF: <statements> -> <statement><statementsPrime>
 * FIRST(<statements>) = { IVID_T, FVID_T, SVID_T, KW_T(KW_if),
 *		KW_T(KW_while), MNID_T(input&), MNID_T(print&) }
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
 * BNF: <statementsPrime> -> <statement><statementsPrime> | ϵ
 * FIRST(<statementsPrime>) = { ϵ , IVID_T, FVID_T, SVID_T, 
 *		KW_T(KW_if), KW_T(KW_while), MNID_T(input&), MNID_T(print&) }
 ***********************************************************
 */
frog_void statementsPrime() {
	psData.parsHistogram[BNF_statementsPrime]++;
	switch (lookahead.code) {
	case CMT_T:
		comment();
	case KW_T:
		if (lookahead.attribute.codeType == KW_if
			|| lookahead.attribute.codeType == KW_while
			|| lookahead.attribute.codeType == KW_return) {
			statement();
			statementsPrime();
			break;
		}
	case MNID_T:
		if (strncmp(lookahead.attribute.idLexeme, LANG_WRTE, 6) == 0) {
			statements();
			break;
		}
	default:
		; //empty string
	}
}

/*
 ************************************************************
 * OptionalReturnValue
 * BNF: <variable list Prime> -> ,<variable identifier><variable list Prime> | ϵ
 * FIRST(<variable list prime>) = { COM_T,  ϵ } = { , , ϵ }
 ***********************************************************
 */
frog_void optReturnValue() {
	//psData.parsHistogram[BNF_optReturnValue]++;
	switch (lookahead.code) {
	case INL_T:
		matchToken(INL_T, NO_ATTR);
		break;
	case STR_T:
		matchToken(STR_T, NO_ATTR);
		break;
	default:
		; // empty
	}
}

/*
 ************************************************************
 * Return Statement
 * BNF: <return statement> -> return (<variableIdentifier> | INL_T | FPL_T | SL_T | ϵ)
 * FIRST(<return statement>) = { KW_T(KW_return) }
 ***********************************************************
 */
frog_void returnStatement() {
	psData.parsHistogram[BNF_returnStatement]++;
	matchToken(KW_T, KW_return);
	//matchToken(LPR_T, NO_ATTR);
	optReturnValue();
	//matchToken(RBR_T, NO_ATTR);
	matchToken(EOS_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Return statement parsed");
}

/*
 ************************************************************
 * Single statement
 * BNF: <statement> -> <assignment statement> | <selection statement> |
 *	<iteration statement> | <input statement> | <output statement>
 * FIRST(<statement>) = { IVID_T, FVID_T, SVID_T, KW_T(KW_if), KW_T(KW_while),
 *			MNID_T(input&), MNID_T(print&) }
 ***********************************************************
 */
frog_void statement() {
	psData.parsHistogram[BNF_statement]++;
	switch (lookahead.code) {
	case CMT_T:
		comment();
	case KW_T:
		switch (lookahead.attribute.codeType) {
		case KW_return:
			returnStatement();
			break;
		default:
			printError();
		}
		break;
	case MNID_T:
		if (strncmp(lookahead.attribute.idLexeme, LANG_WRTE, 6) == 0) {
			outputStatement();
		}
		break;
	default:
		printError();
	}
	printf("%s%s\n", STR_LANGNAME, ": Statement parsed");
}

/*
 ************************************************************
 * Output Statement
 * BNF: <output statement> -> print& (<output statementPrime>);
 * FIRST(<output statement>) = { MNID_T(print&) }
 ***********************************************************
 */
frog_void outputStatement() {
	psData.parsHistogram[BNF_outputStatement]++;
	matchToken(MNID_T, NO_ATTR);
	matchToken(LPR_T, NO_ATTR);
	outputVariableList();
	matchToken(RPR_T, NO_ATTR);
	matchToken(EOS_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Output statement parsed");
}

/*
 ************************************************************
 * Output Variable List
 * BNF: <opt_variable list> -> <variable list> | ϵ
 * FIRST(<opt_variable_list>) = { IVID_T, FVID_T, SVID_T, ϵ }
 ***********************************************************
 */
frog_void outputVariableList() {
	psData.parsHistogram[BNF_outputVariableList]++;
	switch (lookahead.code) {
	case STR_T:
		matchToken(STR_T, NO_ATTR);
		break;
	default:
		;
	}
	printf("%s%s\n", STR_LANGNAME, ": Output variable list parsed");
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
