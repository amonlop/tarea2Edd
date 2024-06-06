#ifndef HASHTABLEUSERNAME_SEPARATECHAINING_H
#define HASHTABLEUSERNAME_SEPARATECHAINING_H

#include <iostream>
#include <string>
#include "uni_follower.h"
#include <vector>
#include <unordered_map>
#include "FuncionesHash.h"

using namespace std;

//Tabla Hash ocupando Username como clave, utilizando hashing abierto (encadenamiento separado)
class HashTableUsername_separateChaining {
    private:
        int size;
        vector<unordered_map<long long int, uni_follower>> table; //un unordered_map q simule una lista enlazada de par(clave, valor) dentro del vector principal
        

        //función hash para convertir de una clave String a int
        long long int hashCodeString(string key) {
            unsigned int aux = 2166136261;
            unsigned int aux2 = 16777619;
            unsigned int hash = aux;

            for (int i = 0; i < key.length(); ++i) {
                hash ^= key[i];
                hash *= aux2;
            }

            return hash;
        }

    public:

        HashTableUsername_separateChaining(int size) : size(size) {
            table.resize(size);
        }

        //metodo para insertar valores en la tabla hash
        void insert(string key, uni_follower usuario) {
            long long int hash = hashCodeString(key);
            int index = FuncionesHash::h1(hash, size);
            table[index][hash] = usuario;
        }

        //método para buscar una clave en la tabla hash
        uni_follower* search(string key) {
            long long int hash = hashCodeString(key);
            int index = FuncionesHash::h1(hash, size);
            auto it = table[index].find(hash); // un iterador de par clave,valor
            if (it != table[index].end()) {
                return &it->second;// si la encuentra, devuelve un puntero al valor
            }

            //cout << "Clave: " << key << " no encontrada" << endl;
            return nullptr;
        }

};


#endif