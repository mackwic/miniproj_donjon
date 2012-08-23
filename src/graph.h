/*
 * Graph.c presente toutes les methodes de deplacement dans le donjon
 * Not Thread safe, pourquoi faire ?
 */

#ifndef _GRAPH_
#define _GRAPH_

struct link
{
    int cost;
    struct s_node * link_to;
    struct link * next;
};

struct s_node
{
    int id;
    int cost;
    struct link * go_to;
};

struct s_node_array
{
    int length;
    struct s_node * first;
};

struct movement
{
    int * rooms; /* tableau de salles visitables */
    int * costs; /* cout de ces visites */
};

/* pour une position donnée, indique les mouvements possibles */
int can_go(int from, int hp, struct donjon * doj, struct movement * mov);

#endif
