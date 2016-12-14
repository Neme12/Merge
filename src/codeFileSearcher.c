#include "string.h"
#include "codeFileSearcher.h"

void codeFileSearcher_new(codeFileSearcher* searcher, string directory)
{
    fileSearcher_new(&searcher->_searcher, directory);
}

void codeFileSearcher_delete(codeFileSearcher* searcher)
{
    fileSearcher_delete(&searcher->_searcher);
}

bool codeFileSearcher_findNext(codeFileSearcher* searcher)
{
    while (true)
    {
        bool foundNext = fileSearcher_findNextFile(&searcher->_searcher);
        if (!foundNext)
            return false;

        if (string_endsWithString(searcher->_searcher.fileName, string(".c")))
        {
            searcher->fileName = searcher->_searcher.fileName;
            return true;
        }
    }
}
