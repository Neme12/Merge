#include <stdbool.h>
#include <string.h>

#include "args.h"

bool args_contains(int argc, char* argv[], char* value)
{
    for (int i = 0; i < argc; ++i)
    {
        if (strcmp(argv[i], value) == 0)
            return true;
    }

    return false;
}

args_optional args_optionalFrom(int argc, char* argv[])
{
    args_optional this;
    this.argc = argc;
    this.argv = argv;
    this.index = 0;
    return this;
}

bool args_optional_next(args_optional* this)
{
    while (true)
    {
        if (this->index >= this->argc)
            return false;

        if (this->argv[this->index][0] == '-')
            break;  

        this->index += 1;
    }

    this->current = this->argv[this->index];
    this->index += 1;

    this->value = this->index >= this->argc ? NULL : this->argv[this->index];
    this->index += 1;

    return true;
}
