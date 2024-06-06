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
#include <chrono>

using namespace std;

int main(int argc, char** argv) {

    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <HashtableType> <numInsertions>" << endl;
        return 1;
    }

    string tablaHash = argv[1];
    int num_inserciones = atoi(argv[2]);
    int size = 25033; //tamaño tabla hash

    auto start = chrono::high_resolution_clock::now();
    if(tablaHash == "linear") {
        HashTableID_openAddressing tableLinear(size, FuncionesHash::linear_probing);
        loadCVS_ID("universities_followers.csv", tableLinear, num_inserciones);
    } else if(tablaHash == "double") {
        HashTableID_openAddressing tableDoubleHashing(size, FuncionesHash::double_hashing);
        loadCVS_ID("universities_followers.csv", tableDoubleHashing, num_inserciones);
    } else if(tablaHash == "cuadratic") {
        HashTableID_openAddressing tableCuadratic(size, FuncionesHash::quadratic_probing);
        loadCVS_ID("universities_followers.csv", tableCuadratic, num_inserciones);
    } else if(tablaHash == "chaining") {
        HashTableID_separateChaining tableChaining(size);
        loadCVS_ID("universities_followers.csv", tableChaining, num_inserciones);
    } else {
        cout << "Ingrese un método válido " << endl;
        exit(1);
    }
    auto end = chrono::high_resolution_clock::now();
    double duration_double = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    duration_double *= 1e-9; //duracion en segundos

    //guardar tabletype, num_inserciones, duracion
    ofstream outputFile("results_insertions_ID.csv", ios::app);
    if (!outputFile.is_open()) {
        cerr << "Error abriendo el archivo: results_insertions_ID.csv" << endl;
        return 1;
    }
    outputFile << tablaHash << ";" << num_inserciones << ";" << duration_double << endl;
    outputFile.close();

    return 0;
}