@ECHO OFF
pushd %~dp0\
call bin\premake5.exe export-compile-commands --file=RedEngine.lua  
popd
PAUSE