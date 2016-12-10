#include "string.h"
#include "codeFileSearcher.h"

void codeFileSearcher_new(codeFileSearcher* searcher)
{
    fileSearcher_new(&searcher->_searcher);
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

        string fileName = string_fromStr(searcher->_searcher.current);
        if (string_endsWithString(fileName, string(".c")))
        {
            searcher->fileName = fileName.data;
            return true;
        }
    }
}
