#include <fstream>
#include "Planet.h"

Planet::Planet(const char* plansza,const char* rudy)
{
    std::ifstream in;
    in.open(plansza,std::ios::binary);
    in >> width;
    in >> heigth;
    tablica = new char*[heigth];
    for(int i=0;i<heigth;i++)
    {
        tablica[i] = new char[width];
    }
    for(int i=0;i<heigth;i++)
    {
        std::string line;
        in >> line;
        if(int(line.length())!=width) std::cerr << "bu";
        for(int j=0;j<width;j++)
        {
            tablica[i][j] = line[j];
        }
    }

    in.close();
    in.open(rudy,std::ios::binary);
    in >> ores;
    for(int i=0;i<ores;i++)
    {
        Mithril* tmp = new Mithril();
        in >> tmp->id;
        in >> tmp->weigth;
        in >> tmp->pos_x;
        in >> tmp->pos_y;
        in >> tmp->dest_x;
        in >> tmp->dest_y;
        rudy_lista.push_back(tmp);


    }
}

void Planet::print()
{
    for(int i=0;i<heigth;i++)
    {
        for(int j=0;j<width;j++)
        {
            std::cout << tablica[i][j];
        }
        std::cout << std::endl;
    }
}
