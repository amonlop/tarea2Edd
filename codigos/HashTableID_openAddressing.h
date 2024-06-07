#ifndef HASHTABLEID_OPENADDRESSING_H
#define HASHTABLEID_OPENADDRESSING_H

#include <iostream>
#include <string>
#include "uni_follower.h"
#include <vector>
#include <unordered_map>
#include <cmath>
#include "FuncionesHash.h"

using namespace std;

//Tabla Hash con clave User_ID, utilizando métodos de hashing cerrado (linear_probing, cuadratic_probing, double_hashing)
class HashTableID_openAddressing {
    private:
        int size;                                           //tamaño de la tabla
        vector<pair<long long int, uni_follower>> table;    // un vector en que cada casilla tiene un par(clave, valor)
        int (*hashing_method)(long long int, int, int);     //metodo hash a utilizar


    public:
        HashTableID_openAddressing(int size, int (*hashing_method)(long long int, int, int))
            : size(size), hashing_method(hashing_method) {
            table.resize(size, make_pair(-1, uni_follower())); //todos los pair (-1, unifollower)
        }

        //metodo para insertar elementos mientras aún haya espacio
        void insert(long long int key, uni_follower user) {
            int i = 0;
            int index = hashing_method(key, size, i);
            while (table[index].first != -1) {
                i++;
                index = hashing_method(key, size, i);
                if (i >= size) {
                    //sin rehashing
                    cout << "Error, tabla llena. No se pueden insertar más elementos" << endl;
                    return;
                }
            }
            table[index] = make_pair(key, user);
        }

        //método para buscar un usuario a partir de una clave
        uni_follower* search(long long int key) {
            int i = 0;
            int index = hashing_method(key, size, i);
            while (table[index].first != key && table[index].first != -1) {
                i++;
                index = hashing_method(key, size, i);
                if (i >= size) { 
                    //cout << "Clave: " << key << " no encontrada" << endl;
                    return nullptr;
                }
            }
            if (table[index].first == -1) { //si no encuentra la clave, retorna null
                return nullptr;
            }
            return &table[index].second; //retorna un puntero al usuario encontrado
        }


        //devuelve el tamaño en bytes de la tabla
        size_t sizeInBytes() {
            size_t size_vector = sizeof(table) + (table.capacity() * sizeof(pair<long long int, uni_follower>));
            size_t size_elements = 0;
            for (const auto& element : table) {
                size_elements += sizeof(element.first) + sizeof(element.second);
            }
            return sizeof(*this) - sizeof(table) + size_vector + size_elements;
        }

};


#endif