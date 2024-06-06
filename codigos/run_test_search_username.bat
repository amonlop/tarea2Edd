@echo off
setlocal

REM Compilar el programa 
g++ -o test_search_username test_search_username.cpp 

REM Crear el archivo CSV y agregar encabezados (si no existe)
if exist results_search_username.csv (
    del results_search_username.csv
)

REM añadir encabezado de los campos al csv
echo HashtableType;avg_time_existing;avg_time_non_existing > results_search_username.csv

REM Ejecutar pruebas 50 veces para diferentes métodos
for /L %%I in (1,1,50) do (
    echo Test %%I with Linear Probing
    test_search_username.exe linear
    echo Test %%I with Double Hashing
    test_search_username.exe double
    echo Test %%I with Quadratic Probing
    test_search_username.exe cuadratic
    echo Test %%I with Chaining
    test_search_username.exe chaining
)

endlocal
pause