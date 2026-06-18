/*
************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Spring, 2026
* Author: Andrei Cojocaru and Leo Paquette
* Professors: Vardaan Sangar
************************************************************
#
# ECHO "=---------------------------------------="
# ECHO "|  COMPILERS - ALGONQUIN COLLEGE (F25)  |"
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
# ECHO "[READER SCRIPT .........................]"
# ECHO "                                         "
*/

/*
************************************************************
* File name: Reader.h
* Compiler: MS Visual Studio 2022
* Course: CST 8152 � Compilers, Lab Section: [011, 012]
* Assignment: A2
* Date:
* Professor: Vardaan Sangar
* Purpose: This file is the main header for Reader (.h)
************************************************************
*/

/*
 *.............................................................................
 * MAIN ADVICE:
 * Review the functions to use "Defensive Programming".
 *.............................................................................
 */

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef READER_H_
#define READER_H_

 /* TIP: Do not change pragmas, unless necessary .......................................*/
 /*#pragma warning(1:4001) *//*to enforce C89 type comments  - to make //comments an warning */
 /*#pragma warning(error:4001)*//* to enforce C89 comments - to make // comments an error */

 /* standard header files */
#include <stdio.h>  /* standard input/output */
#include <stdlib.h> /* for dynamic memory allocation*/
#include <limits.h> /* implementation-defined data type ranges and limits */

/* CONSTANTS DEFINITION: GENERAL (NOT LANGUAGE DEPENDENT) .................................. */

/* Constants about controls (not need to change) */
#define READER_ERROR		(-1)		/* General error message */
#define READER_TERMINATOR	'\0'		/* General EOF */

/* CONSTANTS DEFINITION: PREFIXED BY LANGUAGE NAME .................................. */

/* You should add your own constant definitions here */
#define READER_MAX_SIZE		INT_MAX-1	/* maximum capacity */ 

#define READER_DEFAULT_SIZE		100			/* default initial buffer reader capacity */
#define READER_DEFAULT_FACTOR	0.5f		/* default factor */

#define READER_ASCII_START		0
#define READER_ASCII_END		127

/* Buffer status flags are implemented as the Flag struct below
 * (isEmpty / isFull / isRead / isMoved) rather than packed bit-masks. */

#define NCHAR				128			/* Chars from 0 to 127 */

#define CHARSEOF			(-1)		/* EOF Code for Reader */

/* STRUCTURES DEFINITION: SUFIXED BY LANGUAGE NAME .................................. */

/* Offset declaration */
typedef struct position {
	frog_int wrte;					/* the offset to the add chars (in chars) */
	frog_int read;					/* the offset to the get a char position (in chars) */
	frog_int mark;					/* the offset to the mark position (in chars) */
} Position;

/* Flags declaration */
typedef struct flag {
	frog_bool isEmpty;					/* checks if there is no content */
	frog_bool isFull;					/* the content is using all size */
	frog_bool isRead;					/* all content was read */
	frog_bool isMoved;					/* the content was moved in reallocation */
} Flag;

/* Buffer structure */
typedef struct bufferReader {
	frog_str		content;			/* pointer to the beginning of character array (character buffer) */
	frog_int		size;				/* current dynamic memory size (in bytes) allocated to character buffer */
	frog_float		factor;				/* factor for increase the buffer */
	Flag			flags;				/* contains character array reallocation flag and end-of-buffer flag */
	Position		position;			/* Offset / position field */
	frog_int		histogram[NCHAR];	/* Statistics of chars */
	frog_int		numReaderErrors;	/* Number of errors from Reader */
	frog_int		checkSum;			/* Sum of bytes(chars) */
} Buffer, * BufferPointer;

/* FUNCTIONS DECLARATION:  .................................. */

/* General Operations */
BufferPointer	readerCreate(frog_int, frog_float);
BufferPointer	readerAddChar(BufferPointer const, frog_char);
frog_bool		readerClear(BufferPointer const);
frog_bool		readerFree(BufferPointer const);
frog_bool		readerIsFull(BufferPointer const);
frog_bool		readerIsEmpty(BufferPointer const);
frog_bool		readerSetMark(BufferPointer const, frog_int);
frog_int		readerPrint(BufferPointer const);
frog_int		readerLoad(BufferPointer const, frog_str);
frog_bool		readerRecover(BufferPointer const);
frog_bool		readerRetract(BufferPointer const);
frog_bool		readerRestore(BufferPointer const);
frog_int		readerChecksum(BufferPointer const);
/* Getters */
frog_char		readerGetChar(BufferPointer const);
frog_str		readerGetContent(BufferPointer const, frog_int);
frog_int		readerGetPosRead(BufferPointer const);
frog_int		readerGetPosWrte(BufferPointer const);
frog_int		readerGetPosMark(BufferPointer const);
frog_int		readerGetSize(BufferPointer const);
frog_void		readerPrintFlags(BufferPointer const);
frog_void		readerPrintStat(BufferPointer const);
frog_int		readerNumErrors(BufferPointer const);

#endif
