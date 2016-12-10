#include <stdio.h>
#include <stdbool.h>
#include "string.h"

#define T char
#include "arrayList.h"
#undef T

typedef struct fileLineReader_s {
    FILE* _file;
    arrayList_char _list;
    string current;
} fileLineReader;

void fileLineReader_new(fileLineReader* reader, char* fileName);
void fileLineReader_delete(fileLineReader* reader);

bool fileLineReader_readLine(fileLineReader* reader);
