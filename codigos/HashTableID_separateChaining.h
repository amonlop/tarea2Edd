#ifndef HASHTABLEID_SEPARATECHAINING_H
#define HASHTABLEID_SEPARATECHAINING_H

#include <iostream>
#include <string>
#include "uni_follower.h"
#include <vector>
#include <unordered_map>

using namespace std;

//tabla hash utilizando la clave user_ID, con hashing abierto (encadenamiento separado)
class HashTableID_separateChaining {
    private:
        int size;                                                   // tamaño de la tabla
        vector<unordered_map<long long int, uni_follower>> table; //un unordered_map q simule una lista enlazada de par(clave, valor) dentro del vector principal

        //funcion hash h1
        int h1(long long int key) {
            return key % size;
        }

    public:
        //constructor de la clase, recibe el tamaño de la tabla hash
        HashTableID_separateChaining(int size) : size(size) {
            table.resize(size);
        }

        //metodo para insertar valores en la tabla hash
        void insert(long long int key, uni_follower usuario) {
            int index = h1(key);
            table[index][key] = usuario;
        }

        //método para buscar una clave en la tabla hash
        uni_follower* search(long long int key) {
            int index = h1(key);
            auto it = table[index].find(key); // un iterador de par clave,valor
            if (it != table[index].end()) {
                return &it->second;// si la encuentra, devuelve un puntero al valor
            }
            //cout << "Clave: " << key << " no encontrada" << endl;
            return nullptr;
        }

        //método para calcular el tamaño en bytes de la estructura
        size_t sizeInBytes() {
            size_t total_size = sizeof(*this); // tamaño base de la clase
            total_size += table.capacity() * sizeof(unordered_map<long long int, uni_follower>); // tamaño del vector y su capacidad
            for (const auto& chain : table) {
                total_size += chain.size() * (sizeof(long long int) + sizeof(uni_follower)); // tamaño de las claves y valores en el unordered_map
            }
            return total_size;
        }

};


#endif