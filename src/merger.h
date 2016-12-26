#include "string.h"
#include "fileLineReader.h"
#include "fileLineWriter.h"

#define TYPE string, string
#include "arrayList.h"
#undef TYPE

typedef struct merger {
    fileLineWriter writer;
    string outputDir;
    arrayList_string includedFiles;
    arrayList_string externalFiles;
    string definedT;
} merger;

void merger_new(merger* this, string outputDir, string outputFileName, arrayList_string externalFiles);
void merger_delete(merger* this);

void merger_merge(merger* this, char* fileName);

void merger_includeFile(merger* this, char* fileName);
void merger_mergeFile(merger* this, char* fileName);
void merger_mergeLine(merger* this, string line);
bool merger_handlePreprocessorLine(merger* this, string line);

bool merger_handleInclude(merger* this, string line);
bool merger_handleDefine(merger* this, splitIterator split);
bool merger_handleUndefine(merger* this, splitIterator split);
bool merger_handlePragma(merger* this, splitIterator split);
