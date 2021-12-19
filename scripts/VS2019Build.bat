@echo off
echo %1 Build Start

msbuild.exe "scripts/projects/vs2019/RedEngine.sln" /t:Build /p:Configuration=%1 /p:Platform=Win64

echo %1 Build End