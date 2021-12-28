@ECHO OFF
pushd %~dp0\
call bin\premake5.exe gmake2 --file=RedEngine.lua
popd
PAUSE