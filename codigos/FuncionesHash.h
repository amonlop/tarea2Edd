#ifndef FUNCIONESHASH_H
#define FUNCIONESHASH_H

#include <iostream>
#include <cmath>

using namespace std;


//Clase que reúne las funciones hash utilizadas por las tablas hash, para la reutilización de código
class FuncionesHash {

    public:
        static const float A;
        
        static int h1(long long int key, int size) {
            return key % size;
        }

        // Método de la multiplicación
        // key: clave a la cual aplicaremos la función hash
        // size: tamaño de la tabla hash
        static int h2(long long int key, int size) {
            float a = (float)key * A;
            a -= (int)a; // Esta línea implementa la operación módulo 1 (%1)

            return size * a;
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
            return (h1(k, n) + i * (h2(k, n) + 1)) % n;
        }

};

const float FuncionesHash::A = (sqrt(5) - 1) / 2;


#endif