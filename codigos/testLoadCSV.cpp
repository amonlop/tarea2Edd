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

using namespace std;

int main() {

    //Hash con username
    HashTableUsername_separateChaining tableChaining_username(1033);
    HashTableUsername_openAddressing tableLinear_username(1033, FuncionesHash::linear_probing);
    HashTableUsername_openAddressing tableCuadratic_username(1033, FuncionesHash::quadratic_probing);
    HashTableUsername_openAddressing tableDoubleHashing_username(1033, FuncionesHash::double_hashing);

    //Hash con ID
    HashTableID_separateChaining tableChaining(1033);
    HashTableID_openAddressing tableLinear(1033, FuncionesHash::linear_probing);
    HashTableID_openAddressing tableCuadratic(1033, FuncionesHash::quadratic_probing);
    HashTableID_openAddressing tableDoubleHashing(1033, FuncionesHash::double_hashing);


    // loadCVS_ID("universities_followers.csv", tableLinear, tableCuadratic, tableDoubleHashing, tableChaining);

    // //ejemplo de búsqueda por ID
    // double id = stod("1.19827737845325E+018");
    // uni_follower* usuario = tableDoubleHashing.search(static_cast<long long int>(id));

    // if(usuario) {
    //     cout << "Usuario encontrado: " << usuario->username << endl;
    // } else {
    //     cout << "Usuario no encontrado" << endl; 
    // }

    //ejemplo de búsqueda por username
    loadCVS_Username("universities_followers.csv", tableLinear_username, tableCuadratic_username, tableDoubleHashing_username, tableChaining_username);
    
    string cadena = "Gringrid";
    uni_follower* usuario = tableLinear_username.search(cadena);

    if(usuario) {
        cout << "Usuario encontrado: " << usuario->username << endl;
        cout << "id: " << usuario->user_id << endl;
    } else {
        cout << "Usuario no encontrado" << endl; 
    }

    return 0;

}


