@echo off

set PROJECT_DIR=%cd%
set BUILD_DIR=%PROJECT_DIR%\build

if exist "%BUILD_DIR%" (
    echo Lösche den Build-Ordner...
    rmdir /s /q "%BUILD_DIR%"
)

mkdir "%BUILD_DIR%"
cd "%BUILD_DIR%"

cmake -G "MinGW Makefiles" ..

cmake --build . --config Release

echo Starte das Programm...
"%BUILD_DIR%\Zahlenspiel.exe"
