#ifndef HASHTABLEID_OPENADDRESSING.H
#define HASHTABLEID_OPENADDRESSING.H

#include <iostream>
#include <string>
#include <uni_follower.h>
#include <vector>
#include <unordered_map>
#include <cmath>

using namespace std;

const float A = (sqrt(5) - 1) / 2;
//FUNCIONES HASH

int h1(long long int key, int size) {
    return key % size;
}

// Método de la multiplicación
// key: clave a la cual aplicaremos la función hash
// size: tamaño de la tabla hash
int h2(long long int key, int size) {
    float a = (float)key * A;
    a -= (int)a; // Esta línea implementa la operación módulo 1 (%1)

    return size * a;
}


// Linear probing
// k: clave a la cual aplicaremos la función hash
// n: tamaño de la tabla hash
// i: número del intento
int linear_probing(long long int k, int n, int i) {
    // Utilizando el método de la division
    return (h1(k, n) + i) % n;
}

// Quadratic probing
// k: clave a la cual aplicaremos la función hash
// n: tamaño de la tabla hash
// i: número del intento
int quadratic_probing(long long int k, int n, int i) {
    // Utilizando el método de la division
    return (h1(k, n) + i + 2*i*i) % n;
}

// Double hashing
// k: clave a la cual aplicaremos la función hash
// n: tamaño de la tabla hash
// i: número del intento
int double_hashing(long long int k, int n, int i) {
    // Utilizando como primer método el método de la division y luego el
    // método de la multiplicacion
    return (h1(k, n) + i * (h2(k, n) + 1)) % n;
}

class HashTableID_openAddressing {
    private:
        int size;
        vector<pair<long long int, uni_follower>> table;
        int (*hashing_method)(long long int, int, int);


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
                    cout << "Llave: " << key << "no encontrada" << endl;
                    return nullptr;
                }
            }
            if (table[index].first == -1) { //si no encuentra la clave, retorna null
                return nullptr;
            }
            return &table[index].second; //retorna un puntero al usuario encontrado
        }

};


#endif