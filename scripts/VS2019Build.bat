@ECHO OFF
pushd %~dp0\
echo "Building %1"
msbuild "scripts/projects/vs2019/RedEngine.sln" /t:Build /p:Configuration=%1 /p:Platform=Win64
popd