:: A1 SCRIPT
echo off
echo '----------------------------------------------'
echo '-       ALGONQUIN COLLEGE - COM - 26W        -'
echo '----------------------------------------------'
echo '-                                            -'
echo '-     ====                                   -'
echo '-    =                                       -'
echo '-   =       ==   = =  ==  = =   =   ==  ==   -'
echo '-    =     =  = = = = = = = =   ==  =  ==    -'
echo '-     ====  ==  = = = =   = === === =   ==   -'
echo '-                                            -'
echo '----------------------------------------------'
echo '-[A1: Coder - Andrei Cojocaru / Leo Paquette]-'
echo '----------------------------------------------'
set "CODE_DIR=%~dp0..\code"
set "INPUT_DIR=%~dp0..\input"
set "arg=%1"
set "param=2"
if "%arg%"=="" set "arg=%INPUT_DIR%\CODED.txt"
del "%INPUT_DIR%\CODED.txt" "%INPUT_DIR%\RESTORED.txt" 2>nul
gcc "%CODE_DIR%\compilers.c" "%CODE_DIR%\main1coder.c" "%CODE_DIR%\step1coder.c" -o "%CODE_DIR%\compilers"
ping -n 2 127.0.0.1 >nul
"%CODE_DIR%\compilers" 1 1 "%INPUT_DIR%\README.txt" "%arg%" > "%~dp0..\output\out.txt" 2> "%~dp0..\output\err.txt"
ping -n 2 127.0.0.1 >nul
"%CODE_DIR%\compilers" 1 0 "%arg%" "%INPUT_DIR%\ORIGINAL.txt" >> "%~dp0..\output\out.txt" 2>> "%~dp0..\output\err.txt"
ping -n 2 127.0.0.1 >nul
dir "%~dp0..\output\out.txt" "%~dp0..\output\err.txt"
type "%~dp0..\output\out.txt"