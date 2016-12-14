#include <stdlib.h>
#include "str.h"
#include "fileSearcher.h"

char* formatDir(string directory)
{
    char* formatted;
#if WIN32
    formatted = malloc(directory.length + 1 + 1);
    string_concatIntoStr(directory, string("*"), formatted);
    str_terminate(formatted, directory.length + 1);
#else
    formatted = malloc(2 + directory.length + 1);
    string_concatIntoStr(string("./"), directory, formatted);
    str_terminate(formatted, 2 + directory.length);
#endif
    return formatted;
}

void fileSearcher_new(fileSearcher* searcher, string directory)
{
#if WIN32
    searcher->_findHandle = NULL;
#else
    char* formatted = formatDir(directory);
    searcher->_dir = opendir(formatted);
    free(formatted);
#endif
    searcher->directory = directory;
    searcher->fileName = string_empty();
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
            char* formatted = formatDir(searcher->directory);
            searcher->_findHandle = FindFirstFileA(formatted, &searcher->_findData);
            free(formatted);

            if (searcher->_findHandle == INVALID_HANDLE_VALUE)
                return false;
        }
        else
        {
            bool foundNext = FindNextFileA(searcher->_findHandle, &searcher->_findData);
            if (!foundNext)
                return false;
        }

        searcher->fileName = string_fromStr(searcher->_findData.cFileName);
        return true;
#else
        searcher->_dirData = readdir(searcher->_dir);
        if (searcher->_dirData == NULL)
            return false;

        searcher->fileName = string_fromStr(searcher->_dirData->d_name);
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
