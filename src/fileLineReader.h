#include <stdio.h>
#include <stdbool.h>
#include "string.h"

#define TYPE char, char
#include "arrayList.h"
#undef TYPE

typedef struct fileLineReader_s {
    FILE* _file;
    arrayList_char _list;
    string current;
} fileLineReader;

bool fileLineReader_new(fileLineReader* reader, char* fileName);
void fileLineReader_delete(fileLineReader* reader);

bool fileLineReader_readLine(fileLineReader* reader);
