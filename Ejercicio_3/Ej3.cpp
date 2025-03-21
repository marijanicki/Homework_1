#include "Ej3.h"
#include <iostream>
#include <memory>

using namespace std;

struct node_t{
    int value;
    shared_ptr<node_t> next;

};

struct list_t{
    shared_ptr<node_t> head;
    shared_ptr<node_t> tail;
    size_t size;
};

shared_ptr<node_t> create_node(int value){
    shared_ptr<node_t> new_node = make_shared<node_t>();
    new_node->value = value;
    new_node->next = nullptr;
    return new_node;
}

shared_ptr<list_t> create_list(){
    shared_ptr<list_t> list = make_shared<list_t>();
    list->head = nullptr;
    list->tail =nullptr;
    list->size = 0;
    return list;
}

bool list_is_empty(const shared_ptr<list_t> list){
    return list->size == 0;
}

void push_front(int value, shared_ptr<list_t> list){
    shared_ptr<node_t> new_node = create_node(value);
    if(list_is_empty(list)){
        list->tail = new_node;
    }
    new_node->next = list->head; 
    list->head = new_node;
    list->size++;
}

void push_back(int value, shared_ptr<list_t> list){
    shared_ptr<node_t> new_node = create_node(value);
    if(list_is_empty(list)){
        list->head = new_node;
        list->tail = new_node;
        list->size++;
        return;
    }
    list->tail->next = new_node;
    list->tail = new_node;
    list->size++;
    return;
}

void list_pop_head(shared_ptr<list_t> list){
    if(list_is_empty(list)){return;}
    //si hay un solo nodo estaría liberando el head y el tail ya que son el mismo
    if(!list->head->next){
        list->head = nullptr;
        list->tail = nullptr;
        list->size--;
        return;
    }

    shared_ptr<node_t> aux = list->head;
    list->head = aux->next;
    if(!list->head){list->tail = nullptr;}
    list->size--;
}

void list_pop_tail(shared_ptr<list_t> list){
    if(list_is_empty(list)){return;} 
    if(!list->head->next){
        list->head = nullptr;
        list->tail = nullptr;
        list->size--;
        return;
    }

    shared_ptr<node_t> curr = list->head;
    while(curr->next->next){
        //Voy iterando sobre la lista hasta llegar al anterior del ultimo así 
        //puedo reacomodar los punteros de manera sencilla y no tengo que 
        //volver a recorrer para 
        curr = curr->next;
    }
    curr->next = nullptr; //así elimino el último nodo, en vez de apuntar a al tail a punta a null indicando que es el nuevo tail
    list->tail = curr;
    list->size--;
}

bool insert(int pos, shared_ptr<list_t> list, int value){
    
    if(static_cast<size_t>(pos)> list->size){
        push_back(value, list);
        return false;
    }
    else if(pos == 0){
        push_front(value, list);
        return true;
    }
    else{
        shared_ptr<node_t> new_node = create_node(value);
        shared_ptr<node_t> curr = list->head;
        for( int i = 0; i<pos-1; i++){
            curr = curr->next;
        }
        new_node->next =curr->next;
        curr->next = new_node;
        list->size++;
        return true;
    }
}

bool erase(shared_ptr<list_t> list, int pos){
    if(list_is_empty(list)){return false;}
    //en caso de que haya un unico nodo borro el head ya que tambien va a borrar el tail
    if(static_cast<size_t>(pos) >= list->size){
        list_pop_tail(list);
        return false;
    }
    else if(pos == 0){
        list_pop_head(list);
        return true;
    }
    else{
        shared_ptr<node_t> curr = list->head;
        for( int i = 0; i<pos-1; i++){
            //voy iterando hasta llegar al anterior del nodo que quiero eliminar
            curr = curr->next;
        }
        shared_ptr<node_t> aux = curr->next; //es el nodo que quiero eliminar
        curr->next = aux->next;
        aux = nullptr;
        list->size--;
        return true;
    }
}

void print_list(shared_ptr<list_t> list){
    shared_ptr<node_t> curr = list->head;
    while(curr){
        if(!curr->next){
            cout << curr->value<<endl;
        }
        else{
            cout << curr->value << "->";
        }
        curr = curr->next;
    }

}

int main(){
    shared_ptr<list_t> list= create_list();
    cout<<"Se inserta un elemento en una posición mayor al largo de la lista:"<<endl;
    insert(1, list, 5);
    print_list(list);
    cout<<"Se inserta un elemento al final de la lista"<<endl;
    push_back(8,list);
    print_list(list);
    cout<<"Se ingresa un elemento en el inicio de la lista"<<endl;
    push_front(6,list);
    print_list(list);
    cout<<"Se quiere eliminar un elemento en una posición mayor al largo de la lista"<<endl;
    erase(list, 3);
    print_list(list);
    cout<<"Se inserta un elemento en la mitad de la lista"<<endl;
    insert(1,list,9);
    print_list(list);
    cout<<"Se elimina la cabeza de la lista"<<endl;
    erase(list,0);
    print_list(list);
    cout<<"Se inserta un elemento al final de la lista"<<endl;
    insert(2, list, 4);
    print_list(list);
    cout<<"Se elimina el último elemento de la lista"<<endl;
    erase(list, 2);
    print_list(list);
    cout<<"Se elimina toda la lista"<<endl;
    
    while(list->head){
        erase(list, 0); //l epongo pos 0 ya que al ir borrando los elementos en el head va a haber uno distinto en cada iteración
        if(list->head){
            print_list(list);
        }
        else{
            cout<<"NULL"<<endl;
        }
    }
    cout<<"Se intenta eliminar un elemento con la lista vacia (no se imprime nada)"<<endl;
    erase(list,0);
    print_list(list);
    cout<<"Despues de dejar a la lista vacia se pueden insertar elementos igual"<<endl;
    insert(1,list,3);
    print_list(list);
} 
