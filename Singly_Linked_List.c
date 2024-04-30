#include <stdio.h> 
#include <stdlib.h> 
#include <assert.h>

#define SUCCESS             1 
#define TRUE                1 
#define FALSE               0 
#define LIST_INVALID_DATA   2 
#define LIST_EMPTY          3 

struct node{
    int data; 
    struct node* next;
}; 

/* Interface routines */
struct node* create_list(void); 

void insert_start(struct node* p_head_node, int new_data); 
void insert_end(struct node* p_head_node, int new_data); 
int insert_after(struct node* p_head_node, int e_data, int new_data); 
int insert_before(struct node* p_head_node, int e_data, int new_data);

int get_start(struct node* p_head_node, int* p_start_data); 
int get_end(struct node* p_head_node, int* p_end_start); 
int pop_start(struct node* p_head_node, int* p_start_data); 
int pop_end(struct node* p_head_node, int* p_end_data); 
int remove_start(struct node* p_head_node); 
int remove_end(struct node* p_head_node); 
int remove_data(struct node* p_head_node, int r_data); ; 

int get_length(struct node* p_head_node); 
int is_list_empty(struct node* p_head_node); 

void show_list(struct node* p_head_node, char* msg); 
void destroy_list(struct node* p_head_node); 


/* Interlist routines */
struct node* concat_lists(struct node* p_head_1, struct node* p_head_2); 
void append(struct node* p_head_node_1, struct node** pp_head_node_2); 
struct node* get_reversed_list(struct node* p_head_node); 
struct node* merge_lists(struct node* p_head_1, struct node* p_head_2); 
void reverse_list(struct node* p_list); 

/* Helper routines */
struct node* search_node(struct node* p_head_node, int search_data); 
void get_node_and_its_pred(struct node* p_head_node, int search_data,  struct node** pp_node, 
                            struct node** pp_pred_node); 
struct node* get_node(int data); 
void* xmalloc(size_t number_of_bytes); 

int main(void){
    struct node* p_list = NULL; 
    int data; 
    int status; 
    int length; 

    puts("SINGLY LINKED LIST:"); 

    p_list = create_list(); 
    assert(p_list != NULL); 

    assert(get_start(p_list, &data) == LIST_EMPTY); 
    assert(pop_start(p_list, &data) == LIST_EMPTY); 
    assert(get_end(p_list, &data) == LIST_EMPTY); 
    assert(pop_end(p_list, &data) == LIST_EMPTY); 
    assert(remove_start(p_list) == LIST_EMPTY); 
    assert(remove_end(p_list) == LIST_EMPTY); 
    assert(get_length(p_list) == 0); 
    assert(is_list_empty(p_list) == TRUE); 
    puts("testing, get_start(), pop_start(), get_end(), pop_end(), remove_start(), remove_end() on empty list...OK"); 
    puts("testing, get_length() on empty list ... ok ");
    puts("testing, is_list_empty() on empty list ... ok"); 
    show_list(p_list, "testing, empty list"); 

    for(data = 0; data <= 40; data = data + 10)
        insert_start(p_list, data); 

    show_list(p_list, "testing, insert_start()"); 

    for(data = 50; data <= 100; data = data + 10)
        insert_end(p_list, data); 

    show_list(p_list, "testing, insert_end()"); 

    puts("testing, insert_after() for false case"); 
    status = insert_after(p_list, -300, 500); 
    assert(status == LIST_INVALID_DATA); 
    puts("testing, insert_after() false case... ok"); 

    puts("testing insert_before() for false case"); 
    status = insert_before(p_list, 8976, 500); 
    assert(status == LIST_INVALID_DATA); 
    puts("testing, insert_before() false case ... ok"); 

    puts("testing insert_after() and insert_before() for valid data"); 
    status = insert_after(p_list, 0, 1000); 
    assert(status == SUCCESS); 
    status = insert_before(p_list, 0, 2000); 
    assert(status == SUCCESS); 

    show_list(p_list, "test, insert_after(), insert_before()... ok"); 

    status = get_start(p_list, &data); 
    assert(status == SUCCESS); 
    printf("START OF LIST = %d\n", data); 
    show_list(p_list, "showing list after get_start()"); 

    status = get_end(p_list, &data); 
    assert(status == SUCCESS); 
    printf("END OF LIST = %d\n", data); 
    show_list(p_list, "showing list after get_end()"); 

    status = pop_start(p_list, &data); 
    assert(status == SUCCESS); 
    printf("START OF LIST = %d\n", data); 
    show_list(p_list, "showing list after pop_start()"); 

    status = pop_end(p_list, &data); 
    assert(status == SUCCESS); 
    printf("END OF LIST = %d\n", data); 
    show_list(p_list, "showing list after pop_end()"); 

    status = remove_start(p_list); 
    assert(status == SUCCESS); 
    show_list(p_list, "showing list after remove_start()"); 

    status = remove_end(p_list); 
    assert(status == SUCCESS); 
    show_list(p_list, "showing list after remove_end()"); 

    puts("testing, get_start(), pop_start(), get_end(), pop_end(), remove_start(), remove_end() on non-empty list...OK"); 

    length = get_length(p_list); 
    printf("length = %d\n", length); 

    puts("testing remove_data() for false case"); 
    status = remove_data(p_list, 1234); 
    assert(status == LIST_INVALID_DATA); 
    puts("testing remove data for false case ... ok"); 

    puts("testing remove_data() for success case"); 
    status = remove_data(p_list, 0); 
    assert(status == SUCCESS); 
    puts("testing remove data for success case ... ok"); 
    show_list(p_list, "showing list after removing 0"); 

    assert(is_list_empty(p_list) == FALSE); 
    puts("testing, is_list_empty() for non-empty list...ok"); 

    destroy_list(p_list); 
    p_list = NULL;

    struct node* p_list_1 = create_list(); 
    struct node* p_list_2 = create_list(); 

    for(data = 10; data <= 50; data += 10)  
        insert_end(p_list_1, data); 

    for(data = 15; data <= 85; data += 10)
        insert_end(p_list_2, data); 

    struct node* p_concat_list = concat_lists(p_list_1, p_list_2); 

    show_list(p_list_1, "List 1:"); 
    show_list(p_list_2, "List 2:"); 
    show_list(p_concat_list, "Concatenated list"); 

    struct node* merge_list =  merge_lists(p_list_1,p_list_2);
    show_list(merge_list,"merged list");

    struct node* p_reversed_list = get_reversed_list(p_list_2); 
    show_list(p_reversed_list, "Reversed version of list 2"); 

    
    append(p_list_1, &p_list_2); 
    assert(p_list_2 == NULL); 
    show_list(p_list_1, "After appending list 2 to list 1"); 

    destroy_list(p_list_1); 
    p_list_1 = NULL; 

    destroy_list(p_concat_list); 
    p_concat_list = NULL; 

    destroy_list(p_reversed_list); 
    p_reversed_list = NULL; 

    puts("exiting from application:SUCCESS"); 
    return (EXIT_SUCCESS); 
}

struct node* create_list(void){
    struct node* p_head_node = NULL; 

    p_head_node = get_node(0); 
    
    return (p_head_node); 
}

void insert_start(struct node* p_head_node, int new_data)
{
    struct node* p_new_node = NULL; 

    p_new_node = get_node(new_data); 
    p_new_node->next = p_head_node->next; 
    p_head_node->next = p_new_node; 
}

void insert_end(struct node* p_head_node, int new_data)
{
    struct node* last_node = NULL; 

    last_node = p_head_node; 
    while(last_node->next != NULL)
        last_node = last_node->next; 
    last_node->next = get_node(new_data); 
}

int insert_after(struct node* p_head_node, int e_data, int new_data)
{
    struct node* e_node = NULL;
    struct node* new_node = NULL; 

    e_node = search_node(p_head_node, e_data); 
    if(e_node == NULL)
        return (LIST_INVALID_DATA); 

    new_node = get_node(new_data); 
    new_node->next = e_node->next; 
    e_node->next = new_node; 

    return (SUCCESS); 
}

int insert_before(struct node* p_head_node, int e_data, int new_data)
{
    struct node* e_node = NULL; 
    struct node* e_node_pred = NULL; 
    struct node* new_node = NULL; 

    get_node_and_its_pred(p_head_node, e_data, &e_node, &e_node_pred); 
    if(e_node == NULL)
        return (LIST_INVALID_DATA); 

    new_node = get_node(new_data); 
    new_node->next = e_node;
    e_node_pred->next = new_node; 
     
    return (SUCCESS); 
}

int get_start(struct node* p_head_node, int* p_start_data)
{

    if(p_head_node->next == NULL)
        return (LIST_EMPTY); 

    *p_start_data = p_head_node->next->data; 
    return (SUCCESS); 
}

int get_end(struct node* p_head_node, int* p_end_data)
{
    struct node* run = NULL; 

    if(p_head_node->next == NULL)
        return (LIST_EMPTY); 

    run = p_head_node; 
    while(run->next != NULL)
        run = run->next; 

    *p_end_data = run->data; 
    return (SUCCESS); 
}

int pop_start(struct node* p_head_node, int* p_start_data)
{
    struct node* tmp_ptr = NULL; 

    if(p_head_node->next == NULL) 
        return (LIST_EMPTY); 

    tmp_ptr = p_head_node->next; 
    *p_start_data = tmp_ptr->data; 
    p_head_node->next = tmp_ptr->next; 
    free(tmp_ptr); 
    tmp_ptr = NULL; 

    return (SUCCESS); 
}

int pop_end(struct node* p_head_node, int* p_end_data)
{
    struct node* last_node = NULL; 
    struct node* last_node_pred = NULL; 

    if(p_head_node->next == NULL)
        return (LIST_EMPTY); 

    last_node_pred = p_head_node; 
    last_node = p_head_node->next; 

    while(last_node->next != NULL)
    {
        last_node_pred = last_node; 
        last_node = last_node->next; 
    }

    *p_end_data = last_node->data; 
    free(last_node); 
    last_node = NULL; 

    last_node_pred->next = NULL; 
    return (SUCCESS); 
}

int remove_start(struct node* p_head_node)
{
    struct node* tmp_ptr = NULL; 

    if(p_head_node->next == NULL) 
        return (LIST_EMPTY); 

    tmp_ptr = p_head_node->next; 
    p_head_node->next = tmp_ptr->next; 
    free(tmp_ptr); 
    tmp_ptr = NULL; 

    return (SUCCESS); 
}

int remove_end(struct node* p_head_node)
{
    struct node* last_node = NULL; 
    struct node* last_node_pred = NULL; 

    if(p_head_node->next == NULL)
        return (LIST_EMPTY); 

    last_node_pred = p_head_node; 
    last_node = p_head_node->next; 

    while(last_node->next != NULL)
    {
        last_node_pred = last_node; 
        last_node = last_node->next; 
    }

    free(last_node); 
    last_node = NULL; 

    last_node_pred->next = NULL; 
    return (SUCCESS); 
}

int remove_data(struct node* p_head_node, int r_data)
{
    struct node* run = NULL; 
    struct node* run_pred = NULL; 

    run_pred = p_head_node; 
    run = p_head_node->next; 
    while(run != NULL)
    {
       
        if(run->data == r_data)
            break; 

        run_pred = run; 
        run = run->next; 
    }

    if(run == NULL)
        return (LIST_INVALID_DATA); 

    run_pred->next = run->next; 
    free(run); 

    return (SUCCESS); 
}

int get_length(struct node* p_head_node)
{
    int n_length = 0; 
    struct node* run = NULL; 

    run = p_head_node->next; 
    while(run != NULL)
    {
        n_length += 1; 
        run = run->next; 
    }

    return (n_length); 
}

int is_list_empty(struct node* p_head_node)
{
    return (p_head_node->next == NULL); 
}

void show_list(struct node* p_head_node, char* msg)
{
    struct node* run = NULL; 
    
    if(msg != NULL)
        puts(msg); 

    printf("[START]->"); 
    run = p_head_node->next; 
    while(run != NULL)
    {
        printf("[%d]->", run->data); 
        run = run->next; 
    }
    puts("[END]"); 
}

void destroy_list(struct node* p_head_node)
{
    struct node* run = NULL; 
    struct node* run_next = NULL; 

    run = p_head_node; 
    while(run != NULL)
    {
        run_next = run->next; 
        free(run); 
        run = run_next; 
    }
}

struct node* concat_lists(struct node* p_head_1, struct node* p_head_2)
{
    struct node* p_cat_list = NULL; 
    struct node* run = NULL; 

    p_cat_list = create_list(); 

    for(run = p_head_1->next; run != NULL; run = run->next)
        insert_end(p_cat_list, run->data); 
    for(run = p_head_2->next; run != NULL; run = run->next)
        insert_end(p_cat_list, run->data);

    return (p_cat_list); 
}

struct node* merge_lists(struct node* p_head_1, struct node* p_head_2)
{
    struct node* p_merged_list = NULL; 
    struct node* run1 = NULL; 
    struct node* run2 = NULL; 

    p_merged_list = create_list(); 
    run1 = p_head_1->next; 
    run2 = p_head_2->next; 

    while(TRUE)
    {
        if(run1 == NULL)
        {
            while(run2 != NULL)
            {
                insert_end(p_merged_list, run2->data); 
                run2 = run2->next; 
            }

            break; 
        }

        if(run2 == NULL)
        {
            while(run1 != NULL)
            {
                insert_end(p_merged_list, run1->data); 
                run1 = run1->next; 
            }

            break; 
        }

        if(run1->data <= run2->data)
        {
            insert_end(p_merged_list, run1->data); 
            run1 = run1->next; 
        }
        else
        {
            insert_end(p_merged_list, run2->data); 
            run2 = run2->next; 
        }
    }

    return (p_merged_list); 
}

void append(struct node* p_head_node_1, struct node** pp_head_node_2)
{
    struct node* run = NULL; 
    struct node* p_head_node_2 = *pp_head_node_2;

    run = p_head_node_1;
    while(run->next != NULL)
        run = run->next;

    run->next = p_head_node_2->next; 
    free(p_head_node_2); 
    p_head_node_2 = NULL; 
    *pp_head_node_2 = NULL; 
}

struct node* get_reversed_list(struct node* p_head_node)
{
    struct node* p_reversed_list = NULL; 
    struct node* run = NULL; 

    p_reversed_list = create_list(); 

    for(run = p_head_node->next; run != NULL; run = run->next)
        insert_start(p_reversed_list, run->data); 

    return (p_reversed_list); 
}

void reverse_list(struct node* p_list)
{
    struct node* original_first_node = NULL; 
    struct node* run = NULL; 
    struct node* run_next = NULL; 

    if(p_list->next == NULL || p_list->next->next == NULL)
        return; 

    original_first_node = p_list->next; 

    run = p_list->next->next; 
    while(run != NULL)
    {
        run_next = run->next;

        run->next = p_list->next; 
        p_list->next = run;

        run = run_next; 
    }

    original_first_node->next = NULL; 
}

struct node* search_node(struct node* p_head_node, int search_data)
{
    struct node* run = NULL; 

    run = p_head_node->next; 
    while(run != NULL)
    {
        if(run->data == search_data)
            break; 
        run = run->next; 
    }

    return (run); 
}

void get_node_and_its_pred(
    struct node* p_head_node,
    int search_data, 
    struct node** pp_node, 
    struct node** pp_pred_node
)
{
    struct node* run = NULL; 
    struct node* run_pred = NULL; 

    run_pred = p_head_node; 
    run = p_head_node->next; 

    while(run != NULL)
    {
        if(run->data == search_data)
        {
            *pp_node = run; 
            *pp_pred_node = run_pred; 
            return; 
        }

        run_pred = run; 
        run = run->next; 
    }

    *pp_node = NULL; 
}

struct node* get_node(int data)
{
    struct node* p_new_node = NULL; 

    p_new_node = (struct node*)xmalloc(sizeof(struct node)); 
    p_new_node->data = data; 
    p_new_node->next = NULL; 

    return (p_new_node); 
}

void* xmalloc(size_t number_of_bytes)
{
    void* ptr = NULL; 

    ptr = malloc(number_of_bytes); 
    if(ptr == NULL)
    {
        puts("Error in allocating memory"); 
        exit(EXIT_FAILURE); 
    }

    return (ptr); 
}

