#pragma once
#include <iostream>
#include <memory>

using namespace std;

struct node_t;

struct list_t;

/*
 *Crea un nuevo nodo asignandole su valor correspondiente
 */
shared_ptr<node_t> create_node(int value);

/*
 * Crea una nueva lista.
 */
shared_ptr<list_t> create_list();

/*
 * Devuelve TRUE si la lista está vacia.
 * Pre-condiciones: La lista existe.
 */
bool list_is_empty(const shared_ptr<list_t> list);

/*
 * Inserta un elemento al principio de la lista.
 * Pre-condiciones: La lista existe.
 */
void push_front(int value, shared_ptr<list_t> list);

/*
 * Inserta un elemento al final de la lista.
 * Pre-condiciones: La lista existe.
 */
void push_back(int value, shared_ptr<list_t> list);

/*
 * Elimina un elemento del principio de la lista.
 * Pre-condiciones: La lista existe.
 * Post-condiciones: Saca un nodo del principio de la lista
 * si la lista no está vacia. Devuelve NULL si está vacia.
 */
void list_pop_head(shared_ptr<list_t> list);

/*
 * Elimina un elemento del final de la lista.
 * Pre-condiciones: La lista existe.
 * Post-condiciones: Saca un nodo del final de la lista
 * si la lista no está vacia. Devuelve NULL si está vacia.
 */
void list_pop_tail(shared_ptr<list_t> list);

/*
 * Se inserta un elemento en la posición indicada de la lista. 
 * En caso de que la posición sea mayor al largo de la lista se 
 * inserta el elemento al final.
 * Pre-condiciones: La lista existe.
 */
bool insert(int pos, shared_ptr<list_t> list, int value);

/*
 * Elimina un elemento de la lista en la posición.
 * Pre-condiciones: La lista existe.
 * Post: Elimina el elemento de la posición especificada.
 * En caso de que la posición sea mayor al largo de la lista se 
 * inserta el elemento al final.
 */
bool erase(shared_ptr<list_t> list, int pos);

/*
 *Se imprime la lista.
 */
void print_list(shared_ptr<list_t> list);

