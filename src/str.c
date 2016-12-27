#include <string.h>
#include "str.h"

char* str_newTerminated(int length)
{
    char* str = malloc((length + 1) * sizeof(char));
    str_terminate(str, length);
    return str;
}

void str_delete(char* str)
{
    free(str);
}

void str_terminate(char* str, int length)
{
    str[length] = '\0';
}

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

int str_compare(const char* str1, const char* str2)
{
    return strcmp(str1, str2);
}

bool str_equals(const char* str1, const char* str2)
{
    return strcmp(str1, str2) == 0;
}
