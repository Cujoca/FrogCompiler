/*
************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Fall, 2025
* Author: TO_DO
* Professors: Paulo Sousa
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
***********************************************************
* File name: Reader.c
* Compiler: MS Visual Studio 2022
* Course: CST 8152  Compilers, Lab Section: [011, 012, 013]
* Assignment: A12.
* Date: Sep 01 2025
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef CODER_H_
#include "Step1Coder.h"
#endif

// Function to perform the Vigenère cipher (encoding or decoding)
void vigenereFile(const frog_str inputFileName, const frog_str outputFileName, const frog_str key, frog_int encode) {
	// Checking for null arguments
	if (inputFileName == NULL || outputFileName == NULL || key == NULL) {
		errorPrint("Error: Null argument passed.\n");
		return;
	}

	// Checking for valid encoding option
	if (encode != CYPHER && encode != DECYPHER) {
		errorPrint("Error: Invalid operation. Use 'CYPHER' or 'DECYPHER'.\n");
		return;
	}

	// Local variables
	frog_int keySize = (frog_int)strlen(key);
	frog_int keyIndex = 0;
	frog_int inputChar;

	// Input and output files
	FILE* inputFile = fopen(inputFileName, "r");
	FILE* outputFile = fopen(outputFileName, "w");

	// Checking if files were opened successfully
	if (!inputFile){
		errorPrint("Error: Could not open input file '%s'.\n", inputFileName);
		return;
	}

	if (!outputFile) {
		errorPrint("Error: Could not open output file '%s'.\n", outputFileName);
		fclose(inputFile);
		return;
	}

	// Checking for key length
	if (keySize == 0) {
		errorPrint("Error: Key is empty.\n");
		fclose(inputFile);
		fclose(outputFile);
		return;
	}

	// Check if it is encode/decode to change the char (using Vigenere algorithm)
	while ((inputChar = fgetc(inputFile)) != EOF) {
		if (inputChar >= ASCII_START && inputChar <= ASCII_END) {
			frog_int keyChar = key[keyIndex % keySize] - ASCII_START;
			frog_int outputChar;

			if (encode == CYPHER) {
				outputChar = (inputChar - ASCII_START + keyChar) % ASCII_RANGE + ASCII_START;
			} else { // DECYPHER
				outputChar = (inputChar - ASCII_START - keyChar + ASCII_RANGE) % ASCII_RANGE + ASCII_START;
			}
			fputc(outputChar, outputFile);
			keyIndex++;
		} else {
			fputc(inputChar, outputFile);
		}
	}

	// Closing the files
	fclose(inputFile);
	fclose(outputFile);
}

// Function to perform the Vigenère cipher (encoding or decoding)
frog_str vigenereMem(const frog_str inputFileName, const frog_str key, frog_int encode) {
	// Checking for null arguments
	if (inputFileName == NULL || key == NULL) {
		errorPrint("Error: Null argument passed.\n");
		 return NULL;
	}

	// Checking for valid encoding option
	if (encode != CYPHER && encode != DECYPHER) {
		errorPrint("Error: Invalid operation. Use 'CYPHER' or 'DECYPHER'.\n");
		 return NULL;
	}

	// Local Variables
	frog_int keySize = (frog_int)strlen(key);
	frog_int keyIndex = 0;
	frog_int outputIndex = 0;
	frog_int inputChar;

	// Get size of file and allocate memory for output
	frog_int fileSize = getSizeOfFile(inputFileName);
	if (fileSize < 0) {
		errorPrint("Error: Could not get size of input file '%s'.\n", inputFileName);
		 return NULL;
	}

	frog_str output = (frog_str)malloc(fileSize + 1);
	if (!output) {
		errorPrint("Error: Could not allocate memory for output.\n");
		 return NULL;
	}

	// Opening input file
	FILE* inputFile = fopen(inputFileName, "r");
	if (!inputFile) {
		errorPrint("Error: Could not open input file '%s'.\n", inputFileName);
		free(output);
		return NULL;
	}

	// Checking for key length
	if (keySize == 0) {
		errorPrint("Error: Key is empty.\n");
		fclose(inputFile);
		free(output);
		return NULL;
	}

	// Logic to encode/decode for only visible chars
	while ((inputChar = fgetc(inputFile)) != EOF && outputIndex < fileSize ) {
		if (inputChar >= ASCII_START && inputChar <= ASCII_END) {
			frog_int keyChar = key[keyIndex % keySize] - ASCII_START;
			frog_int outputChar;

			if (encode == CYPHER) {
				outputChar = (inputChar - ASCII_START + keyChar) % ASCII_RANGE + ASCII_START;
			} else { // DECYPHER
				outputChar = (inputChar - ASCII_START - keyChar + ASCII_RANGE) % ASCII_RANGE + ASCII_START;
			}
			output[outputIndex++] = (frog_char)outputChar;
			keyIndex++;
		} else {
			output[outputIndex++] = (frog_char)inputChar;
		}
	}

	// Null terminate the string and close the file
	output[outputIndex] = '\0';
	fclose(inputFile);
	return output;
}

// Function to encode (cypher)
void cypher(const frog_str inputFileName, const frog_str outputFileName, const frog_str key) {
    vigenereFile(inputFileName, outputFileName, key, CYPHER);
}

// Function to decode (decypher)
void decypher(const frog_str inputFileName, const frog_str outputFileName, const frog_str key) {
    vigenereFile(inputFileName, outputFileName, key, DECYPHER);
}

// TO_DO: Get file size (util method)
frog_int getSizeOfFile(const frog_str filename) {

    // Checking for null parameter
	if (filename == NULL) {
		errorPrint("Error: Null argument passed.\n");
		return -1;
	}

	FILE* file = fopen(filename, "r");
	frog_int size = 0;

	// Checking if the file opened successfully
	if (!file) {
		errorPrint("Error: Could not open file '%s'.\n", filename);
		return -1;
	}

	// Logic to get the size of the file
	 if (fseek(file, 0, SEEK_END) != 0) {
	 	errorPrint("Error: Could not seek file '%s'.\n", filename);
	 	fclose(file);
	 	return -1;
	 };

	// Logic to get the current position
	size = (frog_int)ftell(file);
	if (size < 0) {
		errorPrint("Error: Could not tell file position for '%s'.\n", filename);
		fclose(file);
		return -1;
	}

	// Closing the file
	fclose(file);

    return size;
}