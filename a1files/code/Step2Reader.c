/*
************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Summer, 2025
* Author: TO_DO
* Professors: Paulo Sousa
************************************************************
#
# ECHO "=---------------------------------------="
# ECHO "|  COMPILERS - ALGONQUIN COLLEGE (F25)  |"
# ECHO "=---------------------------------------="
# ECHO "     -------------------------------	”
# ECHO "	 |        o  o   o  o          |	”
# ECHO "	 |        |\/ \^/ \/|          |	”
# ECHO "	 |        |,-------.|          |	”
# ECHO "	 |      ,-.(|)   (|),-.        |	”
# ECHO "	 |      \_*._ ' '_.* _/        |	”
# ECHO "	 |       /`-.`--' .-'\         |	”
# ECHO "	 |  ,--./    `---'    \,--.    |	”
# ECHO "	 |  \   |(  )     (  )|   /    |	”
# ECHO "	 |   \  | ||       || |  /     |	”
# ECHO "	 |    \ | /|\     /|\ | /      |	”
# ECHO "	 |    /  \-._     _,-/  \      |	”
# ECHO "	 |   //| \  `---'  // |\       |	”
# ECHO "	 |  /,-.,-.\       /,-.,-.\    |	”
# ECHO "	 |  o   o   o      o   o    o  |	”
# ECHO "	 |                             |	”
# ECHO "	 |  F       R       O       G  |	”
# ECHO "	 -------------------------------    ”
# ECHO "                                         "
# ECHO "[READER SCRIPT .........................]"
# ECHO "                                         "
*/

/*
***********************************************************
* File name: Reader.c
* Compiler: MS Visual Studio 2022
* Course: CST 8152 – Compilers, Lab Section: [011, 012, 013]
* Assignment: A12.
* Date: Jan 01 2025
* Professor: Paulo Sousa
* Purpose: This file is the main code for Buffer/Reader (A12)
************************************************************
*/

/*
 *.............................................................................
 * MAIN ADVICE:
 * - Please check the "TODO" labels to develop your activity.
 * - Review the functions to use "Defensive Programming".
 *.............................................................................
 */

#include <ctype.h>
#include <string.h>

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef CODER_H_
#include "Step1Coder.h"
#endif

#ifndef READER_H_
#include "Step2Reader.h"
#endif

/*
***********************************************************
* Function name: readerCreate
* Purpose: Creates the buffer reader according to capacity, increment
	factor and operational mode ('f', 'a', 'm')
* Author: Svillen Ranev / Paulo Sousa
* History/Versions: S22
* Called functions: calloc(), malloc()
* Parameters:
*   size = initial capacity
*   increment = increment factor
*   mode = operational mode
* Return value: bPointer (pointer to reader)
* Algorithm: Allocation of memory according to inicial (default) values.
* TODO ......................................................
*	- Adjust datatypes for your LANGUAGE.
*   - Use defensive programming
*	- Check boundary conditions
*	- Check flags.
*************************************************************
*/

BufferPointer readerCreate(frog_int size, frog_float factor) {
	BufferPointer readerPointer = NULL;
	/* TO_DO: Defensive programming: size */
	if (size < 0  || size > READER_MAX_SIZE) {
		size = READER_DEFAULT_SIZE;
	}
	if (factor < 0) {
		factor = READER_DEFAULT_FACTOR;
	}

	/* TO_DO: readerPointer allocation */
	readerPointer = (BufferPointer)calloc(1, sizeof(Buffer));
	/* TO_DO: Defensive programming: readerPointer */
	if (readerPointer == NULL) {
		return NULL;
	}

	/* TO_DO: content allocation */
	readerPointer->content = (frog_str)malloc(size);
	/* TO_DO: Defensive programming: content */
	if (readerPointer->content == NULL) {
		free(readerPointer);
		return NULL;
	}
	readerPointer->size = size;
	readerPointer->factor = factor;

	/* TO_DO: Initialize the histogram */
	for (frog_int i = 0; i < NCHAR; i++) {
		readerPointer->histogram[i] = 0;
	}

	/* TO_DO: Update the properties */
	readerPointer->position.wrte = 0;
	readerPointer->position.read = 0;
	readerPointer->position.mark = 0;

	/* TO_DO: Initialize flags */
	readerPointer->flags.isEmpty = FROG_TRUE;
	readerPointer->flags.isFull = FROG_FALSE;
	readerPointer->flags.isRead = FROG_FALSE;
	readerPointer->flags.isMoved = FROG_FALSE;

	/* TO_DO: Initialize errors */
	readerPointer->numReaderErrors = 0;
	readerPointer->checkSum = 0;
	return readerPointer;
}


/*
***********************************************************
* Function name: readerAddChar
* Purpose: Adds a char to buffer reader
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   ch = char to be added
* Return value:
*	readerPointer (pointer to Buffer Reader)
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/

BufferPointer readerAddChar(BufferPointer const readerPointer, frog_char ch) {
	frog_str tempReader = NULL;
	frog_int newSize = 0;
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL ) {
		printf("readerPointer is NULL\n");
		return NULL;
	}
	if (ch < READER_ASCII_START || ch > READER_ASCII_END) {
		readerPointer->numReaderErrors++;
		return NULL;
	}
	/* TO_DO: Test the inclusion of chars */
	if (readerPointer->position.wrte * (frog_int)sizeof(frog_char) < readerPointer->size) {
		/* TO_DO: Buffer not full: set flag */
		readerPointer->flags.isFull = FROG_FALSE;
		readerPointer->flags.isEmpty = FROG_FALSE;
	}
	else {
		/* TO_DO: Reset Full flag */
		readerPointer->flags.isFull = FROG_TRUE;
		/* TO_DO: Adjust the size to be duplicated */
		frog_float ratio = 1.0f + readerPointer->factor;
		newSize = readerPointer->size * ratio;
		/* TO_DO: Defensive programming */
		if (newSize <= 0 || newSize > READER_MAX_SIZE) {
			readerPointer->numReaderErrors++;
			return NULL;
		}
		tempReader = realloc(readerPointer->content, newSize);
		if (tempReader == NULL) {
			readerPointer->numReaderErrors++;
			return NULL;
		}
		if (tempReader != readerPointer->content) {
			readerPointer->flags.isMoved = FROG_TRUE;
		}
		readerPointer->content = tempReader;
		readerPointer->size = newSize;
		readerPointer->flags.isFull = FROG_FALSE;
	}
	/* TO_DO: Add the char */
	readerPointer->content[readerPointer->position.wrte] = ch;
	readerPointer->position.wrte++;
	/* TO_DO: Updates histogram */
	if (ch >= ASCII_START && ch <= ASCII_END) {
		readerPointer->histogram[ch]++;
	}
	return readerPointer;
}

/*
***********************************************************
* Function name: readerClear
* Purpose: Clears the buffer reader
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* Completed by Leo
*************************************************************
*/
frog_bool readerClear(BufferPointer const readerPointer) {
	// Defensive programming
	if (readerPointer == NULL) {
		printf("readerPointer is NULL\n");
			return FROG_FALSE;
	}
	// Adjust positions to zero
	readerPointer->position.wrte = 0;
	readerPointer->position.read = 0;
	readerPointer->position.mark = 0;

	// Adjust flags to original values
	readerPointer->flags.isEmpty = FROG_TRUE;
	readerPointer->flags.isFull = FROG_FALSE;
	readerPointer->flags.isRead = FROG_FALSE;
	readerPointer->flags.isMoved = FROG_FALSE;
	return FROG_TRUE;
}

/*
***********************************************************
* Function name: readerFree
* Purpose: Releases the buffer address
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
* Completed by Leo
*************************************************************
*/
frog_bool readerFree(BufferPointer const readerPointer) {
	// Defensive programming
	if (readerPointer == NULL) {
		return FROG_FALSE;
	}
	// Free memory (buffer/content)
	free(readerPointer->content);
	free(readerPointer);

	return FROG_TRUE;
}

/*
***********************************************************
* Function name: readerIsFull
* Purpose: Checks if buffer reader is full
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
* Completed by Leo
*************************************************************
*/
frog_bool readerIsFull(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL) {
		return FROG_FALSE;
	}
	/* TO_DO: Check flag if buffer is FUL */
	return readerPointer->flags.isFull;
}


/*
***********************************************************
* Function name: readerIsEmpty
* Purpose: Checks if buffer reader is empty.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
* Completed by Leo
*************************************************************
*/
frog_bool readerIsEmpty(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL) {
		return FROG_FALSE;
	}
	/* TO_DO: Check flag if buffer is EMP */
	return readerPointer->flags.isEmpty;
}

/*
***********************************************************
* Function name: readerSetMark
* Purpose: Adjust the position of mark in the buffer
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   mark = mark position for char
* Return value:
*	Boolean value about operation success
* TO_DO:
* Completed by Leo
*************************************************************
*/
frog_bool readerSetMark(BufferPointer const readerPointer, frog_int mark) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL) {
		return FROG_FALSE;
	}
	/* TO_DO: Adjust mark */
	if (!(mark >= 0 && mark < readerPointer->size)) {
		return FROG_FALSE;
	}
	readerPointer->position.mark = mark;
	return FROG_TRUE;
}


/*
***********************************************************
* Function name: readerPrint
* Purpose: Prints the string in the buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Number of chars printed.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
frog_int readerPrint(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming (including invalid chars) */
	if (readerPointer == NULL) {
		return READER_ERROR;
	}
	/* TO_DO: Print the buffer content */
	frog_int count = 0;
	frog_char ch;

	while ((ch = readerGetChar(readerPointer)) != READER_TERMINATOR) {
		/* TO_DO: Defensive programming (including invalid chars) */
		if (ch < ASCII_START || ch > ASCII_END) {
			readerPointer->numReaderErrors++;
			continue;
		}
		printf("%c", ch);
		count++;
	}
	return count;
}


/*
***********************************************************
* Function name: readerLoad
* Purpose: Loads the string in the buffer with the content of
	an specific file.
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   fileDescriptor = pointer to file descriptor
* Return value:
*	Number of chars read and put in buffer.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
frog_int readerLoad(BufferPointer const readerPointer, frog_str fileName) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL) {
		return READER_ERROR;
	}
	if (fileName == NULL) {
		return READER_ERROR;
	}
	/* TO_DO: Loads the file */
	/* TO_DO: Creates the string calling vigenereMem(fileName, STR_LANGNAME, DECYPHER) */
	frog_str content = vigenereMem(fileName, STR_LANGNAME, DECYPHER);
	if (content == NULL) {
		return READER_ERROR;
	}
	frog_int count = 0;
	while (content[count] != '\0') {
		BufferPointer tempReader = readerAddChar(readerPointer, content[count]);
		if (tempReader == NULL) {
			free(content);
			return READER_ERROR;
		}
		count++;
	}
	free(content);
	return count;
}

/*
***********************************************************
* Function name: readerRecover
* Purpose: Rewinds the buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value
*	Boolean value about operation success
* TO_DO:
* Completed by Leo
*************************************************************
*/
frog_bool readerRecover(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL) {
		return FROG_FALSE;
	}
	/* TO_DO: Adjust read and mark to zero */
	readerPointer->position.read = 0;
	readerPointer->position.mark = 0;
	return FROG_TRUE;
}


/*
***********************************************************
* Function name: readerRetract
* Purpose: Retracts the buffer to put back the char in buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
* Completed by Leo
*************************************************************
*/
frog_bool readerRetract(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL) {
		return FROG_FALSE;
	}
	if (readerPointer->position.read <= 0) {
		return FROG_FALSE;
	}
	/* TO_DO: Retract (return 1 pos read) */
	readerPointer->position.read--;
	return FROG_TRUE;
}


/*
***********************************************************
* Function name: readerRestore
* Purpose: Resets the buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
* Completed by Leo
*************************************************************
*/
frog_bool readerRestore(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL) {
		return FROG_FALSE;
	}
	/* TO_DO: Restore read to mark */
	readerPointer->position.read = readerPointer->position.mark;
	return FROG_TRUE;
}



/*
***********************************************************
* Function name: readerGetChar
* Purpose: Returns the char in the getC position.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Char in the getC position.
* TO_DO:
* Completed by Leo
*************************************************************
*/
frog_char readerGetChar(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL) {
		return READER_TERMINATOR;
	}
	if (readerPointer->position.read >= readerPointer->position.wrte) {
		readerPointer->flags.isRead = FROG_TRUE;
		return READER_TERMINATOR;
	}
	/* TO_DO: Returns size in the read position and updates read */
	readerPointer->flags.isRead = FROG_FALSE;
	frog_char ch = readerPointer->content[readerPointer->position.read];
	readerPointer->position.read++;
	return ch;
}


/*
***********************************************************
* Function name: readerGetContent
* Purpose: Returns the pointer to String.
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   pos = position to get the pointer
* Return value:
*	Position of string char.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
frog_str readerGetContent(BufferPointer const readerPointer, frog_int pos) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL) {
		return NULL;
	}
	if (!(pos >= 0 && pos < readerPointer->size)) {
		return NULL;
	}
	/* TO_DO: Return content (string) */
	return &(readerPointer->content[pos]);
}

/*
***********************************************************
* Function name: readerGetPosRead
* Purpose: Returns the value of getCPosition.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	The read position offset.
* TO_DO:
* Completed by Leo
*************************************************************
*/
frog_int readerGetPosRead(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL) {
		return READER_ERROR;
	}
	/* TO_DO: Return read */
	return readerPointer->position.read;
}


/*
***********************************************************
* Function name: readerGetPosWrte
* Purpose: Returns the position of char to be added
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Write position
* TO_DO:
* Completed by Leo
*************************************************************
*/
frog_int readerGetPosWrte(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL) {
		return READER_ERROR;
	}
	/* TO_DO: Return wrte */
	return readerPointer->position.wrte;}


/*
***********************************************************
* Function name: readerGetPosMark
* Purpose: Returns the position of mark in the buffer
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Mark position.
* TO_DO:
* Completed by Leo
*************************************************************
*/
frog_int readerGetPosMark(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL) {
		return READER_ERROR;
	}
	/* TO_DO: Return mark */
	return readerPointer->position.mark;}


/*
***********************************************************
* Function name: readerGetSize
* Purpose: Returns the current buffer capacity
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Size of buffer.
* TO_DO:
* Completed by Leo
*************************************************************
*/
frog_int readerGetSize(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL) {
		return READER_ERROR;
	}
	/* TO_DO: Return size */
	return readerPointer->size;}

/*
***********************************************************
* Function name: readerGetFlags
* Purpose: Returns the entire flags of Buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Flags from Buffer.
* TO_DO:
* Completed by Leo
*************************************************************
*/
#define FLAGS_
#undef FLAGS_
#ifndef FLAGS_
frog_void readerPrintFlags(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL) {
		return;
	}
	/* TO_DO: Return flags */
	printf("readerPointer->flags.isEmpty = %d\n", readerPointer->flags.isEmpty);
	printf("readerPointer->flags.isFull = %d\n", readerPointer->flags.isFull);
	printf("readerPointer->flags.isRead = %d\n", readerPointer->flags.isRead);
	printf("readerPointer->flags.isMoved = %d\n", readerPointer->flags.isMoved);
}
#else
#define bGetFlags(readerPointer) ((readerPointer)?(readerPointer->flags):(RT_FAIL_1))
#endif

/*
***********************************************************
* Function name: readerShowStat
* Purpose: Shows the char statistic.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value: (Void)
* TO_DO:
* Completed by Leo
*************************************************************
*/
frog_void readerPrintStat(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL) {
		return;
	}
	/* TO_DO: Print statistics */
	for (frog_int i = 0; i < NCHAR - 1; i++) {
		if (readerPointer->histogram[i] > 0) {
			printf("%c: %d\n", (char)i, readerPointer->histogram[i]);
		}
	}
}

/*
***********************************************************
* Function name: readerNumErrors
* Purpose: Returns the number of errors found.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Number of errors.
* TO_DO:
* Completed by Leo
*************************************************************
*/
frog_int readerNumErrors(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL) {
		return READER_ERROR;
	}
	/* TO_DO: Return the number of errors */
	return readerPointer->numReaderErrors;
}

/*
***********************************************************
* Function name: readerChecksum
* Purpose: Sets the checksum of the reader (4 bits).
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	[None]
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/

frog_int readerChecksum(BufferPointer readerPointer) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL) {
		return READER_ERROR;
	}
	/* TO_DO: Return the checksum (given by the content) */
	frog_int sum = 0;
	frog_int i = 0;
	for (i = 0; i < readerPointer->position.wrte; i++) {
		sum += readerPointer->content[i];
	}
	frog_int checksum = sum & 0x0F;
	readerPointer->checkSum = checksum;
	return checksum;
}
