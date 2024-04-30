#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define TRUE 1
#define FALSE 0
#define LIST_EMPTY 2
#define LIST_INVALID_DATA 3
#define SUCCESS 4

struct node
{
    int data;
    struct node *next;
};

typedef struct node list_t;
typedef list_t node_t;
typedef int data_t;
typedef int status_t;
typedef int len_t;

/*INTERFACE FUNCTION*/
list_t *create_list(void);
void show_list(list_t *p_list, char *msg);
status_t destroy_list(list_t *p_list);
status_t insert_start(list_t *p_list, data_t new_data);
status_t insert_end(list_t *p_list, data_t new_data);
status_t insert_after(list_t *p_list, data_t e_data, data_t new_data);
status_t insert_before(list_t *p_list, data_t e_data, data_t new_data);
status_t pop_start(list_t *p_list, data_t *p_data);
status_t pop_end(list_t *p_list, data_t *p_data);
status_t get_start(list_t *p_list, data_t *p_data);
status_t get_end(list_t *p_list, data_t *p_data);
status_t remove_start(list_t *p_list);
status_t remove_end(list_t *p_list);
status_t remove_data(list_t *p_list, data_t e_data);
status_t is_list_empty(list_t *p_list);
status_t get_length(list_t *p_list);

list_t* concat(list_t *p_list_1, list_t *p_list_2);
void reverse_list(list_t* p_list);
list_t* get_reversed_list(list_t* p_list);
void append(list_t* p_list_1,list_t** pp_list_2);
list_t* merge_list(list_t* p_head_1,list_t* p_head_2);


/*HELPER FUNCTION*/
void *xmalloc(size_t size_in_bytes);
node_t *get_node(data_t new_data);
node_t *search_data(list_t *p_list, data_t e_data);
void get_node_and_pred(list_t *p_list, data_t e_data, node_t **pp_e_node, node_t **pp_pred_node);
void generic_insert(node_t *start_node, node_t *new_node);
void generic_delete(node_t *start_node, node_t *delete_node);

int main(void)
{

    list_t *p_list_1 = NULL;
    list_t *p_list_2 = NULL;
    list_t *concat_list_1_and_2 = NULL;
    list_t* revers_list = NULL;
    data_t data;
    status_t status;
    len_t length;

    p_list_1 = create_list();
    for (int i = 10; i <= 40; i = 10 + i)
    {
        insert_end(p_list_1, i);
    }
    show_list(p_list_1, "showing first list");

    p_list_2 = create_list();
    for (int i = 5; i <= 55; i = 10 + i)
    {
        insert_end(p_list_2, i);
    }
    show_list(p_list_2, "showing second list");

    list_t* merged_list = NULL;
    merged_list = merge_list(p_list_1,p_list_2);
    show_list(merged_list,"merged_list");

    reverse_list(p_list_1);
    show_list(p_list_1,"showing reverse_list");

    revers_list = get_reversed_list(p_list_2);
    show_list(revers_list, "showing get reversed list");

    concat_list_1_and_2 = concat(p_list_1, p_list_2);
    show_list(concat_list_1_and_2, "showing the concatenated linked list ");

    append(p_list_1,&p_list_2);
    show_list(p_list_1,"append");

    destroy_list(p_list_1);
    destroy_list(p_list_2);
    destroy_list(concat_list_1_and_2);

    return (EXIT_SUCCESS);
}

/*INTERFACE FUNCTION*/

list_t *create_list(void)
{
    list_t *p_list = NULL;
    p_list = get_node(0);

    p_list->next = p_list;
    return (p_list);
}
void show_list(list_t *p_list, char *msg)
{
    node_t *trav = NULL;
    trav = p_list->next;

    if (msg)
        puts(msg);
    printf("START->");
    while (trav != p_list)
    {
        printf("[%d]->", trav->data);
        trav = trav->next;
    }
    puts("END\n");
}
status_t destroy_list(list_t *p_list)
{
    node_t *trav = NULL;
    node_t *trav_next = NULL;
    trav = p_list;
    while (trav->next != p_list)
    {
        trav_next = trav->next;
        free(trav);
        trav = trav_next;
    }

    return (SUCCESS);
}
status_t insert_start(list_t *p_list, data_t new_data)
{

    generic_insert(p_list, get_node(new_data));
    return (SUCCESS);
}
status_t insert_end(list_t *p_list, data_t new_data)
{
    node_t *trav = NULL;
    trav = p_list;

    while (trav->next != p_list)
    {
        trav = trav->next;
    }

    generic_insert(trav, get_node(new_data));
    return (SUCCESS);
}
status_t insert_after(list_t *p_list, data_t e_data, data_t new_data)
{
    node_t *e_node = NULL;
    if (p_list->next == p_list)
        return (LIST_EMPTY);

    e_node = search_data(p_list, e_data);
    if (e_node == NULL)
        return (LIST_INVALID_DATA);

    generic_insert(e_node, get_node(new_data));

    return (SUCCESS);
}
status_t insert_before(list_t *p_list, data_t e_data, data_t new_data)
{
    node_t *e_node = NULL;
    node_t *prev_node = NULL;
    if (p_list->next == p_list)
        return (LIST_EMPTY);

    get_node_and_pred(p_list, e_data, &e_node, &prev_node);
    if (e_node == NULL)
        return (LIST_INVALID_DATA);

    generic_insert(prev_node, get_node(new_data));
    return (SUCCESS);
}
status_t pop_start(list_t *p_list, data_t *p_data)
{
    if (p_list->next == p_list)
        return (LIST_EMPTY);

    *p_data = p_list->next->data;
    generic_delete(p_list, p_list->next);
    return (SUCCESS);
}
status_t pop_end(list_t *p_list, data_t *p_data)
{
    node_t *trav = NULL;
    trav = p_list;
    if (p_list->next == p_list)
        return (LIST_EMPTY);

    while (trav->next->next != p_list)
    {
        trav = trav->next;
    }

    *p_data = trav->next->data;
    generic_delete(trav, trav->next);
    return (SUCCESS);
}

status_t get_start(list_t *p_list, data_t *p_data)
{
    if (p_list->next == p_list)
        return (LIST_EMPTY);

    *p_data = p_list->next->data;
    return (SUCCESS);
}
status_t get_end(list_t *p_list, data_t *p_data)
{
    node_t *trav = NULL;
    trav = p_list;
    if (p_list->next == p_list)
        return (LIST_EMPTY);

    while (trav->next != p_list)
    {
        trav = trav->next;
    }

    *p_data = trav->data;
    return (SUCCESS);
}
status_t remove_start(list_t *p_list)
{
    if (p_list->next == p_list)
        return (LIST_EMPTY);

    generic_delete(p_list, p_list->next);
    return (SUCCESS);
}
status_t remove_end(list_t *p_list)
{
    node_t *trav = NULL;
    trav = p_list;
    if (p_list->next == p_list)
        return (LIST_EMPTY);

    while (trav->next->next != p_list)
    {
        trav = trav->next;
    }

    generic_delete(trav, trav->next);
    return (SUCCESS);
}
status_t remove_data(list_t *p_list, data_t e_data)
{
    node_t *e_node = NULL;
    node_t *prev_node = NULL;
    if (p_list->next == p_list)
        return (LIST_EMPTY);

    get_node_and_pred(p_list, e_data, &e_node, &prev_node);
    if (e_node == NULL)
        return (LIST_INVALID_DATA);

    generic_delete(prev_node, e_node);
    return (SUCCESS);
}
status_t is_list_empty(list_t *p_list)
{
    return (p_list->next == p_list);
}
status_t get_length(list_t *p_list)
{
    node_t *trav = NULL;
    trav = p_list->next;
    data_t count = 0;
    while (trav != p_list)
    {
        count += 1;
        trav = trav->next;
    }

    return (count);
}
list_t *concat(list_t *p_list_1, list_t *p_list_2)
{
    node_t *run = NULL;
    list_t *p_concat_list = NULL;

    p_concat_list = create_list();

     run = p_list_1->next;
     while (run != p_list_1)
     {
        insert_end(p_concat_list,run->data);
        run = run->next;
     }

     run= p_list_2->next;
     while (run != p_list_2)
      {
         insert_end(p_concat_list,run->data);
         run = run->next;
      }

    return (p_concat_list);
}
void append(list_t* p_list_1,list_t** pp_list_2)
{
    node_t* run = NULL;
    node_t* p_list_2 = *pp_list_2;

    if(p_list_2->next != p_list_2 )
    {    
        run = p_list_1;
        while(run->next != p_list_1)
            run = run->next;
    
        run->next = p_list_2->next;

        run = p_list_2;
        while(run->next != p_list_2)
            run = run->next;

        run->next = p_list_1;
    }

    free(*pp_list_2);
    *pp_list_2 = NULL;

    p_list_2 = NULL;
    run = NULL;
}
list_t* get_reversed_list(list_t* p_list)
{
    node_t* run = NULL;
    list_t* reversed_list = NULL;

    reversed_list = create_list();
    run = p_list->next;
    while(run != p_list)
    {
        insert_start(reversed_list,run->data);
        run = run->next;
    }
    return(reversed_list);
}
void reverse_list(list_t* p_list)
{
    node_t* run = NULL;
    node_t* run_next = NULL;
    node_t* original_first_node = NULL;

    if(p_list->next == p_list || p_list->next->next == p_list)
       return;

    original_first_node = p_list->next;
    run = p_list->next->next;
    while(run != p_list)
    {
        run_next = run->next;

        run->next = p_list->next;
        p_list->next = run;

        run = run_next;

    }   
    original_first_node->next = p_list;
    return;
}
list_t* merge_list(list_t* p_head_1,list_t* p_head_2)
{
    list_t* merged_list = NULL;
    node_t* run1 = NULL;
    node_t* run2 = NULL;

    merged_list = create_list();
    run1 = p_head_1->next;
    run2 = p_head_2->next;

    while(TRUE)
    {
        if(run1 == p_head_1)
        {
            while(run2 != p_head_2)
            {
                 insert_end(merged_list,run2->data);
                 run2 = run2->next;
            }
            break;
        }

        if(run2 == p_head_2)
        {
            while(run1 != p_head_1)
            {
                insert_end(merged_list,run1->data);
                run1 = run1->next;
            }
            break;
        }

        if(run1->data <= run2->data)
        {
            insert_end(merged_list,run1->data);
            run1 = run1->next;
        }
        else
        {
            insert_end(merged_list,run2->data);
            run2 = run2->next;
        }
    }

    return(merged_list);
}
/*HELPER FUNCTION*/

void *xmalloc(size_t size_in_bytes)
{
    void *ptr = NULL;
    ptr = malloc(size_in_bytes);
    assert(ptr != NULL);

    return (ptr);
}
node_t *get_node(data_t new_data)
{
    node_t *p_new_node = NULL;
    p_new_node = (node_t *)xmalloc(sizeof(node_t));

    p_new_node->data = new_data;
    p_new_node->next = NULL;

    return (p_new_node);
}
node_t *search_data(list_t *p_list, data_t e_data)
{
    node_t *trav = NULL;
    trav = p_list->next;
    while (trav != p_list)
    {
        if (trav->data == e_data)
            return (trav);

        trav = trav->next;
    }

    return (NULL);
}

void get_node_and_pred(list_t *p_list, data_t e_data, node_t **pp_e_node, node_t **pp_pred_node)
{
    node_t *trav = NULL;
    node_t *trav_prev = NULL;
    trav = p_list->next;
    trav_prev = p_list;
    while (trav != p_list)
    {
        if (trav->data == e_data)
        {
            *pp_e_node = trav;
            *pp_pred_node = trav_prev;
            return;
        }
        trav_prev = trav;
        trav = trav->next;
    }

    *pp_e_node = NULL;
}
void generic_insert(node_t *start_node, node_t *new_node)
{
    new_node->next = start_node->next;
    start_node->next = new_node;
}
void generic_delete(node_t *start_node, node_t *delete_node)
{
    start_node->next = delete_node->next;
    free(delete_node);
    delete_node = NULL;
}
