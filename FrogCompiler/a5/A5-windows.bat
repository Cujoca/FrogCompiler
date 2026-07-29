:: A4 SCRIPT
echo off
echo '------------------------------------------------'
echo '-        ALGONQUIN COLLEGE - COM - 26S         -'
echo '------------------------------------------------'
echo '-                                              -'
echo '-     ====                                     -'
echo '-    =                                         -'
echo '-   =       ==   = =  ==  = =   =   ==  ==     -'
echo '-    =     =  = = = = = = = =   ==  =  ==      -'
echo '-     ====  ==  = = = =   = === === =    ==    -'
echo '-                                              -'
echo '------------------------------------------------'
echo '-[A5: Writer - Leo Paquette / Andrei Cojocaru] -'
echo '------------------------------------------------'
set "CODE_DIR=%~dp0..\code"
set "INPUT_DIR=%~dp0..\input"
set "OUTPUT_DIR=%~dp0..\output"

:: Parameter is the plaintext Frog source file (in INPUT_DIR) to encode and parse.
:: Defaults to the Frog sample program if none is given.
:: Set the src file to FrogHello.txt/FrogControlFlow.txt/FrogFunctions.txt for valid input and FrogErrors.txt for invalid input.
set "src=%1"
if "%src%"=="" set "src=FrogHello.txt"
set "coded=%INPUT_DIR%\CODED.txt"

gcc "%CODE_DIR%\compilers.c" "%CODE_DIR%\main1coder.c" "%CODE_DIR%\step1coder.c" "%CODE_DIR%\main2reader.c" "%CODE_DIR%\step2reader.c" "%CODE_DIR%\main3scanner.c" "%CODE_DIR%\step3scanner.c" "%CODE_DIR%\main4parser.c" "%CODE_DIR%\step4parser.c" "%CODE_DIR%\main5writer.c" "%CODE_DIR%\step5writer.c" -o "%CODE_DIR%\compilers"
ping -n 2 127.0.0.1 >nul

"%CODE_DIR%\compilers" 1 1 "%INPUT_DIR%\%src%" "%coded%"
ping -n 2 127.0.0.1 >nul

"%CODE_DIR%\compilers" 5 "%coded%" > "%OUTPUT_DIR%\out.txt" 2> "%OUTPUT_DIR%\err.txt"
ping -n 2 127.0.0.1 >nul

dir "%OUTPUT_DIR%\out.txt" "%OUTPUT_DIR%\err.txt"
type "%OUTPUT_DIR%\out.txt"
