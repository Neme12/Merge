#include <stdlib.h>
#include "codeFileSearcher.h"
#include "merger.h"
#include "args.h"
#include "str.h"
#include "main.h"

char* makeFileName(string value, string defaultName)
{
    char* fileName;

    if (string_endsWith(value, '/'))
    {
        fileName = malloc(value.length + defaultName.length + 1);
        string_concatIntoStr(value, defaultName, fileName);
        str_terminate(fileName, value.length + defaultName.length);
    }
    else
    {
        fileName = malloc(value.length + 1);
        string_copyIntoStr(value, fileName);
        str_terminate(fileName, value.length);
    }

    return fileName;
}

int main(int argc, char** argv)
{
    arrayList_string excludedFiles;
    arrayList_string_new(&excludedFiles);
    char* outputFileName = NULL;

    args a = args_from(argc, argv);
    while (args_next(&a))
    {
        if (a.current == NULL)
            continue;

        if (str_equals(a.current, "-o") && outputFileName == NULL)
            outputFileName = makeFileName(string_fromStr(a.value), string("main.c"));
        else if (str_equals(a.current, "-e"))
            arrayList_string_add(&excludedFiles, string_fromStr(a.value));
    }

    if (outputFileName == NULL)
        outputFileName = makeFileName(string("final/"), string("main.c"));

    mergeAll(outputFileName, excludedFiles);

    free(outputFileName);
    arrayList_string_delete(&excludedFiles);
    return 0;
}

void mergeAll(char* outputFileName, arrayList_string excludedFiles)
{
    string dir = string("");

    codeFileSearcher searcher;
    codeFileSearcher_new(&searcher, dir);

    merger merger;
    merger_new(&merger, outputFileName, excludedFiles);

    while (codeFileSearcher_findNext(&searcher))
    {
        char* formattedFileName = malloc(dir.length + searcher.fileName.length + 1);
        string_concatIntoStr(dir, searcher.fileName, formattedFileName);
        str_terminate(formattedFileName, dir.length + searcher.fileName.length);

        if (!str_equals(formattedFileName, outputFileName))
            merger_merge(&merger, formattedFileName);

        free(formattedFileName);
    }

    merger_delete(&merger);
    codeFileSearcher_delete(&searcher);
}
