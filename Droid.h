#ifndef DROID_H_INCLUDED
#define DROID_H_INCLUDED

#include <iostream>
#include <string>
#include <sstream>
#include "Rudy.h"
#include "Kierunek.h"
#include "Planet.h"




class Droid
{
    public:
        bool alive;
        int id;
        int energy;
        int capacity;
        int x,y;

        std::list<Rudy*> rudy_lista;
        Planet* plansza;
        int** odleglosci;
        char tmp_in[1000];

        Droid(Planet* _plansza);
        bool canCollect(Rudy* ruda);
        void collect(std::string rudy, int inicjatywa = 1);
        void transform(std::string rudy, int inicjatywa = 1);
        void move(char dir, int inicjatywa = 1);
        void print_odleglosci();
        void oblicz_odleglosci(int x,int y);
        Rudy* wyznaczNajblizszego();
        std::string wyznaczDroge(int x,int y, int dest_x, int dest_y);
        void start();

};


#endif // DROID_H_INCLUDED
