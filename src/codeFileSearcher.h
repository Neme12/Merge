#include "fileSearcher.h"

typedef struct codeFileSearcher_s {
    fileSearcher _searcher;
    char* fileName;
} codeFileSearcher;

void codeFileSearcher_new(codeFileSearcher* searcher);
void codeFileSearcher_delete(codeFileSearcher* searcher);

bool codeFileSearcher_findNext(codeFileSearcher* searcher);
