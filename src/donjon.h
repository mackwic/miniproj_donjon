#ifndef _donjon_
#define _donjon_

#include "arc_list.h"

enum ROOM_TYPE
{
    ROOM_ORDINARY,
    ROOM_MONSTER,
    ROOM_TRAP,
    ROOM_BREWERY
};

struct arc
{
    int cost;
    int from;
    int to;
};

struct arc * create_arc(const int cost, const int from, const int to);

struct donjon
{
    int nb_room;
    int * rooms;
    struct arc_list * arcs;
};

struct donjon * create_donjon( int nb_room, int * rooms, struct arc_list * arcs);

#endif
