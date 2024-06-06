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

//50 llaves
vector<long long int> existing_keys = {414942137, 995799091, 119157522, 107828392, 3157777815, 779200093, 105278779, 3342070079, 197969660, 1859685872, 3308253918, 3085046392, 99004019, 1326167888, 72700410, 344881817, 287800469, 1339542342, 3407892076, 2511129368, 1400303311, 116599554, 3355667831, 395065295, 69738118, 3413894967, 379371536, 15348330, 935258035, 383938430, 2707923709, 123270934, 36474946, 118517827, 2841970690, 199572311, 269403454, 4541323823, 370323325, 2901627227, 441350226, 98511849, 3852383297, 2541707748, 1111920254, 2526807700, 50704286, 401996629, 109476346, 461314902};

vector<long long int> non_existing_keys = {123123123, 1231231, 12311, 390232, 390231, 390234, 390235, 390236, 390237, 390238, 390239, 121111, 121110, 121112, 121113, 121114, 121115, 121116, 121118, 12119, 222221, 222222, 222223, 222224, 222225, 222226, 222227, 222228, 222229, 222220, 12119, 222221, 222222, 222223, 222224, 222225, 222226, 222227, 222228, 222229, 222220, 123123123, 1231231, 12311, 390232, 390231, 390234, 390235, 390236, 390237};

template <typename HashTable>
//Función que calcula el tiempo promedio de realizar una búsqueda, expresado en nanosegundos (ns)
double calc_tiempo_prom(HashTable& hashtable, vector<long long int> llaves) {
    double sum_tiempo = 0.0;
    for(long long int key : llaves) {
        auto start = chrono::high_resolution_clock::now();
        hashtable.search(key);
        auto end = chrono::high_resolution_clock::now();
        double duration_each = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        sum_tiempo += duration_each;
    }

    sum_tiempo /= llaves.size();
    return sum_tiempo;
}


int main(int argc, char** argv) {

    //type_search es {1,0}, 1 para buscar usuarios existentes, 0 para buscar usuarios no existentes
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <HashtableType>" << endl;
        return 1;
    } 

    string tablaHash = argv[1];
    int num_inserciones = 21500; //todos los usuarios
    int size = 25033; //tamaño tabla hash

    double tiempo_existing;
    double tiempo_non_existing;

    if(tablaHash == "linear") {
        HashTableID_openAddressing tableLinear(size, FuncionesHash::linear_probing);
        loadCVS_ID("universities_followers.csv", tableLinear, num_inserciones);
        tiempo_existing = calc_tiempo_prom(tableLinear, existing_keys);
        tiempo_non_existing = calc_tiempo_prom(tableLinear, non_existing_keys);

    } else if(tablaHash == "double") {
        HashTableID_openAddressing tableDoubleHashing(size, FuncionesHash::double_hashing);
        loadCVS_ID("universities_followers.csv", tableDoubleHashing, num_inserciones);
        tiempo_existing = calc_tiempo_prom(tableDoubleHashing, existing_keys);
        tiempo_non_existing = calc_tiempo_prom(tableDoubleHashing, non_existing_keys);

    } else if(tablaHash == "cuadratic") {
        HashTableID_openAddressing tableCuadratic(size, FuncionesHash::quadratic_probing);
        loadCVS_ID("universities_followers.csv", tableCuadratic, num_inserciones);
        tiempo_existing = calc_tiempo_prom(tableCuadratic, existing_keys);
        tiempo_non_existing = calc_tiempo_prom(tableCuadratic, non_existing_keys);

    } else if(tablaHash == "chaining") {
        HashTableID_separateChaining tableChaining(size);
        loadCVS_ID("universities_followers.csv", tableChaining, num_inserciones);
        tiempo_existing = calc_tiempo_prom(tableChaining, existing_keys);
        tiempo_non_existing = calc_tiempo_prom(tableChaining, non_existing_keys);

    } else {
        cout << "Ingrese un método válido " << endl;
        exit(1);
    }

    //guardar tabletype, tiempo_prom_existing_user, tiempo_prom_non_existing, duracion
    ofstream outputFile("results_search_ID.csv", ios::app);
    if (!outputFile.is_open()) {
        cerr << "Error abriendo el archivo: results_search_ID.csv" << endl;
        return 1;
    }
    outputFile << tablaHash << ";" << tiempo_existing << ";" << tiempo_non_existing << endl;
    outputFile.close();

    return 0;

}