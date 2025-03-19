#include <iostream>
#include <memory>

using namespace std;

struct node_t{
    int value;
    unique_ptr<node_t> next;

};

struct list_t{
    unique_ptr<node_t> head;
    unique_ptr<node_t> tail;
    size_t size;
};

struct list_iter_t{
    unique_ptr<list_t> list;
    unique_ptr<node_t> curr;
};

unique_ptr<node_t> create_node(int value){
    //tengo que verificar que se haya creado el nodo?
    unique_ptr<node_t> new_node = make_unique<node_t>();
    new_node->value = value;
    new_node->next = nullptr;
    return move(new_node);
}

unique_ptr<list_t> create_list(){
    unique_ptr<list_t> list = make_unique<list_t>();
    list->head = nullptr;
    list->tail =nullptr;
    list->size = 0;
}

bool list_is_empty(const unique_ptr<list_t> list){
    return list->size == 0;
}

void push_front(int value, unique_ptr<list_t> list){
    unique_ptr<node_t> new_node = create_node(value);
    if(list_is_empty){
        list->tail = move(new_node);
    }
    new_node->next = move(list->head); 
    list->head = move(new_node);
    list->size++;
}

void push_back(int value, unique_ptr<list_t> list){
    unique_ptr<node_t> new_node = create_node(value);
    if(list_is_empty){
        list->head = move(new_node);
    }
    list->tail->next = move(new_node);
    list->tail = move(new_node);
    list->size++;
}

unique_ptr<list_iter_t> list_iter_create_head(unique_ptr<list_t> list){
    unique_ptr<list_iter_t> iter = make_unique<list_iter_t>();
    iter->list = move(list);
    iter->curr = move(list->head);
    return move(iter);
}

unique_ptr<list_iter_t> list_iter_create_tail(unique_ptr<list_t> list){
    unique_ptr<list_iter_t> iter = make_unique<list_iter_t>();
    iter->list = move(list);
    iter->curr = move(list->tail);
    return move(iter);
}

bool list_iter_forward(unique_ptr<list_iter_t> iter){
    if(list_is_empty(iter->list)||!iter->curr->next){return false;}
    iter->curr = iter->curr->next;
    return true;
}



bool insert(int pos, unique_ptr<list_t> list, int value){
    unique_ptr<node_t> new_node = create_node(value);
    if( pos > list->size){
        list->tail->next = move(new_node);
        list->tail = move(new_node);
        return false;
    }
    
    
}