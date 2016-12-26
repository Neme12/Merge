bool args_contains(int argc, char* argv[], char* value);

typedef struct args {
    int argc;
    char** argv;

    int index;

    char* current;
    char* value;
} args;

args args_from(int argc, char* argv[]);
bool args_next(args* this);
