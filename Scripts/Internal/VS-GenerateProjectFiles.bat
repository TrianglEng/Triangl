@echo off
pushd %~dp0\..\..\
call .\ThirdParty\Premake\Binaries\windows-x86_64\premake5.exe vs%1
popd
pause
