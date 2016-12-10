#include "str.h"

int str_firstIndexOf(const char* str, char value)
{
    for (int i = 0; str[i] != 0; ++i)
    {
        if (str[i] == value)
            return i;
    }

    return -1;
}

bool str_startsWith(const char* str, char value)
{
    if (str[0] == 0)
        return false;

    return str[0] == value;
}

bool str_startsWithStr(const char* str, const char* value)
{
    for (int i = 0; value[i] != 0; ++i)
    {
        if (str[i] == 0 || str[i] != value[i])
            return false;
    }

    return true;
}
