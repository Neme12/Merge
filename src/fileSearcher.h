#include <stdbool.h>
#include "string.h"

#if WIN32
#include <windows.h>
#else
#include <dirent.h>
#endif

typedef struct fileSearcher_s {
#if WIN32
    HANDLE _findHandle;
    WIN32_FIND_DATAA _findData;
#else
    DIR* _dir;
    struct dirent* _dirData;
#endif
    string directory;
    string fileName;
} fileSearcher;

void fileSearcher_new(fileSearcher* searcher, string directory);
void fileSearcher_delete(fileSearcher* searcher);

bool fileSearcher_findNext(fileSearcher* searcher);
bool fileSearcher_findNextFile(fileSearcher* searcher);
