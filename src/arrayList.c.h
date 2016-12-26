#include <stdlib.h>
#include "arrayList.h"

void arrayList_(new)(arrayList_t* list)
{
    list->length = 0;
    list->capacity = 4;
    list->data = malloc(list->capacity * sizeof(T));
}

void arrayList_(delete)(arrayList_t* list)
{
    free(list->data);
}

void arrayList_(add)(arrayList_t* list, T item)
{
    if (list->length == list->capacity)
    {
        list->capacity *= 2;
        list->data = realloc(list->data, list->capacity * sizeof(T));
    }

    list->data[list->length++] = item;
}

void arrayList_(clear)(arrayList_t* list)
{
    list->length = 0;
}

bool arrayList_(contains)(arrayList_t* list, T item, bool equals(T a, T b))
{
    for (int i = 0; i < list->length; ++i)
    {
        if (equals(list->data[i], item))
            return true;
    }

    return false;
}
