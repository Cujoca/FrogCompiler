/*
************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Spring, 2026
* Author: Andrei Cojocaru and Leo Paquette
* Professor: Vardaan Sangar
************************************************************
#
# ECHO "=---------------------------------------="
# ECHO "|  COMPILERS - ALGONQUIN COLLEGE (S26)  |"
# ECHO "=---------------------------------------="
# ECHO "     -------------------------------	�
# ECHO "	 |        o  o   o  o          |	�
# ECHO "	 |        |\/ \^/ \/|          |	�
# ECHO "	 |        |,-------.|          |	�
# ECHO "	 |      ,-.(|)   (|),-.        |	�
# ECHO "	 |      \_*._ ' '_.* _/        |	�
# ECHO "	 |       /`-.`--' .-'\         |	�
# ECHO "	 |  ,--./    `---'    \,--.    |	�
# ECHO "	 |  \   |(  )     (  )|   /    |	�
# ECHO "	 |   \  | ||       || |  /     |	�
# ECHO "	 |    \ | /|\     /|\ | /      |	�
# ECHO "	 |    /  \-._     _,-/  \      |	�
# ECHO "	 |   //| \  `---'  // |\       |	�
# ECHO "	 |  /,-.,-.\       /,-.,-.\    |	�
# ECHO "	 |  o   o   o      o   o    o  |	�
# ECHO "	 |                             |	�
# ECHO "	 |  F       R       O       G  |	�
# ECHO "	 -------------------------------    �
# ECHO "                                         "
# ECHO "[COMPILER SCRIPT .......................]"
# ECHO "                                         "
/*

************************************************************
* File name: Compilers.h
* Compiler: MS Visual Studio 2022
* Course: CST 8152 Compilers, Lab Section: 301
* Assignment: A1
* Date: May 31, 2026
* Professor: Vardaan Sangar
* Purpose: This file defines the functions called by main function.
* Function list: mainReader(), mainScanner(), mainParser().
*************************************************************/

#ifndef COMPILERS_H_
#define COMPILERS_H_

#define DEBUG 0

/*
 * ............................................................................
 * NOTE: This file must be updated according to each assignment
 * (see the progression: reader > scanner > parser).
 * ............................................................................
 */

/* Language name (cannot be "Sofia") */
#define STR_LANGNAME	"Frog"

/* Logical constants - adapt for your language */
#define FROG_TRUE  1
#define FROG_FALSE 0

#define INVALID NULL
#define EOF_CHAR '\0'

/*
------------------------------------------------------------
Data types definitions
NOTE: Some types may not be directly used by your language,
		but they can be necessary for conversions.
------------------------------------------------------------
*/

/* Language-specific type definitions */
typedef char			frog_char;
typedef char*			frog_str;
typedef int				frog_int;
typedef float			frog_float;
typedef void			frog_void;

typedef unsigned char	frog_bool;
typedef unsigned char	frog_byte;

typedef long			frog_long;
typedef double			frog_doub;

/*
------------------------------------------------------------
Programs:
1: Coder - invokes Main1Coder code
2: Reader - invokes Main2Reader code
3: Scanner - invokes Main3Scanner code
4: Parser - invokes Main4Parser code
5: Writer - invokes Main5Writer code
------------------------------------------------------------
*/
enum PROGRAMS {
	PGM_CDR = '1', // Coder:	05pt
	PGM_RDR = '2', // Reader:	05pt
	PGM_SCN = '3', // Scanner:	15pt
	PGM_PSR = '4', // Parser:	15pt
	PGM_WRT = '5', // Writer:	10pt
};

/*
------------------------------------------------------------
Main functions signatures
(Code will be updated during next assignments)
------------------------------------------------------------
*/
frog_int main1Coder	(frog_int argc, frog_str* argv);
frog_int main2Reader (frog_int argc, frog_str* argv);
frog_int main3Scanner(frog_int argc, frog_str* argv);
frog_int main4Parser (frog_int argc, frog_str* argv);
frog_void printLogo();
frog_void errorPrint(frog_str fmt, ...);

#endif

/*
	  "args": [
		1,
		1,
		"README.txt",
		"CODED.txt"
	  ]
	  "args": [
		4,
		"CODED.txt"
	  ]
*/
