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

//50 llaves existentes y no existentes
vector<string> existing_keys = {"ntejos", "ComprensLectora", "NicoleAriasA", "historiausach", "edonogamoz", "patocerdaciudad", "Gab_TorresP", "magdalena_espinoza", "Kimiojvm", "laougi", "mielopata", "DarkandChriss","Manimule", "matiaszf", "Daniel_SaenzM", "Cristia70473301", "jany1180", "Portenhisima", "NidiaNatalia", "nicooadk", "McarolinaTapiat", "Marqt_global", "ClaudioSotoV1", "BaezCepeda", "benvalen2", "Valenti13967348", "RodrigoElDuque", "jotamesi", "PabliToty", "PACorreaR", "MARIELA64206914", "MefistofelesR", "frantzvegaruiz", "surena_de", "Alejandroseguri", "JorgeUlloaz", "profpinto", "Chanchifran1", "Vivianaramjel", "glisethbb", "Margaritasercov", "paulavallejos", "Lubeln6", "AnalisisUfro", "OpazoVioleta", "NicolaCastellvi", "Gringrid", "SeremiCienciaCS", "camren_narnia", "shifure"};

vector<string> non_existing_keys = {"abcs", "abcs1", "abcs2", "abcs3", "abcs4", "abcs5", "abcs6", "abcs7", "abcs8", "abcs9", "abcs10", "abcs11", "abcs12", "abcs13", "abcs14", "abcs15", "abcs16", "abcs17", "abcs18", "abcs19", "abcs20", "abcs21", "abcs22", "abcs23", "abcs24", "abcs25", "abcs26", "abcs27", "abcs28", "abcs29", "abcs30", "abcs31", "abcs32", "abcs33", "abcs34", "abcs35", "abcs36", "abcs37", "abcs38", "abcs39", "abcs40", "abcs41", "abcs42", "abcs43", "abcs44", "abcs45", "abcs46", "abcs47", "abcs48", "abcs49"};

template <typename HashTable>
//Función que calcula el tiempo promedio de realizar 50 búsquedas, expresado en nanosegundos (ns)
double calc_tiempo_prom(HashTable& hashtable, vector<string> llaves) {
    double sum_tiempo = 0.0;
    for(string key : llaves) {
        auto start = chrono::high_resolution_clock::now();
        hashtable.search(key);
        auto end = chrono::high_resolution_clock::now();
        double duration_each = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        sum_tiempo += duration_each;
    }

    sum_tiempo /= llaves.size();
    return sum_tiempo;
}


//main que recibe argumentos al ejecutarse, para calcular el tiempo de búsqueda promedio de 50 datos. Se calcula el tiempo de ejecución (en nanosegundos) utilizando el username como clave
/*
    HashtableType: tipo de tabla hash a realizar búsquedas de elementos
*/
int main(int argc, char** argv) {

    //type_search es {1,0}, 1 para buscar usuarios existentes, 0 para buscar usuarios no existentes
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <HashtableType>" << endl;
        return 1;
    } 

    string tablaHash = argv[1];
    int num_inserciones = 21500; //número grande para insertar todos los usuarios
    int size = 25033; //tamaño tabla hash

    double tiempo_existing; //tiempo que demora la estructura en consultar claves existentes
    double tiempo_non_existing;//tiempo que demora la estructura en consultar claves no existentes

    if(tablaHash == "linear") {
        HashTableUsername_openAddressing tableLinear(size, FuncionesHash::linear_probing);
        loadCVS_Username("universities_followers.csv", tableLinear, num_inserciones);
        tiempo_existing = calc_tiempo_prom(tableLinear, existing_keys);
        tiempo_non_existing = calc_tiempo_prom(tableLinear, non_existing_keys);

    } else if(tablaHash == "double") {
        HashTableUsername_openAddressing tableDoubleHashing(size, FuncionesHash::double_hashing);
        loadCVS_Username("universities_followers.csv", tableDoubleHashing, num_inserciones);
        tiempo_existing = calc_tiempo_prom(tableDoubleHashing, existing_keys);
        tiempo_non_existing = calc_tiempo_prom(tableDoubleHashing, non_existing_keys);

    } else if(tablaHash == "cuadratic") {
        HashTableUsername_openAddressing tableCuadratic(size, FuncionesHash::quadratic_probing);
        loadCVS_Username("universities_followers.csv", tableCuadratic, num_inserciones);
        tiempo_existing = calc_tiempo_prom(tableCuadratic, existing_keys);
        tiempo_non_existing = calc_tiempo_prom(tableCuadratic, non_existing_keys);

    } else if(tablaHash == "chaining") {
        HashTableUsername_separateChaining tableChaining(size);
        loadCVS_Username("universities_followers.csv", tableChaining, num_inserciones);
        tiempo_existing = calc_tiempo_prom(tableChaining, existing_keys);
        tiempo_non_existing = calc_tiempo_prom(tableChaining, non_existing_keys);

    } else if(tablaHash == "unordered_map") {
        Unordered_m<string> mapa;
        loadCVS_Username("universities_followers.csv", mapa, num_inserciones);
        tiempo_existing = calc_tiempo_prom(mapa, existing_keys);
        tiempo_non_existing = calc_tiempo_prom(mapa, non_existing_keys);

    } else {
        cout << "Ingrese un método válido " << endl;
        exit(1);
    }

    //guardar tabletype, tiempo_prom_existing_user, tiempo_prom_non_existing, duracion en un archivo csv
    ofstream outputFile("results_search_username.csv", ios::app);
    if (!outputFile.is_open()) {
        cerr << "Error abriendo el archivo: results_search_username.csv" << endl;
        return 1;
    }
    outputFile << tablaHash << ";" << tiempo_existing << ";" << tiempo_non_existing << endl;
    outputFile.close();

    return 0;

}