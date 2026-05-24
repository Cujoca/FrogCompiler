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
	// TO_DO: Use defensive programming (checking files)
	if (inputFileName == NULL || outputFileName == NULL || key == NULL) {
		errorPrint("Error: Null argument passed.\n");
		return;
	}

	if (encode != CYPHER && encode != DECYPHER) {
		errorPrint("Error: Invalid operation. Use 'CYPHER' or 'DECYPHER'.\n");
		return;
	}

	// TO_DO: Define local variables
	frog_int keySize = (frog_int)strlen(key);
	frog_int keyIndex = 0;
	frog_int inputChar;

	// TO_DO: Define the input and output files (ex: FILE* inputFile, FILE* outputFile
	FILE* inputFile = fopen(inputFileName, "r");
	FILE* outputFile = fopen(outputFileName, "w");

	if (!inputFile){
		errorPrint("Error: Could not open input file '%s'.\n", inputFileName);
		return;
	}

	if (!outputFile) {
		errorPrint("Error: Could not open output file '%s'.\n", outputFileName);
		fclose(inputFile);
		return;
	}

	if (keySize == 0) {
		errorPrint("Error: Key is empty.\n");
		fclose(inputFile);
		fclose(outputFile);
		return;
	}

	// TO_DO: Logic: check if it is encode / decode to change the char (using Vigenere algorithm) - next function
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

	// TO_DO: Close the files
	fclose(inputFile);
	fclose(outputFile);
}

// Function to perform the Vigenère cipher (encoding or decoding)
frog_str vigenereMem(const frog_str inputFileName, const frog_str key, frog_int encode) {
	// TO_DO define the return type and local variables
	frog_int keySize = (frog_int)strlen(key);
	frog_int keyIndex = 0;
	frog_int outputIndex = 0;
	frog_int inputChar;

	// TO_DO: Check defensive programming
	if (inputFileName == NULL || key == NULL) {
		errorPrint("Error: Null argument passed.\n");
		 return NULL;
	}

	if (encode != CYPHER && encode != DECYPHER) {
		errorPrint("Error: Invalid operation. Use 'CYPHER' or 'DECYPHER'.\n");
		 return NULL;
	}

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

	FILE* inputFile = fopen(inputFileName, "r");
	if (!inputFile) {
		errorPrint("Error: Could not open input file '%s'.\n", inputFileName);
		free(output);
		return NULL;
	}

	if (keySize == 0) {
		errorPrint("Error: Key is empty.\n");
		fclose(inputFile);
		free(output);
		return NULL;
	}

	while (inputChar = fgetc(inputFile) != EOF && outputIndex < fileSize ) {
		if (output[outputIndex] >= ASCII_START && output[outputIndex] <= ASCII_END) {
			frog_int keyChar = key[keyIndex % keySize] - ASCII_START;
			frog_int outputChar;

			if (encode == CYPHER) {
				outputChar = (output[outputIndex] - ASCII_START + keyChar) % ASCII_RANGE + ASCII_START;
			} else { // DECYPHER
				outputChar = (output[outputIndex] - ASCII_START - keyChar + ASCII_RANGE) % ASCII_RANGE + ASCII_START;
			}
			output[outputIndex++] = (frog_char)outputChar;
			keyIndex++;
		} else {
			output[outputIndex++] = (frog_char)inputChar;
		}
	}

	// TO_DO: Use the logic to code/decode - consider the logic about visible chars only
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

    // TO_DO: Use the logic to get the size of the file
	if (filename == NULL) {
		errorPrint("Error: Null argument passed.\n");
		return -1;
	}

	FILE* file = fopen(filename, "r");
	frog_int size = 0;

	if (!file) {
		errorPrint("Error: Could not open file '%s'.\n", filename);
		return -1;
	}

	 if (fseek(file, 0, SEEK_END) != 0) {
	 	errorPrint("Error: Could not seek file '%s'.\n", filename);
	 	fclose(file);
	 	return -1;
	 };

	size = (frog_int)ftell(file);
	if (size < 0) {
		errorPrint("Error: Could not tell file position for '%s'.\n", filename);
		fclose(file);
		return -1;
	}

	fclose(file);

    return size;
}