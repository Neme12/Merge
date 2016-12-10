#include "fileNameWithT.h"

string fileNameWithT_newFrom(string fileName, string definedT)
{
    string newFileName;

    if (definedT.length > 0)
    {
        newFileName = string_new(fileName.length + 1 + definedT.length);
        string_concat3Into(fileName, string("|"), definedT, newFileName);
    }
    else
    {
        newFileName = string_newClone(fileName);
    }

    return newFileName;
}
