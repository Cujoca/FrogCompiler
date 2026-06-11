/*
************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Spring, 2026
* Author: Andrei Cojocaru and Leo Paquette
* Professor: Vardaan Sangar
************************************************************
#
# ECHO "=---------------------------------------="
# ECHO "|  COMPILERS - ALGONQUIN COLLEGE (F25)  |"
# ECHO "=---------------------------------------="
# ECHO "     -------------------------------	
# ECHO "	 |        o  o   o  o          |	
# ECHO "	 |        |\/ \^/ \/|          |	
# ECHO "	 |        |,-------.|          |	
# ECHO "	 |      ,-.(|)   (|),-.        |	
# ECHO "	 |      \_*._ ' '_.* _/        |	
# ECHO "	 |       /`-.`--' .-'\         |	
# ECHO "	 |  ,--./    `---'    \,--.    |	
# ECHO "	 |  \   |(  )     (  )|   /    |	
# ECHO "	 |   \  | ||       || |  /     |	
# ECHO "	 |    \ | /|\     /|\ | /      |	
# ECHO "	 |    /  \-._     _,-/  \      |	
# ECHO "	 |   //| \  `---'  // |\       |	
# ECHO "	 |  /,-.,-.\       /,-.,-.\    |	
# ECHO "	 |  o   o   o      o   o    o  |	
# ECHO "	 |                             |	
# ECHO "	 |  F       R       O       G  |	
# ECHO "	 -------------------------------    
# ECHO "                                         "
# ECHO "[COMPILER SCRIPT .......................]"
# ECHO "                                         "
*/

/*
************************************************************
* File name: Compilers.c
* Compiler: MS Visual Studio 2022
* Course: CST 8152 Compilers, Lab Section: 301
* Assignment: A1
* Date: May 31, 2026
* Professor: Vardaan Sangar
* Purpose: This file is the main program of Compilers Project
* Function list: main().
************************************************************
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

/*
 * ............................................................................
 * ADVICE 1:
 * Please check the "TODO" labels to develop your activity.
 *
 * ADVICE 2: This file must be updated according to each assignment
 * (see the progression: reader > scanner > parser).
 * ............................................................................
 */

/*
***********************************************************
* Function name: main
* Purpose: Main function
* Author: Paulo Sousa
* History/Versions: Ver F25
* Called functions: mainReader(), mainScanner(), mainParser()
* Parameters: Command line arguments - argc, argv
* Return value: Status
* Algorithm: -
*************************************************************
*/

frog_int main(int argc, char** argv) {

	frog_int i;
	printLogo();
	if (DEBUG) {
		for (i = 0; i < argc; ++i)
			printf("argv[%d] = %s\n", i, argv[i]);
	}
	if (argc < 2) {
		printf("%s%c%s%c%s%c%s%c%s%c%s", "OPTIONS:\n* [",
			PGM_CDR, "] - Coder\n* [",
			PGM_RDR, "] - Reader\n* [",
			PGM_SCN, "] - Scanner\n* [",
			PGM_PSR, "] - Parser\n* [",
			PGM_WRT, "] - Writer\n");
		return EXIT_FAILURE;
	}
	frog_char option = argv[1][0];
	switch (option) {
	case PGM_CDR:
		printf("%s%c%s", "\n[Option '", PGM_CDR, "': Starting CODER .....]\n\n");
		main1Coder(argc, argv);
		break;
	case PGM_RDR:
			printf("%s%c%s", "\n[Option '", PGM_RDR, "': Starting READER .....]\n\n");
			main2Reader(argc, argv);
			break;
	default:
		printf("%s%c%s%c%s%c%s%c%s%c%s", "OPTIONS:\n* [",
			PGM_CDR, "] - Coder\n* [",
			PGM_RDR, "] - Reader\n* [",
			PGM_SCN, "] - Scanner\n* [",
			PGM_PSR, "] - Parser\n* [",
			PGM_WRT, "] - Writer\n");
		break;
	}
	return EXIT_SUCCESS;
}

/*
***********************************************************
* Function name: printLogo
* Purpose: Print Logo
* Author: Paulo Sousa
* History/Versions: Ver F25
* Called functions: -
* Parameters: -
* Return value: (Null)
* Algorithm: -
*************************************************************
*/

frog_void printLogo() {
	printf("%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s",
		"\t=---------------------------------------=\n",
		"\t|  COMPILERS - ALGONQUIN COLLEGE (S25)  |\n",
		"\t=---------------------------------------=\n",
    "\t     -------------------------------     \n",
    "\t     |        o  o   o  o          |     \n",
    "\t     |        |\\/ \\^/ \\/|          |     \n",
    "\t     |        |,-------.|          |     \n",
    "\t     |      ,-.(|)   (|),-.        |     \n",
    "\t     |      \\_*._ ' '_.* _/        |     \n",
    "\t     |       /`-.`--' .-'\\         |     \n",
    "\t     |  ,--./    `---'    \\,--.    |     \n",
    "\t     |  \\   |(  )     (  )|   /    |     \n",
    "\t     |   \\  | ||       || |  /     |     \n",
    "\t     |    \\ | /|\\     /|\\ | /      |     \n",
    "\t     |    /  \\-._     _,-/  \\      |     \n",
    "\t     |   //| \\  `---'  // |\\       |     \n",
    "\t     |  /,-.,-.\\       /,-.,-.\\    |     \n",
    "\t     |  o   o   o      o   o    o  |     \n",
    "\t     |                             |     \n",
    "\t     |  F       R       O       G  |     \n",
    "\t     -------------------------------     \n",
    "\t[CODER SCRIPT ..........................]\n\n");
}

/*
************************************************************
* Error printing function with variable number of arguments
* Params: Variable arguments, using formats from C language.
*	- Internal vars use list of arguments and types from stdarg.h
*   - NOTE: The format is using signature from C Language
************************************************************
*/

frog_void errorPrint(frog_str fmt, ...) {
	/* Initialize variable list */
	va_list ap;
	va_start(ap, fmt);

	(frog_void)vfprintf(stderr, fmt, ap);
	va_end(ap);

	/* Move to new line */
	if (strchr(fmt, '\n') == NULL)
		fprintf(stderr, "\n");
}
