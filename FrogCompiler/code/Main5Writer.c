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
* File name: MainReader.c
* Compiler: MS Visual Studio 2022
* Course: CST 8152 � Compilers, Lab Section: [011, 012]
* Assignment: A12, A22, A32.
* Date: Jan 01 2025
* Professor: Paulo Sousa
* Purpose: This file is the main code for Buffer/Reader (A12)
* Function list: (...).
*************************************************************/

/*
 *.............................................................................
 * ADVICE 1:
 * Please check the "TODO" labels to develop your activity.
 *
 * ADVICE 2: Preprocessor directives
 * The #define _CRT_SECURE_NO_WARNINGS should be used in MS Visual Studio projects
 * to suppress the warnings about using "unsafe" functions like fopen()
 * and standard sting library functions defined in string.h.
 * The define directive does not have any effect on other compiler projects 
 * (Gcc, VSCode, Codeblocks, etc.).
 *.............................................................................
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef CODER_H_
#include "Step1Coder.h"
#endif

#ifndef WRITER_H_
#include "Step5Writer.h"
#endif

/*
************************************************************
* Main function from Buffer
* Parameters:
*   argc / argv = Parameters from command prompt
* Return value:
*	Success operation.
* Algorithm:
*	Decodes the coded source (Coder, A1) into memory, then loads the
*	decoded characters into a fresh source Buffer and drives it through
*	the same startScanner()/tokenizer() machinery the Parser (A4) uses,
*	so the Writer (Step5Writer.c) interprets the real token stream
*	instead of re-parsing raw text.
************************************************************
*/

frog_int main5Writer(frog_int argc, frog_str* argv) {
	if (argc >= 2) {
		frog_str source = argv[2];
		frog_str content;
		frog_str p;
		BufferPointer buf;
		frog_int size;

		/* load source file into input buffer  */
		printf("Reading file %s ....Please wait\n", source);
		size = getSizeOfFile(source);
		content = vigenereMem(source, STR_LANGNAME, DECYPHER);
		/* find the size of the file  */
		if (size <= 0 || content == NULL) {
			printf("The input file %s %s\n", source, "is not completely loaded.");
			return EXIT_SUCCESS;
		}

		buf = readerCreate(READER_DEFAULT_SIZE, READER_DEFAULT_FACTOR);
		if (buf == NULL) {
			errorPrint("%s%s%s", argv[0], ": ", "Could not create source buffer");
			exit(EXIT_FAILURE);
		}
		for (p = content; *p; p++)
			readerAddChar(buf, *p);
		readerAddChar(buf, READER_TERMINATOR);

		stringLiteralTable = readerCreate(READER_DEFAULT_SIZE, READER_DEFAULT_FACTOR);
		if (stringLiteralTable == NULL) {
			errorPrint("%s%s%s", argv[0], ": ", "Could not create string literal buffer");
			exit(EXIT_FAILURE);
		}

		startScanner(buf);
		runProgram(buf);
	}
	return EXIT_SUCCESS;
}
