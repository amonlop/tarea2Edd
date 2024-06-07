#include <iostream>
#include <string>
#include <cmath>
#include "HashTableID_openAddressing.h"
#include "HashTableID_separateChaining.h"
#include "HashTableUsername_openAddressing.h"
#include "HashTableID_separateChaining.h"
#include "LoadCSV.h"
#include "uni_follower.h"
#include "FuncionesHash.h"
#include "Unordered_m.h"
#include <chrono>

using namespace std;

//main que recibe argumentos al ejecutarse, para calcular el tiempo de insercion. Se calcula el tiempo de ejecución (en milisegundos) utilizando el user_id como clave
/*
    HashtableType: tipo de tabla hash a insertar elementos
    numInsertions: número de inserciones a realizar
*/
int main(int argc, char** argv) {

    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <HashtableType> <numInsertions>" << endl;
        return 1;
    }

    string tablaHash = argv[1];
    int num_inserciones = atoi(argv[2]);
    int size = 25033; //tamaño tabla hash
    size_t size_bytes; //tamaño en bytes de la estructura utilizada

    //se empieza a calcular el tiempo de ejecución
    auto start = chrono::high_resolution_clock::now();
    if(tablaHash == "linear") {
        HashTableID_openAddressing tableLinear(size, FuncionesHash::linear_probing);
        loadCVS_ID("universities_followers.csv", tableLinear, num_inserciones);
        size_bytes = tableLinear.sizeInBytes();
    } else if(tablaHash == "double") {
        HashTableID_openAddressing tableDoubleHashing(size, FuncionesHash::double_hashing);
        loadCVS_ID("universities_followers.csv", tableDoubleHashing, num_inserciones);
        size_bytes = tableDoubleHashing.sizeInBytes();
    } else if(tablaHash == "cuadratic") {
        HashTableID_openAddressing tableCuadratic(size, FuncionesHash::quadratic_probing);
        loadCVS_ID("universities_followers.csv", tableCuadratic, num_inserciones);
        size_bytes = tableCuadratic.sizeInBytes();
    } else if(tablaHash == "chaining") {
        HashTableID_separateChaining tableChaining(size);
        loadCVS_ID("universities_followers.csv", tableChaining, num_inserciones);
        size_bytes = tableChaining.sizeInBytes();
    } else if(tablaHash == "unordered_map") {
        Unordered_m<long long int> mapa;
        loadCVS_ID("universities_followers.csv", mapa, num_inserciones);
        size_bytes = mapa.sizeInBytes();
    } else {
        cout << "Ingrese un método válido " << endl;
        exit(1);
    }
    auto end = chrono::high_resolution_clock::now();
    double duration_double = chrono::duration_cast<chrono::milliseconds>(end - start).count();//tiempo en milisegundos que se tarda la inserción de datos

    //duration_double *= 1e-6; //duracion en milisegundos

    //guardar tabletype, num_inserciones, duracion(milisegundos) en un archivo csv
    ofstream outputFile("results_insertions_ID.csv", ios::app);
    if (!outputFile.is_open()) {
        cerr << "Error abriendo el archivo: results_insertions_ID.csv" << endl;
        return 1;
    }
    outputFile << tablaHash << ";" << num_inserciones << ";" << duration_double << ";" << size_bytes << endl;
    outputFile.close();

    return 0;
}