#
# CMakeList.txt : CMake project for Compilers, include source and define project specific logic here.
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


cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("compilers")

# Add source to this project's executable.
add_executable (Compilers
	"Compilers.h"		"Compilers.c"
	"Step1Coder.h"		"Step1Coder.c"		"Main1Coder.c"
	"Step2Reader.h"		"Step2Reader.c"		"Main2Reader.c"
	"Step3Scanner.h"	"Step3Scanner.c"	"Main3Scanner.c"
	"Step4Parser.h"		"Step4Parser.c"		"Main4Parser.c"
		"Step5Writer.h"		"Step5Writer.c"		"Main5Writer.c"

)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Compilers PROPERTY CXX_STANDARD 20)
endif()

# The Writer (A5) interprets recursive Frog function calls via real recursive
# C calls (evalCall -> runFunction -> runStatements -> ... -> evalCall), and
# guards against unbounded recursion with a MAX_CALL_DEPTH check - but the
# default 1MB thread stack (MSVC and MinGW alike) overflows for real before
# that check's depth of 200 is ever reached, crashing the process instead of
# failing with a clean Frog-level error. Raise the reserved stack well above
# what 200 levels of this interpreter's call chain actually needs.
if (MSVC)
  target_link_options(Compilers PRIVATE "/STACK:8388608")
elseif (CMAKE_C_COMPILER_ID STREQUAL "GNU" OR MINGW)
  target_link_options(Compilers PRIVATE "-Wl,--stack,8388608")
endif()

# TODO: Add tests and install targets if needed.
