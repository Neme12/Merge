#include "fileSearcher.h"

void fileSearcher_new(fileSearcher* searcher)
{
#if WIN32
    searcher->_findHandle = NULL;
#else
    searcher->_dir = opendir(".");
#endif
}

void fileSearcher_delete(fileSearcher* searcher)
{
#if WIN32
    FindClose(searcher->_findHandle);
#else
    closedir(searcher->_dir);
#endif
}

bool fileSearcher_findNext(fileSearcher* searcher)
{
#if WIN32
        if (searcher->_findHandle == NULL)
        {
            searcher->_findHandle = FindFirstFileA("*", &searcher->_findData);
            if (searcher->_findHandle == INVALID_HANDLE_VALUE)
                return false;
        }
        else
        {
            bool foundNext = FindNextFileA(searcher->_findHandle, &searcher->_findData);
            if (!foundNext)
                return false;
        }

        searcher->current = searcher->_findData.cFileName;
        return true;
#else
        searcher->_dirData = readdir(searcher->_dir);
        if (searcher->_dirData == NULL)
            return false;

        searcher->current = searcher->_dirData->d_name;
        return true;
#endif
}

bool fileSearcher_findNextFile(fileSearcher* searcher)
{
    while (true)
    {
        bool foundNext = fileSearcher_findNext(searcher);
        if (!foundNext)
            return false;

#if WIN32
        if (!(searcher->_findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
            return true;
#else
        if (searcher->_dirData->d_type == DT_REG)
            return true;
#endif
    }
}
