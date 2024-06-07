@echo off
setlocal

REM Compilar el programa 
g++ -o test_insertion test_insertion.cpp 

REM Crear el archivo CSV y agregar encabezados
if exist results_insertions_ID.csv (
    del results_insertions_ID.csv
)

REM añadir encabezado de los campos al csv
echo HashtableType;numInsertions;duration(ms);size_bytes > results_insertions_ID.csv

REM Ejecutar pruebas 50 veces para diferentes cantidades de inserciones
for /L %%I in (1,1,50) do (
    for %%N in (1000 5000 10000 20000) do (
        echo Test %%I with %%N insertions on Linear Probing
        test_insertion.exe linear %%N
        echo Test %%I with %%N insertions on Double Hashing
        test_insertion.exe double %%N
        echo Test %%I with %%N insertions on Quadratic Probing
        test_insertion.exe cuadratic %%N
        echo Test %%I with %%N insertions on Separate Chaining
        test_insertion.exe chaining %%N
        echo Test %%I with %%N insertions on Unordered Map
        test_insertion.exe unordered_map %%N
    )
)

endlocal
pause