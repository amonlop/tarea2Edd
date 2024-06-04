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


//funcion que carga el archivo csv en las tablas hash, utilizando el ID como clave
void loadCVS_ID(const string& filename, HashTableID_openAddressing& tableLinear, HashTableID_openAddressing& tableCuadratic, HashTableID_openAddressing& tableDoubleHashing, HashTableID_separateChaining& tableChaining) {

    ifstream file(filename);

    if(!file.is_open()) {
        cerr << "Error al abrir el archivo .csv" << endl;
        return;
    }

    string linea; //fila del archivo
    getline(file, linea); //se elimina la primera fila (de los campos)

    int i = 0;
    while (getline(file, linea)) {
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

        //esta condición es para evitar que se sigan insertando elementos cuando las tablas están llenas
        if(i < tableLinear.getSize()) {
            tableLinear.insert(usuario.user_id, usuario);
            tableCuadratic.insert(usuario.user_id, usuario);
            tableDoubleHashing.insert(usuario.user_id, usuario);
        }

        tableChaining.insert(usuario.user_id, usuario);

        //para debug
        // cout << "usuario_id: " << usuario.user_id << endl;
        // cout << "username: " << usuario.username << endl;
        // cout << "number_tweets: " << usuario.number_tweets << endl;
        // cout << "friends_count: " << usuario.friends_count << endl;
        // cout << "followers_count: " << usuario.followers_count << endl;
        // cout << "created_at: " << usuario.created_at << endl;
        i++;
    }

    cout << i << endl; //para comprobar el número de usuarios leídos
    file.close();
}

//funcion que carga el archivo csv en las tablas hash, utilizando el username como clave
void loadCVS_Username(const string& filename, HashTableUsername_openAddressing& tableLinear, HashTableUsername_openAddressing& tableCuadratic, HashTableUsername_openAddressing& tableDoubleHashing, HashTableUsername_separateChaining& tableChaining) {

    ifstream file(filename);

    if(!file.is_open()) {
        cerr << "Error al abrir el archivo .csv" << endl;
        return;
    }

    string linea; //fila del archivo
    getline(file, linea); //se elimina la primera fila (de los campos)

    int i = 0;
    while (getline(file, linea)) {
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

        //esta condición es para evitar que se sigan insertando elementos cuando las tablas están llenas
        if(i < tableLinear.getSize()) {
            tableLinear.insert(usuario.username, usuario);
            tableCuadratic.insert(usuario.username, usuario);
            tableDoubleHashing.insert(usuario.username, usuario);
        }

        tableChaining.insert(usuario.username, usuario);

        //para debug
        // cout << "usuario_id: " << usuario.user_id << endl;
        // cout << "username: " << usuario.username << endl;
        // cout << "number_tweets: " << usuario.number_tweets << endl;
        // cout << "friends_count: " << usuario.friends_count << endl;
        // cout << "followers_count: " << usuario.followers_count << endl;
        // cout << "created_at: " << usuario.created_at << endl;
        i++;
    }

    cout << i << endl; //para comprobar el número de usuarios leídos
    file.close();

}


#endif