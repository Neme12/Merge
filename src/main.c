#include <stdlib.h>
#include "merger.h"
#include "args.h"
#include "str.h"
#include "main.h"

int main(int argc, char** argv)
{
    arrayList_string files, externalFiles;
    arrayList_string_new(&files);
    arrayList_string_new(&externalFiles);
    string outputDir = string("final/");

    args a = args_from(argc, argv);
    args_next(&a);

    while (args_next(&a))
    {
        if (a.current == NULL)
            arrayList_string_add(&files, string_fromStr(a.value));
        else if (str_equals(a.current, "-e"))
            arrayList_string_add(&externalFiles, string_fromStr(a.value));
        else if (str_equals(a.current, "-o"))
            outputDir = string_fromStr(a.value);
    }

    mergeFiles(files, externalFiles, outputDir);

    arrayList_string_delete(&externalFiles);
    arrayList_string_delete(&files);
    return 0;
}

void mergeFiles(arrayList_string files, arrayList_string externalFiles, string outputDir)
{
    merger merger;
    merger_new(&merger, outputDir, files.data[0], externalFiles);

    for (int i = 0; i < files.length; ++i)
        merger_merge(&merger, files.data[i].data);

    merger_delete(&merger);
}
