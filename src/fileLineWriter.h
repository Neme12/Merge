#include <stdio.h>
#include "string.h"

typedef struct fileLineWriter_s {
    FILE* _file;
} fileLineWriter;

void fileLineWriter_new(fileLineWriter* writer, char* fileName);
void fileLineWriter_delete(fileLineWriter* writer);

void fileLineWriter_write(fileLineWriter* writer, string text);
void fileLineWriter_writeLine(fileLineWriter* writer, string text);
