#ifndef PLANSZA_H_INCLUDED
#define PLANSZA_H_INCLUDED

#include <iostream>
#include <string>
#include <list>
#include "Rudy.h"


class Plansza
{
    public:
        int width,heigth;
        char** tablica;
        int ores;
        std::list<Rudy*> rudy_lista;


    public:
        Planet(const char* plansza,const char* rudy);
        void print();


};

#endif


#endif // PLANSZA_H_INCLUDED
