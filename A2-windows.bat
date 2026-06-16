:: A2 SCRIPT
echo off
echo '-----------------------------------------------'
echo '-        ALGONQUIN COLLEGE - COM - 26S        -'
echo '-----------------------------------------------'
echo '-                                             -'
echo '-     ====                                    -'
echo '-    =                                        -'
echo '-   =       ==   = =  ==  = =   =   ==  ==    -'
echo '-    =     =  = = = = = = = =   ==  =  ==     -'
echo '-     ====  ==  = = = =   = === === =    ==   -'
echo '-                                             -'
echo '-----------------------------------------------'
echo '-[A1: Reader - Andrei Cojocaru / Leo Paquette]-'
echo '-----------------------------------------------'
set "CODE_DIR=%~dp0a1files\code"
set "INPUT_DIR=%~dp0a1files\input"
set "arg=%1"
set "param=2"
if "%arg%"=="" set "arg=%INPUT_DIR%\CODED.txt"
:: del "%INPUT_DIR%\CODED.txt" "%INPUT_DIR%\RESTORED.txt"

gcc "%CODE_DIR%\compilers.c" "%CODE_DIR%\main1coder.c" "%CODE_DIR%\step1coder.c" "%CODE_DIR%\main2reader.c" "%CODE_DIR%\step2reader.c" -o "%CODE_DIR%\compilers"
ping -n 2 127.0.0.1 >nul

"%CODE_DIR%\compilers" 1 1 "%INPUT_DIR%\README.txt" "%arg%"
ping -n 2 127.0.0.1 >nul

"%CODE_DIR%\compilers" 2 "%arg%" > "%INPUT_DIR%\out.txt" 2> "%INPUT_DIR%\err.txt"
ping -n 2 127.0.0.1 >nul

dir "%INPUT_DIR%\out.txt" "%INPUT_DIR%\err.txt"
type "%INPUT_DIR%\out.txt"