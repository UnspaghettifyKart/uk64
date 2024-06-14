#include <stdio.h>
#include <stdlib.h>
#include "list.h"

void list_init(List *list) {
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

void list_append(List *list, void *data) {
    ListElement *element = malloc(sizeof(ListElement));
    element->data = data;
    element->next = NULL;
    element->prev = list->tail;

    if (list->tail) {
        list->tail->next = element;
    }
    list->tail = element;

    if (!list->head) {
        list->head = element;
    }

    list->size++;
}

void list_remove(List *list, ListElement *element) {
    if (element->prev) {
        element->prev->next = element->next;
    } else {
        list->head = element->next;
    }

    if (element->next) {
        element->next->prev = element->prev;
    } else {
        list->tail = element->prev;
    }

    free(element);
    list->size--;
}

void list_free(List *list) {
    ListElement *element = list->head;
    while (element) {
        ListElement *next = element->next;
        free(element);
        element = next;
    }
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

ListElement *list_iterate(ListElement *element) {
    return element->next;
}