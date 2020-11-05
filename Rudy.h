#ifndef RUDY_H_INCLUDED
#define RUDY_H_INCLUDED

#include <iostream>
#include <string>

class Rudy
{
    public:
        int id;
        int pos_x;
        int pos_y;
        int dest_x;
        int dest_y;
        int weigth;

    public:
        Rudy();
        Rudy(int _id, int _weigth, int _pos_x, int _pos_y, int _dest_x, int _dest_y);

        friend std::ostream & operator<<(std::ostream & out, const Rudy & ore);


};


#endif // RUDY_H_INCLUDED
