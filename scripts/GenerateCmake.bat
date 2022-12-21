@ECHO OFF
pushd %~dp0\
call bin\premake5.exe cmake --file=RedEngine.lua
popd
PAUSE