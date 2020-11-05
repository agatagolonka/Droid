#include "Droid.h"





Droid::Droid(Planet* _plansza)
{
    id = -1;
    plansza = _plansza;
    odleglosci = new int*[plansza->heigth];
    for(int i=0;i<plansza->heigth;i++)
    {
        odleglosci[i] = new int[plansza->width];
    }
}

bool Droid::canCollect(Mithril* ruda)
{
    if(ruda->weigth<=capacity)
        return true;
    else return false;
}

void Droid::collect(std::string rudy, int inicjatywa)
{
    std::cout << inicjatywa << " C " << rudy;
    energy -= inicjatywa;
}

void Droid::transform(std::string rudy, int inicjatywa)
{
    std::cout << inicjatywa << " T " << rudy;
    energy -= inicjatywa;
}

void Droid::move(char dir, int inicjatywa)
{
    std::cout << inicjatywa << " M " << dir;
    energy -= inicjatywa;
}

void Droid::print_odleglosci()
{
    for(int i=0;i<plansza->heigth;i++)
    {
        for(int j=0;j<plansza->width;j++)
        {
            std::cout<< odleglosci[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void Droid::oblicz_odleglosci(int x,int y)
{
    for(int i=0;i<plansza->heigth;i++)
    {
        for(int j=0;j<plansza->width;j++)
        {
            if(plansza->tablica[i][j]=='^' || plansza->tablica[i][j]=='#')
                odleglosci[i][j] = -1;
            else odleglosci[i][j] = -5;
        }
    }
    odleglosci[y][x] = 0;
    if(y>0)
        if(odleglosci[y-1][x]!=-1)
            odleglosci[y-1][x] = 1;
    if(y<plansza->heigth-1)
        if(odleglosci[y+1][x]!=-1)
            odleglosci[y+1][x] = 1;
    if(x>0)
        if(odleglosci[y][x-1]!=-1)
            odleglosci[y][x-1] = 1;
    if(x<plansza->width-1)
        if(odleglosci[y][x+1]!=-1)
            odleglosci[y][x+1] = 1;

    int licznik=0;

    while (licznik<plansza->width*plansza->heigth)
    {
        for(int i=0;i<plansza->heigth;i++)
        {
            for(int j=0;j<plansza->width;j++)
            {
                if(odleglosci[i][j]==-5)
                {
                    if(j>0)
                    {
                        if(odleglosci[i][j-1]!=-1 && odleglosci[i][j-1]!=-5 && odleglosci[i][j-1]!=0)
                            odleglosci[i][j] = odleglosci[i][j-1]+1;
                    }
                    if(i>0)
                    {
                        if(odleglosci[i-1][j]!=-1 && odleglosci[i-1][j]!=-5 && (odleglosci[i-1][j]!=0))
                            odleglosci[i][j]=odleglosci[i-1][j]+1;
                    }

                    if(j<plansza->width-1)
                    {
                        if (odleglosci[i][j+1]!=-1 && odleglosci[i][j+1]!=-5 && odleglosci[i][j+1]!=0)
                            odleglosci [i][j]=odleglosci[i][j+1]+1;
                    }
                    if(i<plansza->heigth-1)
                    {
                        if(odleglosci[i+1][j]!=-1 && odleglosci[i+1][j]!=-5 && odleglosci[i+1][j]!=0)
                            odleglosci[i][j] = odleglosci[i+1][j]+1;
                    }
                }

            }

        }
        licznik++;
    }
}

Mithril* Droid::wyznaczNajblizszego()
{
    oblicz_odleglosci(x,y);
    int najblizsza = plansza->width + plansza->heigth;
    Mithril* best = 0;
    for( std::list<Mithril*>::iterator it=plansza->rudy_lista.begin(); it!=plansza->rudy_lista.end(); it++ )
    {
        if(najblizsza>odleglosci[(*it)->pos_y][(*it)->pos_x] && (*it)->weigth <capacity)
        {
            best = *it;
            najblizsza = odleglosci[best->pos_y][best->pos_x];
        }
    }
    return best;
}

std::string Droid::wyznaczDroge(int x,int y, int dest_x, int dest_y)
{
    oblicz_odleglosci(x,y);

    std::string droga;
    int wart = odleglosci[dest_y][dest_x];
    while(wart!=0)
    {
        if(dest_y>0 && odleglosci[dest_y-1][dest_x]+1==wart)
        {
            droga += "S";
            dest_y--;
        }
        else if(dest_y<plansza->heigth-1 && odleglosci[dest_y+1][dest_x]+1==wart)
        {
            droga += "N";
            dest_y++;
        }
        else if(dest_x>0 && odleglosci[dest_y][dest_x-1]+1==wart)
        {
            droga += "E";
            dest_x--;
        }
        else if(dest_x<plansza->width-1 && odleglosci[dest_y][dest_x+1]+1==wart)
        {
            droga += "W";
            dest_x++;
        }
        else return 0;
        //std::cout << droga<<std::endl;
        wart--;
    }
    std::string tmp;
    for(int i=droga.length()-1;i>-1;i--)
    {
        tmp += droga.at(i);
    }
    return tmp;
}

void Droid::start()
{
    Mithril* najblizszy = 0;
    std::string droga;
    while(plansza->rudy_lista.size()!=0)
    {
        droga = "";
        najblizszy = wyznaczNajblizszego();
        if(najblizszy!=0)
        {
            if(droga.length()==0)
            {
                droga = wyznaczDroge(x,y,najblizszy->pos_x,najblizszy->pos_y);
            }
            for(int i=0;i<droga.length();i++)
            {
                move(droga.at(i));
                if(droga.at(i)=='W') x--;
                else if(droga.at(i)=='E') x++;
                else if(droga.at(i)=='N') y--;
                else if(droga.at(i)=='S') y++;
                std::cout << std::endl;
                std::cin.getline(tmp_in,1000);
            }
            std::ostringstream tmp;
            tmp << najblizszy->id;
            plansza->rudy_lista.remove(najblizszy);
            rudy_lista.push_back(najblizszy);
            int cap = capacity - najblizszy->weigth;
            for( std::list<Mithril*>::iterator it=plansza->rudy_lista.begin(); it!=plansza->rudy_lista.end(); it++ )
            {
                if((*it) != najblizszy && x == (*it)->pos_x && y == (*it)->pos_y && (*it)->weigth <cap)
                {
                    tmp << " ";
                    tmp << (*it)->id;
                    cap -= (*it)->weigth;
                    rudy_lista.push_back(*it);
                    plansza->rudy_lista.remove(*it);
                }
            }
            capacity = cap;
            collect(tmp.str());
            std::cout << std::endl;
            std::cin.getline(tmp_in,1000);
        }
        //std::cout << rudy_lista.size();
        while(rudy_lista.size()!=0)
        {

            int najblizsza = plansza->width + plansza->heigth;
            Mithril* best;
            Mithril* best2;
            for( std::list<Mithril*>::iterator it=rudy_lista.begin(); it!=rudy_lista.end(); it++ )
            {
                if(najblizsza>odleglosci[(*it)->dest_y][(*it)->dest_x])
                {
                    best = *it;
                    najblizsza = odleglosci[best->dest_y][best->dest_x];
                }
            }
            int najblizsza2 = plansza->width + plansza->heigth;
            for( std::list<Mithril*>::iterator it=plansza->rudy_lista.begin(); it!=plansza->rudy_lista.end(); it++ )
            {
                if(najblizsza2>odleglosci[(*it)->dest_y][(*it)->dest_x] && (*it)->weigth < capacity)
                {
                    best2 = *it;
                    najblizsza2 = odleglosci[best->dest_y][best->dest_x];
                }
            }
            if(najblizsza<najblizsza2)
                droga = wyznaczDroge(x,y,best->dest_x,best->dest_y);
            else droga =  wyznaczDroge(x,y,best2->pos_x,best2->pos_y);

            for(int i=0;i<droga.length();i++)
            {
                move(droga.at(i));
                if(droga.at(i)=='W') x--;
                else if(droga.at(i)=='E') x++;
                else if(droga.at(i)=='N') y--;
                else if(droga.at(i)=='S') y++;
                std::cout << std::endl;
                std::cin.getline(tmp_in,1000);
            }
            if(najblizsza<najblizsza2)
            {
                std::ostringstream tmp;
                tmp << best->id;
                rudy_lista.remove(best);
                for( std::list<Mithril*>::iterator it=rudy_lista.begin(); it!=rudy_lista.end(); it++ )
                {
                    if(x == (*it)->dest_x && y == (*it)->dest_y)
                    {
                        tmp << " ";
                        tmp << (*it)->id;
                        rudy_lista.remove(*it);
                    }
                }
                transform(tmp.str());
                std::cout << std::endl;
                std::cin.getline(tmp_in,1000);
            }
            else
            {
                std::ostringstream tmp;
                tmp << best2->id;
                plansza->rudy_lista.remove(best2);
                rudy_lista.push_back(best2);
                int cap = capacity - best2->weigth;
                for( std::list<Mithril*>::iterator it=plansza->rudy_lista.begin(); it!=plansza->rudy_lista.end(); it++ )
                {
                    if((*it) != best2 && x == (*it)->pos_x && y == (*it)->pos_y && (*it)->weigth <cap)
                    {
                        tmp << " ";
                        tmp << (*it)->id;
                        cap -= (*it)->weigth;
                        rudy_lista.push_back(*it);
                        plansza->rudy_lista.remove(*it);
                    }
                }
                collect(tmp.str());
                capacity = cap;
                std::cout << std::endl;
                std::cin.getline(tmp_in,1000);
            }

        }



    }
}
