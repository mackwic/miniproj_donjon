#include "debug.h"
#include "test.h"
#include "arc_list.h"
#include "donjon.h"

struct arc * create_arc(const int from, const int cost, const int to)
{
    struct arc * res;
    MALLOC(sizeof(*res), res);

    res->cost = cost;
    res->from = from;
    res->to = to;

    return res;
}

void free_arc(struct arc * arc)
{
    DEBUGN("FREE arc");
    free(arc);
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

void free_donjon(struct donjon * doj)
{
    int * ptr1 = doj->rooms, *ptr2;
    DEBUG_SET_INT(i, 0);
    DEBUGN("FREE donjon");

    while (ptr1 != NULL)
    {
	DEBUG("FREE room %d", i);
	ptr2 = ptr1;
	free(ptr2);
	ptr1++;
    }

    DEBUGN("FREE end rooms, calling free on arc_list...");
    free_arc_list(doj->arcs);

    DEBUGN("FREE main pointer");
    free(doj);
    DEBUGN("FREE END TASK");
}

