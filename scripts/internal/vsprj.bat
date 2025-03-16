@echo off
pushd %~dp0\..\..\
call vendor\premake\bin\windows-x86_64\premake5.exe vs%1
popd
pause
