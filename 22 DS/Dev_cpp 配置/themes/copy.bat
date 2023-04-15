@echo off
rem copy syntax to Dev-Cpp
if not exist %HOMEPATH%\AppData\Roaming\Dev-Cpp md %HOMEPATH%\AppData\Roaming\Dev-Cpp
copy *.syntax %HOMEPATH%\AppData\Roaming\Dev-Cpp\*.syntax
pause