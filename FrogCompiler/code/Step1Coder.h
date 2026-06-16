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
* File name: Reader.h
* Compiler: MS Visual Studio 2022
* Course: CST 8152 Compilers, Lab Section: 301
* Assignment: A1
* Date: May 31, 2026
* Professor: Vardaan Sangar
* Purpose: This file is the main header for Reader (.h)
************************************************************
*/

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef CODER_H_
#define CODER_H_

 // ASCII range for visible characters
#define ASCII_START 32
#define ASCII_END 126
#define ASCII_RANGE (ASCII_END - ASCII_START + 1)

#define CYPHER 1
#define DECYPHER 0

/* FUNCTIONS DECLARATION:  .................................. */

/* General Operations */
void vigenereFile(const frog_str inputFileName, const frog_str outputFileName, const frog_str key, frog_int encode);
frog_str vigenereMem(const frog_str inputFileName, const frog_str key, frog_int encode);

void cypher(const frog_str inputFileName, const frog_str outputFileName, const frog_str key);
void decypher(const frog_str inputFileName, const frog_str outputFileName, const frog_str key);
frog_int getSizeOfFile(const frog_str filename);

#endif
