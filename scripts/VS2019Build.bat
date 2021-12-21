@echo off
echo %1 Build Start

rem Force language to english
set VSLANG=1033 
msbuild.exe "scripts/projects/vs2019/RedEngine.sln" /t:Build /p:Configuration=%1 /p:Platform=Win64 /fileLoggerParameters:encoding=UTF-8

echo %1 Build End