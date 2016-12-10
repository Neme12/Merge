bool args_contains(int argc, char* argv[], char* value);

typedef struct args_optional {
    int argc;
    char** argv;

    int index;

    char* current;
    char* value;
} args_optional;

args_optional args_optionalFrom(int argc, char* argv[]);
bool args_optional_next(args_optional* this);
