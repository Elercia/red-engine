@ECHO OFF
pushd %~dp0\
call bin\premake5.exe codelite --file=RedEngine.lua  
popd
PAUSE