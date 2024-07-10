@echo off
for /R %1 %%i in (%2) do (
    echo %%i
    echo %%i>>%3
)
set "first=" 
<nul (for /f "delims=" %%a in (%3) do (
    if defined first (echo() else (set "first=1") 
    set /p ".=%%a" 
)) > %4
del %3