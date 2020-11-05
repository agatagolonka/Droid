#include <iostream>
#include "Mithril.h"

Mithril::Mithril()
{

}

Mithril::Mithril(int _id, int _weigth, int _pos_x, int _pos_y, int _dest_x, int _dest_y)
{
    id = _id;
    weigth = _weigth;
    pos_x = _pos_x;
    pos_y = _pos_y;
    dest_x = _dest_x;
    dest_y = _dest_y;
}

std::ostream & operator<<(std::ostream & out, const Mithril & ore)
{
	return out << "Mithril: " << ore.id  << " " << ore.weigth << " " << ore.pos_x << " " << ore.pos_y << " " << ore.dest_x << " " << ore.dest_y;
}
