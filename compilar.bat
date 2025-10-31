@echo off
REM Script de compilación y prueba para Windows
REM Sistema IoT de Sensores - Sofia Cano

echo ========================================
echo   Sistema IoT de Sensores
echo   Script de Compilación Automática
echo ========================================
echo.

REM Verificar CMake
echo [1/5] Verificando CMake...
cmake --version >nul 2>&1
if %errorlevel% neq 0 (
    echo [ERROR] CMake no está instalado o no está en el PATH
    echo Por favor, instale CMake desde https://cmake.org/download/
    pause
    exit /b 1
)
echo [OK] CMake encontrado

REM Verificar compilador
echo.
echo [2/5] Verificando compilador...
g++ --version >nul 2>&1
if %errorlevel% neq 0 (
    cl >nul 2>&1
    if %errorlevel% neq 0 (
        echo [ERROR] No se encontró compilador C++
        echo Instale MinGW o Visual Studio
        pause
        exit /b 1
    ) else (
        echo [OK] MSVC encontrado
    )
) else (
    echo [OK] MinGW encontrado
)

REM Crear directorio build
echo.
echo [3/5] Creando directorio de compilación...
if exist build (
    echo Limpiando directorio build anterior...
    rmdir /s /q build
)
mkdir build
cd build

REM Generar archivos de compilación
echo.
echo [4/5] Generando archivos de compilación con CMake...
cmake .. -G "MinGW Makefiles"
if %errorlevel% neq 0 (
    echo [ERROR] Falló la generación con CMake
    cd ..
    pause
    exit /b 1
)
echo [OK] Archivos generados

REM Compilar
echo.
echo [5/5] Compilando proyecto...
cmake --build .
if %errorlevel% neq 0 (
    echo [ERROR] Falló la compilación
    cd ..
    pause
    exit /b 1
)

echo.
echo ========================================
echo   COMPILACIÓN EXITOSA!
echo ========================================
echo.
echo El ejecutable está en: build\SistemaIoTSensores.exe
echo.
echo Para ejecutar:
echo   cd build
echo   .\SistemaIoTSensores.exe
echo.
echo ========================================

cd ..
pause
