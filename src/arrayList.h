#include <stdbool.h>

#define TNAME(TYPE) arrayList ## _ ## TYPE
#define FNAME(NAME, TYPE) arrayList ## _ ## TYPE ## _ ## NAME

#define arrayList(TYPE) TNAME(TYPE)
#define arrayList_(NAME, TYPE) FNAME(NAME, TYPE)

typedef struct arrayList(T) {
    T* data;
    int capacity;
    int length;
} arrayList(T);

void arrayList_(new, T)(arrayList(T)* list);
void arrayList_(delete, T)(arrayList(T)* list);

void arrayList_(add, T)(arrayList(T)* list, T item);

bool arrayList_(contains, T)(arrayList(T)* list, T item, bool equals(T a, T b));
