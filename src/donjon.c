#include "debug.h"
#include "test.h"
#include "arc_list.h"
#include "donjon.h"

struct arc * create_arc(const int cost, const int from, const int to)
{
    struct arc * res;
    MALLOC(sizeof(*res), res);

    res->cost = cost;
    res->from = from;
    res->to = to;

    return res;
}

struct donjon * create_donjon(const int nb_room, int * rooms, struct arc_list * arcs)
{
    struct donjon * res;
    MALLOC(sizeof(*res), res);

    res->nb_room = nb_room;
    res->rooms = rooms;
    res->arcs = arcs;

    return res;
}
