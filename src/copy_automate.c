#include "automate.h"

t_con   *copy_connection(t_con *con, int id_offset)
{
    t_con   *copy;
    t_con   *cur;

    if (con == NULL)
        return (NULL);
    copy = malloc(sizeof(t_con));
    copy->ett = con->ett;
    copy->to = con->to + id_offset;
    copy->next = NULL;
    con = con->next;
    cur = copy;
    while (con)
    {
        cur->next = malloc(sizeof(t_con));
        cur = cur->next;
        cur->to = con->to + id_offset;
        cur->ett = con->ett;
        cur->next = NULL;
        con = con->next;
    }
    return (copy);
}

t_node  *copy_nodes(t_node *nodes, int size, int id_offset)
{
    t_node  *copy;
    int     i;

    copy = calloc(size + 1, sizeof(t_node));
    i = -1;
    while (++i < size)
    {
        copy[i].id = nodes[i].id + id_offset;
        copy[i].con = copy_connection(nodes[i].con, id_offset);
    }
    copy[i].con = (t_con *)-1;
    return (copy);
}

int get_nodes_size(t_node *nodes)
{
    int size;

    size = 0;
    while(nodes[size].con != (t_con *)-1)
        size++;
    return (size);
}


t_automate  *copy_autmate(t_automate *a, int id_offset)
{
    t_automate  *copy;
    t_node  *node;

    copy = malloc(sizeof(t_automate));
    copy->nodes = copy_nodes(a->nodes, get_nodes_size(a->nodes), id_offset);
    copy->ins = copy_nodes(a->ins, get_nodes_size(a->ins), id_offset);
    copy->outs = copy_nodes(a->outs, get_nodes_size(a->outs), id_offset);
    return (copy);
}
