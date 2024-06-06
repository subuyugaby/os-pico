#include "list.h"

// Inicializa la lista
void list_init(struct list *list) {
    list->head.next = &list->tail;
    list->tail.prev = &list->head;
    list->head.prev = NULL;
    list->tail.next = NULL;
}

// Verifica si la lista está vacía
bool list_empty(const struct list *list) {
    return list->head.next == &list->tail;
}

// Inserta un nuevo elemento al final de la lista
void list_push_back(struct list *list, struct list_elem *elem) {
    struct list_elem *before = list->tail.prev;
    elem->next = &list->tail;
    elem->prev = before;
    before->next = elem;
    list->tail.prev = elem;
}

// Inserta un nuevo elemento al principio de la lista
void list_push_front(struct list *list, struct list_elem *elem) {
    struct list_elem *after = list->head.next;
    elem->next = after;
    elem->prev = &list->head;
    after->prev = elem;
    list->head.next = elem;
}

// Elimina y retorna el primer elemento de la lista
struct list_elem *list_pop_front(struct list *list) {
    if (list_empty(list)) {
        return NULL;
    }
    struct list_elem *front = list->head.next;
    list_remove(front);
    return front;
}

// Elimina el elemento de la lista
void list_remove(struct list_elem *elem) {
    elem->prev->next = elem->next;
    elem->next->prev = elem->prev;
}

struct list_elem *list_begin(const struct list *list) {
    if (list_empty(list)) {
        return NULL; // Devuelve NULL si la lista está vacía
    } else {
        return list->head.next; // Devuelve un puntero al primer elemento de la lista
    }
}

struct list_elem *list_end(const struct list *list) {
    if (list_empty(list)) {
        return NULL; // Devuelve NULL si la lista está vacía
    } else {
        return list->tail.next; // Devuelve un puntero al primer elemento de la lista
    } // Devuelve el último elemento de la lista
}

struct list_elem * list_next (struct list_elem *elem) {
  return elem->next;
}