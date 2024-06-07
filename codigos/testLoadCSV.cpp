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

using namespace std;

//main dedicado a testear (y debugear) búsquedas de datos de forma inicial, y el funcionamiento correcto de las tablasHash 
int main() {

    int n_inserciones = 20000; //num inserciones inicial de usuarios

    //Hash con username
    HashTableUsername_separateChaining tableChaining_username(2033);
    HashTableUsername_openAddressing tableLinear_username(2033, FuncionesHash::linear_probing);
    HashTableUsername_openAddressing tableCuadratic_username(2033, FuncionesHash::quadratic_probing);
    HashTableUsername_openAddressing tableDoubleHashing_username(23033, FuncionesHash::double_hashing);

    //Hash con ID
    HashTableID_separateChaining tableChaining(2033);
    HashTableID_openAddressing tableLinear(2033, FuncionesHash::linear_probing);
    HashTableID_openAddressing tableCuadratic(2033, FuncionesHash::quadratic_probing);
    HashTableID_openAddressing tableDoubleHashing(25333, FuncionesHash::double_hashing);


    // //ejemplo de búsqueda por ID
    // loadCVS_ID("universities_followers.csv", tableDoubleHashing, n_inserciones);

    // double id = stod("762696222");
    // uni_follower* usuario = tableDoubleHashing.search(static_cast<long long int>(id));

    // if(usuario) {
    //     cout << "Usuario encontrado: " << usuario->username << endl;
    // } else {
    //     cout << "Usuario no encontrado" << endl; 
    // }


    // //ejemplo de búsqueda por username
    // loadCVS_Username("universities_followers.csv", tableDoubleHashing_username, n_inserciones);
    
    // string cadena = "mariajosejana";
    // uni_follower* usuario = tableDoubleHashing_username.search(cadena);

    // if(usuario) {
    //     cout << "Usuario encontrado: " << usuario->username << endl;
    //     cout << "id: " << usuario->user_id << endl;
    // } else {
    //     cout << "Usuario: " << cadena << " no encontrado" << endl; 
    // }


    //EJEMPLO DE BUSQUEDA POR unordered_map

    Unordered_m<string> mapa_id;
    loadCVS_Username("universities_followers.csv", mapa_id, 22000);
    string cadena = "mariajosejana";
    uni_follower* usuario = mapa_id.search(cadena);


     if(usuario) {
        cout << "Usuario encontrado: " << usuario->user_id << endl;
    } else {
        cout << "Usuario no encontrado" << endl; 
    }


    return 0;

}


