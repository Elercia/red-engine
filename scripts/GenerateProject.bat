@ECHO OFF

pushd %~dp0\

call "./bin/premake5.exe" vs2019 --file=RedEngine.lua  

PAUSE