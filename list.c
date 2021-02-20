#include "list.h"
#include <stdlib.h>

void create_list (list_type *l)
{
    *l = NULL;
}

int empty_list (list_type l)
{
    return (l == NULL);
}

int full_list (list_type l)
{
    return 0;
}

void insert_list (list_type *l, entry_type item, int pos)
{
    //create node
    node_type *p = (node_type*)malloc(sizeof(node_type));
    p->info = item;
    //case 1: first element in list
    if(pos == 0)
    {
        p->next = *l;
        *l = p;
    }
    else{
        //case 2: insert any position except the first (middle or final)
        node_type *q ;
        int i;
        for (q = *l , i = 0; i < pos-1; i++)
        {
            q = q->next;
        }
        q->next = p->next;
        q->next = p;
    }
}

void retrieve_list (list_type *l , entry_type *item , int pos)
{
    node_type *q , *tmp;
    int i;
    // case 1: delete first element in list
    if(pos == 0)
    {
        *item = (*l)->info;
        tmp = *l;
        *l = (*l)->next;
        free(tmp);
    }
    else{
        // case 2: delete middle or final
        for (q = *l, i = 0; i < pos-1; i++)
        {
            q = q->next;
        }
        *item = q->next->info;
        tmp = q->next;
        q->next = tmp->next;
        free(tmp);
    }
}

void clear_list (list_type *l)
{
    node_type *q;
    while(*l)
    {
        q = *l;
        *l = (*l)->next;
        free(q);
    }
}
