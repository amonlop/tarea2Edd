#ifndef UNI_FOLLOWERS.H
#define UNI_FOLLOWERS.H


#include <iostream>
#include <string>

using namespace std;

//struct que representa a los usuarios que siguen distintas universidades
struct uni_followers {
    long long int user_id; //único
    string username;    // único
    string university;
    int number_tweets;
    int friends_count;
    int followers_count;
    string created_at;

};

#endif