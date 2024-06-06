#ifndef FUNCIONESHASH_H
#define FUNCIONESHASH_H

#include <iostream>
#include <cmath>

using namespace std;

const double A = (sqrt(5.0) - 1.0) / 2.0;


//Clase que reúne las funciones hash utilizadas por las tablas hash, para la reutilización de código
class FuncionesHash {

    public:
        
        static int h1(long long int key, int size) {
            return key % size;
        }

        // Método de la multiplicación
        // key: clave a la cual aplicaremos la función hash
        // size: tamaño de la tabla hash
        static int h2(long long int key, int size) {
            double fractional_part = (key * A) - floor(key * A);
            int result = static_cast<int>(size * fractional_part);
            // cout << "h2 -> key: " << key << ", fractional_part: " << fractional_part << ", result: " << result << endl;
            return (result == 0) ? 1 : result; // Asegurar que h2 no devuelva 0
        }


        // Linear probing
        // k: clave a la cual aplicaremos la función hash
        // n: tamaño de la tabla hash
        // i: número del intento
        static int linear_probing(long long int k, int n, int i) {
            // Utilizando el método de la division
            return (h1(k, n) + i) % n;
        }

        // Quadratic probing
        // k: clave a la cual aplicaremos la función hash
        // n: tamaño de la tabla hash
        // i: número del intento
        static int quadratic_probing(long long int k, int n, int i) {
            // Utilizando el método de la division
            return (h1(k, n) + i + 2*i*i) % n;
        }

        // Double hashing
        // k: clave a la cual aplicaremos la función hash
        // n: tamaño de la tabla hash
        // i: número del intento
        static int double_hashing(long long int k, int n, int i) {
            // Utilizando como primer método el método de la division y luego el
            // método de la multiplicacion
            int h1_val = h1(k, n);
            int h2_val = h2(k, n);
            int index = (h1_val + i * h2_val) % n;
            // cout << "double_hashing -> k: " << k << ", i: " << i << ", h1: " << h1_val << ", h2: " << h2_val << ", index: " << index << endl;
            return index;
        }

};


#endif