#ifndef LIST_H
#define LIST_H

#include <stddef.h>
#include <stdbool.h>

// Estructura de un elemento en la lista
struct list_elem {
    struct list_elem *prev;
    struct list_elem *next;
};

// Estructura de la lista
struct list {
    struct list_elem head;
    struct list_elem tail;
};

// Inicializa la lista
void list_init(struct list *list);

// Verifica si la lista está vacía
bool list_empty(const struct list *list);

// Inserta un nuevo elemento al final de la lista
void list_push_back(struct list *list, struct list_elem *elem);

// Inserta un nuevo elemento al principio de la lista
void list_push_front(struct list *list, struct list_elem *elem);

// Elimina y retorna el primer elemento de la lista
struct list_elem *list_pop_front(struct list *list);

// Elimina el elemento de la lista
void list_remove(struct list_elem *elem);

// Macro para obtener el contenedor de un elemento de la lista
#define list_entry(LIST_ELEM, STRUCT, MEMBER) \
    ((STRUCT *) ((uint8_t *) (LIST_ELEM) - offsetof (STRUCT, MEMBER)))

struct list_elem *list_begin(const struct list *list);

struct list_elem *list_end(const struct list *list);

struct list_elem * list_next (struct list_elem *elem);

#endif /* LIST_H */