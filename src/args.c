#include <stdbool.h>
#include <stdlib.h>
#include "str.h"
#include "args.h"

bool args_contains(int argc, char* argv[], char* value)
{
    for (int i = 0; i < argc; ++i)
    {
        if (str_equals(argv[i], value))
            return true;
    }

    return false;
}

args args_from(int argc, char* argv[])
{
    args this;
    this.argc = argc;
    this.argv = argv;
    this.index = 0;
    this.current = NULL;
    return this;
}

bool args_next(args* this)
{
    if (this->index >= this->argc)
        return false;

    if (this->argv[this->index][0] == '-')
    {
        this->current = this->argv[this->index];
        this->index += 1;
    }

    this->value = this->index >= this->argc ? NULL : this->argv[this->index];
    this->index += 1;

    return true;
}
