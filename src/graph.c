#include <stdlib.h>

#include "debug.h"
#include "test.h"

#include "donjon.h"
#include "graph.h"

int node_array_init(int length, struct s_node_array * res)
{
    MALLOC((sizeof *res), res);
    MALLOC(length * (sizeof res->first), res->first);

    res->length = length;

    return 0;
}

struct s_node * node_array_get(int idx, const struct s_node_array * arr)
{
    if (idx < 0 || idx >= arr->length)
    {
	printf("ERROR: node_array_get: out of bounds\n");
	exit(EXIT_FAILURE);
    }

    return &(arr->first[idx]);
}

void node_array_set(int idx, struct s_node_array * arr, const struct s_node * value)
{
    if (idx < 0 || idx >= arr->length)
    {
	printf("ERROR: node_array_set: out of bounds\n");
	exit(EXIT_FAILURE);
    }

   arr->first[idx] = *value;
}

void node_array_free(struct s_node_array * arr)
{
    DEBUG_SET_S_INT(nb,0);
    int i;

    DEBUG_DO(nb++);
    DEBUG("FREE node_array %d\n", nb);

    for( i = (arr->length - 1); i >= 0; i--)
    {
	DEBUG("FREE elt %d\n", i);
	free(&(arr->first[i]));

	DEBUG_DO(i++);
    }

    DEBUG("FREE %d free main pointer...\n", nb);
    free(arr);

    DEBUG("FREE node_array %d END TASK\n", nb);
}


int add_link_to_node(struct s_node_array * graph, int idx, struct link * link)
{
    struct s_node * node;
    DEBUG("[convert] adding link from [%d] to [%d] with cost [%d]",
	    idx,
	    link->link_to->id,
	    link->cost);

    node = node_array_get(idx, graph);

    if (node->go_to == NULL)
    {
	DEBUGN("[convert] no link found, I add a new one");

	node->go_to = link;
    }
    else
    {
	DEBUGN("[convert] link found, I add in head");

	link->next = node->go_to;
	node->go_to = link;
    }

    return 0;
}


/* converti une structure donjon en un graphe exploitable
 * initialise graph
 */
int convert(struct donjon * doj, struct s_node_array * graph)
{
    int i;
    struct arc_list * arcs;

    DEBUGN("[convert] BEGIN TASK");
    node_array_init(doj->nb_room, graph);

    for( i = 0; i < doj->nb_room; i++)
    {
	DEBUG("[convert] initializing elt %d\n", i);
	struct s_node * n;
	MALLOC(sizeof *n, n);

	n->id = i;
	n->cost = doj->rooms[i];
	n->go_to = NULL;

	node_array_set(i, graph, n);
    }

    DEBUGN("[convert] elements initialized");
    DEBUGN("[convert] initialising links...");

    arcs = doj->arcs;

    while (arcs != NULL)
    {
	struct link * link;
	MALLOC(sizeof *link, link);

	link->cost = arcs->node->cost;
	link->link_to = node_array_get(arcs->node->to, graph);

	add_link_to_node(graph, arcs->node->from, link);

	arcs = arcs->next;
    }

    DEBUGN("[convert] TASK END");
    return 0;
}


int can_go(int from, int hp, struct s_node_array graph, struct movement * mov)
{
    DEBUGN("[can_go] called with [from=%d, hp=%d]");

    if (hp == 0)
	return NULL; // TODO changer en appel récursif qui se rajoute

    return 1;
}



