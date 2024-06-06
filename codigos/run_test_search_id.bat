@echo off
setlocal

REM Compilar el programa 
g++ -o test_search_id test_search_id.cpp 

REM Crear el archivo CSV y agregar encabezados (si no existe)
if exist results_search_ID.csv (
    del results_search_ID.csv
)

REM añadir encabezado de los campos al csv
echo HashtableType;avg_time_existing;avg_time_non_existing > results_search_ID.csv

REM Ejecutar pruebas 50 veces para diferentes métodos
for /L %%I in (1,1,50) do (
    echo Test %%I with Linear Probing
    test_search_id.exe linear
    echo Test %%I with Double Hashing
    test_search_id.exe double
    echo Test %%I with Quadratic Probing
    test_search_id.exe cuadratic
    echo Test %%I with Chaining
    test_search_id.exe chaining
)

endlocal
pause