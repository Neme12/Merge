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
    char* outputFileName = NULL;

    args_optional o = args_optionalFrom(argc, argv);
    while (args_optional_next(&o))
    {
        if (str_equals(o.current, "-o"))
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
    string dir = string("");

    codeFileSearcher searcher;
    codeFileSearcher_new(&searcher, dir);

    merger merger;
    merger_new(&merger, outputFileName);

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
