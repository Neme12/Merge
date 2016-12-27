#include "fileNameWithT.h"

string fileNameWithT_newFrom(string fileName, string definedT)
{
    return definedT.length > 0
        ? string_newConcat3(fileName, string("|"), definedT)
        : string_newClone(fileName);
}
