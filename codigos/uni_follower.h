#ifndef UNI_FOLLOWER_H
#define UNI_FOLLOWER_H

#include <iostream>
#include <string>

using namespace std;

//struct que representa a los usuarios que siguen distintas universidades
//cada uni_follower representa una fila del dataset
struct uni_follower {
    long long int user_id; //único
    string username;    // único
    string university;
    int number_tweets;
    int friends_count;
    int followers_count;
    string created_at;

};

#endif