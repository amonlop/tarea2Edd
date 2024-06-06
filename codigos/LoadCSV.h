#ifndef LOADCSV_H
#define LOADCSV_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "uni_follower.h"
#include <vector>
#include <cmath>
#include "HashTableID_openAddressing.h"
#include "HashTableID_separateChaining.h"
#include "HashTableUsername_openAddressing.h"
#include "HashTableUsername_separateChaining.h"


template<typename HashTable>
//funcion que carga el archivo csv en las tablas hash, utilizando el ID como clave, con un numero máximo de n_inserciones
void loadCVS_ID(const string& filename, HashTable& hashtable, int num_inserciones) {

    ifstream file(filename);

    if(!file.is_open()) {
        cerr << "Error al abrir el archivo .csv" << endl;
        return;
    }

    string linea; //fila del archivo
    getline(file, linea); //se elimina la primera fila (de los campos)

    int i = 0;
    while (getline(file, linea) && i < num_inserciones) {
        stringstream ss(linea);
        string cadena;
        uni_follower usuario;

        //se obtienen los distintos campos de la fila leída
        getline(ss, cadena, ',');
        usuario.university = cadena;
        getline(ss, cadena, ',');
        //realizar un casteo de los números en notación científica
        double usuario_id_double = stod(cadena);
        usuario.user_id = static_cast<long long int>(usuario_id_double);
        getline(ss, cadena, ',');
        usuario.username = cadena;
        getline(ss, cadena, ',');
        usuario.number_tweets = stoi(cadena);
        getline(ss, cadena, ',');
        usuario.friends_count = stoi(cadena);
        getline(ss, cadena, ',');
        usuario.followers_count = stoi(cadena);
        getline(ss, cadena, ',');
        usuario.created_at = cadena;

        hashtable.insert(usuario.user_id, usuario);

        //para debug
        // cout << "usuario_id: " << usuario.user_id << endl;
        // cout << "username: " << usuario.username << endl;
        // cout << "number_tweets: " << usuario.number_tweets << endl;
        // cout << "friends_count: " << usuario.friends_count << endl;
        // cout << "followers_count: " << usuario.followers_count << endl;
        // cout << "created_at: " << usuario.created_at << endl;
        i++;
    }
    //cout << i << endl;

    file.close();
}


template<typename HashTable>
//funcion que carga el archivo csv en las tablas hash, utilizando el username como clave, con un número máximo n_inserciones de usuarios
void loadCVS_Username(const string& filename, HashTable& hashtable, int num_inserciones) {

    ifstream file(filename);

    if(!file.is_open()) {
        cerr << "Error al abrir el archivo .csv" << endl;
        return;
    }

    string linea; //fila del archivo
    getline(file, linea); //se elimina la primera fila (de los campos)

    int i = 0;
    while (getline(file, linea) && i < num_inserciones) {
        stringstream ss(linea);
        string cadena;
        uni_follower usuario;

        //se obtienen los distintos campos de la fila leída
        getline(ss, cadena, ',');
        usuario.university = cadena;
        getline(ss, cadena, ',');
        //realizar un casteo de los números en notación científica
        double usuario_id_double = stod(cadena);
        usuario.user_id = static_cast<long long int>(usuario_id_double);
        getline(ss, cadena, ',');
        usuario.username = cadena;
        getline(ss, cadena, ',');
        usuario.number_tweets = stoi(cadena);
        getline(ss, cadena, ',');
        usuario.friends_count = stoi(cadena);
        getline(ss, cadena, ',');
        usuario.followers_count = stoi(cadena);
        getline(ss, cadena, ',');
        usuario.created_at = cadena;

        hashtable.insert(usuario.username, usuario);

        //para debug
        // cout << "usuario_id: " << usuario.user_id << endl;
        // cout << "username: " << usuario.username << endl;
        // cout << "number_tweets: " << usuario.number_tweets << endl;
        // cout << "friends_count: " << usuario.friends_count << endl;
        // cout << "followers_count: " << usuario.followers_count << endl;
        // cout << "created_at: " << usuario.created_at << endl;
        i++;
    }

    //cout << i << endl; //para comprobar el número de usuarios leídos
    file.close();

}


#endif