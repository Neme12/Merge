#include <stdbool.h>

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
    char* current;
} fileSearcher;

void fileSearcher_new(fileSearcher* searcher);
void fileSearcher_delete(fileSearcher* searcher);

bool fileSearcher_findNext(fileSearcher* searcher);
bool fileSearcher_findNextFile(fileSearcher* searcher);
