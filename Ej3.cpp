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
}