@echo off
setlocal EnableDelayedExpansion

:: Auto-detect .exe file (first match)
for %%f in (*.exe) do (
    if not defined EXE_NAME set EXE_NAME=%%f
)

:: If no .exe found, prompt to compile
if not defined EXE_NAME (
    echo ❌ No .exe file found in current folder.
    pause
    exit /b
)

:menu
cls
echo ====================================
echo 🛠 Competitive Programming Toolkit
echo ====================================
echo 🔍 Detected Executable: %EXE_NAME%
echo.
echo 1. Run Auto-Test (tests/input*.txt)
echo 2. Run Stress Tester (needs gen.exe, brute.exe)
echo 3. Interactive Input Test
echo 4. Post-Contest Cleanup
echo 5. Exit
echo ====================================
set /p choice=Enter your choice (1-5): 

if "%choice%"=="1" (
    python auto_test.py %EXE_NAME%
    pause
    goto menu
)
if "%choice%"=="2" (
    python stress_test.py %EXE_NAME%
    pause
    goto menu
)
if "%choice%"=="3" (
    python interactive_test.py %EXE_NAME%
    pause
    goto menu
)
if "%choice%"=="4" (
    set /p ccode=Enter contest code (e.g. 1857): 
    python cleanup.py !ccode!
    pause
    goto menu
)
if "%choice%"=="5" (
    exit /b
)

echo ❌ Invalid choice. Try again.
pause
goto menu
