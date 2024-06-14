typedef struct ListElement {
    void *data;
    struct ListElement *next;
    struct ListElement *prev;
} ListElement;

typedef struct {
    ListElement *head;
    ListElement *tail;
    int size;
} List;

void list_init(List *list);
void list_append(List *list, void *data);
void list_remove(List *list, ListElement *element);
void list_free(List *list);
ListElement *list_iterate(ListElement *element);
