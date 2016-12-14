#include "fileSearcher.h"

typedef struct codeFileSearcher_s {
    fileSearcher _searcher;
    string fileName;
} codeFileSearcher;

void codeFileSearcher_new(codeFileSearcher* searcher, string directory);
void codeFileSearcher_delete(codeFileSearcher* searcher);

bool codeFileSearcher_findNext(codeFileSearcher* searcher);
