@ECHO OFF
pushd %~dp0\..\test
call RedEngineTest.exe
popd
PAUSE