#ifndef UNORDERED_M_H
#define UNORDERED_M_H


#include <iostream>
#include <string>
#include "uni_follower.h"
#include <vector>
#include <unordered_map>

using namespace std;

template <typename K>
//clase que solo implementa unordered_map de la STL, con métodos de búsqueda e inserción de datos
class Unordered_m {
    private:
        unordered_map<K, uni_follower> mapa;
    
    public: 
        Unordered_m() {}


        //método para insertar datos, con una clave genérica y un usuario
        void insert(K key, uni_follower usuario) {
            mapa[key] = usuario;
        }

        //método para buscar un usuario, con una clave genérica
        uni_follower* search(K key) {
            auto usuario = mapa.find(key);
            if(usuario != mapa.end()) {
                return &usuario->second;
            }
            return nullptr;
        }

        //método para calcular el tamaño en bytes de la estructura
        size_t sizeInBytes() {
            size_t size_map = sizeof(mapa);
            for (const auto& pair : mapa) {
                size_map += sizeof(pair.first) + sizeof(pair.second);
            }
            return size_map;
        }
        
};


#endif