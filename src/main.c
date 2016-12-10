#include <stdio.h>
#include <string.h>
#include "codeFileSearcher.h"
#include "merger.h"
#include "main.h"
#include "args.h"

#include <stdlib.h>

char* makeFileName(string value, string defaultName)
{
    char* fileName;

    if (string_endsWith(value, '/'))
    {
        fileName = malloc(value.length + defaultName.length + 1);
        strncpy(fileName, value.data, value.length);
        strncpy(fileName + value.length, defaultName.data, defaultName.length);
        fileName[value.length + defaultName.length] = '\0';
    }
    else
    {
        fileName = malloc(value.length + 1);
        strncpy(fileName, value.data, value.length);
        fileName[value.length] = '\0';
    }

    return fileName;
}

int main(int argc, char** argv)
{
    char* outputFileName = NULL;

    args_optional o = args_optionalFrom(argc, argv);
    while (args_optional_next(&o))
    {
        if (strcmp(o.current, "-o") == 0)
        {
            outputFileName = makeFileName(string_fromStr(o.value), string("main.c"));
            break;
        }
    }

    if (outputFileName == NULL)
        outputFileName = makeFileName(string("final/"), string("main.c"));

    mergeAll(outputFileName);

    free(outputFileName);
    return 0;
}

void mergeAll(char* outputFileName)
{
    codeFileSearcher searcher;
    codeFileSearcher_new(&searcher);

    merger merger;
    merger_new(&merger, outputFileName);

    while (codeFileSearcher_findNext(&searcher))
    {
        if (strcmp(searcher.fileName, outputFileName) != 0)
            merger_merge(&merger, searcher.fileName);
    }

    merger_delete(&merger);
    codeFileSearcher_delete(&searcher);
}
