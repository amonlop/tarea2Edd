#ifndef HASHTABLEUSERNAME_OPENADDRESSING_H
#define HASHTABLEUSERNAME_OPENADDRESSING_H

#include <iostream>
#include <string>
#include "uni_follower.h"
#include <vector>
#include <unordered_map>
#include "FuncionesHash.h"

using namespace std;

//Tabla Hash ocupando como clave Username, con hashing cerrado (linear_probing, cuadratic_probing, double_hashing)
class HashTableUsername_openAddressing {
    private:
        int size;
        vector<pair<long long int, uni_follower>> table;
        int (*hashing_method)(long long int, int, int);

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

        HashTableUsername_openAddressing(int size, int (*hashing_method)(long long int, int, int))
            : size(size), hashing_method(hashing_method) {
            table.resize(size, make_pair(-1, uni_follower())); //todos los pair (-1, unifollower)
        }

        //metodo para insertar elementos mientras aún haya espacio
        void insert(string key, uni_follower user) {
            int i = 0;
            long long int hash = hashCodeString(key);
            int index = hashing_method(hash, size, i);
            while (table[index].first != -1) {
                i++;
                index = hashing_method(hash, size, i);
                if (i >= size) {
                    //sin rehashing
                    cout << "Error, tabla llena. No se pueden insertar más elementos" << endl;
                    return;
                }
            }
            table[index] = make_pair(hash, user);
        }

        //método para buscar un usuario a partir de una clave String
        uni_follower* search(string key) {
            int i = 0;
            long long int hash = hashCodeString(key);
            int index = hashing_method(hash, size, i);
            while (table[index].first != hash && table[index].first != -1) {
                i++;
                index = hashing_method(hash, size, i);
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

        int getSize() {
            return size;
        }

};

#endif