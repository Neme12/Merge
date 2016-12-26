#include <stdbool.h>
#include "generics.h"

#define arrayList_t T_NAME(arrayList, TAlias)
#define arrayList_(NAME) F_NAME(arrayList, TAlias, NAME)

typedef struct arrayList_t {
    T* data;
    int capacity;
    int length;
} arrayList_t;

void arrayList_(new)(arrayList_t* list);
void arrayList_(delete)(arrayList_t* list);

void arrayList_(add)(arrayList_t* list, T item);
void arrayList_(clear)(arrayList_t* list);

bool arrayList_(contains)(arrayList_t* list, T item, bool equals(T a, T b));
