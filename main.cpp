#include <iostream>
#include <vector>
#include <cstdlib>
#include "Planet.h"
#include "Droid.h"
#include "Dir.h"
#include <string>

using namespace std;

int main(int argc, char* argv[])
{
    char tmp[1000];
    if(argc!=6) return 1;

    cin.getline(tmp,1000);
    string pozycja(tmp);

    Planet plansza(argv[4],argv[5]);
    Droid kamil(&plansza);
    kamil.id = atoi(argv[1]);
    kamil.capacity = atoi(argv[2]);
    kamil.energy = atoi(argv[3]);
    int pos = pozycja.find("#"+kamil.id,0);
    int x = atoi(pozycja.substr(pozycja.find("X",pos)+2,pozycja.find("Y",pos)-pozycja.find("X",pos)-3).c_str());
    int y;
    if(pozycja.find("#",pos+3)!=string::npos)
        y = atoi(pozycja.substr(pozycja.find("Y",pos)+2,pozycja.find("#",pos)-pozycja.find("Y",pos)-3).c_str());
    else y = atoi(pozycja.substr(pozycja.find("Y",pos)+2,pozycja.size()-2-pozycja.find("Y",pos)).c_str());
    kamil.x = x;
    kamil.y = y;

    kamil.start();



    return 0;
}


//./NazwiskoImie [id] [capacity] [energy] [plik_z_plansz¹] [plik_ze_z³o¿ami]
