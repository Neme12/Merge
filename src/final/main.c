// args.c

#include <stdbool.h>
#include <stdlib.h>
// #include "str.h"
// {
#include <stdbool.h>

void str_terminate(char* str, int length);

int str_firstIndexOf(const char* str, char value);

bool str_startsWith(const char* str, char value);
bool str_startsWithStr(const char* str, const char* value);

int str_compare(const char* str1, const char* str2);
bool str_equals(const char* str1, const char* str2);

// }
// #include "args.h"
// {
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

// }

bool args_contains(int argc, char* argv[], char* value)
{
    for (int i = 0; i < argc; ++i)
    {
        if (str_equals(argv[i], value))
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

// arrayList.c

// #include "string.h"
// {
// #pragma once

#include <stdbool.h>

// create directly from a string literal - we don't have to calculate the size using strlen
#define string(LITERAL) string_from(LITERAL, sizeof(LITERAL) - 1)

// This string is NOT null-terminated.
typedef struct string_s {
    char* data; // NOT null-terminated
    int length;
} string;

string string_new(int length);
string string_newClone(string source);
string string_newConcat(string s1, string s2);
string string_newConcat3(string s1, string s2, string s3);
void string_delete(string s);

string string_empty();
string string_fromStr(char* str);
string string_from(char* data, int length);

string string_substring(string s, int index, int length);
string string_substringFrom(string s, int fromIndex);
string string_substringTo(string s, int toIndex);
string string_substringFromTo(string s, int fromIndex, int toIndex);

void string_copyInto(string source, string out);
void string_concatInto(string s1, string s2, string out);
void string_concat3Into(string s1, string s2, string s3, string out);

void string_copyIntoStr(string source, char* out);
void string_concatIntoStr(string s1, string s2, char* out);
void string_concat3IntoStr(string s1, string s2, string s3, char* out);

int string_firstIndexOf(string s, char value);
int string_lastIndexOf(string s, char value);

bool string_startsWith(string s, char value);
bool string_endsWith(string s, char value);

bool string_startsWithString(string s, string value);
bool string_endsWithString(string s, string value);

int string_compare(string s1, string s2);
bool string_equals(string s1, string s2);

void string_print(string s);
void string_printLine(string s);

typedef struct splitIterator {
    string source;
    string current;
    int index;
} splitIterator;

splitIterator string_split(string s);
bool splitIterator_next(splitIterator* this);
string splitIterator_rest(splitIterator* this);

// }

#define T char
// #include "arrayList.c.h"
// {
#include <stdlib.h>
// #include "arrayList.h"
// {
#include <stdbool.h>

#define TNAME(TYPE) arrayList ## _ ## TYPE
#define FNAME(NAME, TYPE) arrayList ## _ ## TYPE ## _ ## NAME

#define arrayList(TYPE) TNAME(TYPE)
#define arrayList_(NAME, TYPE) FNAME(NAME, TYPE)

typedef struct arrayList(T) {
    T* data;
    int capacity;
    int length;
} arrayList(T);

void arrayList_(new, T)(arrayList(T)* list);
void arrayList_(delete, T)(arrayList(T)* list);

void arrayList_(add, T)(arrayList(T)* list, T item);

bool arrayList_(contains, T)(arrayList(T)* list, T item, bool equals(T a, T b));

// }

void arrayList_(new, T)(arrayList(T)* list)
{
    list->length = 0;
    list->capacity = 4;
    list->data = malloc(list->capacity * sizeof(T));
}

void arrayList_(delete, T)(arrayList(T)* list)
{
    free(list->data);
}

void arrayList_(add, T)(arrayList(T)* list, T item)
{
    if (list->length == list->capacity)
    {
        list->capacity *= 2;
        list->data = realloc(list->data, list->capacity * sizeof(T));
    }

    list->data[list->length++] = item;
}

bool arrayList_(contains, T)(arrayList(T)* list, T item, bool equals(T a, T b))
{
    for (int i = 0; i < list->length; ++i)
    {
        if (equals(list->data[i], item))
            return true;
    }

    return false;
}

// }
#undef T

#define T string
// #include "arrayList.c.h"
// {
#include <stdlib.h>
// #include "arrayList.h"
// {
#include <stdbool.h>

#define TNAME(TYPE) arrayList ## _ ## TYPE
#define FNAME(NAME, TYPE) arrayList ## _ ## TYPE ## _ ## NAME

#define arrayList(TYPE) TNAME(TYPE)
#define arrayList_(NAME, TYPE) FNAME(NAME, TYPE)

typedef struct arrayList(T) {
    T* data;
    int capacity;
    int length;
} arrayList(T);

void arrayList_(new, T)(arrayList(T)* list);
void arrayList_(delete, T)(arrayList(T)* list);

void arrayList_(add, T)(arrayList(T)* list, T item);

bool arrayList_(contains, T)(arrayList(T)* list, T item, bool equals(T a, T b));

// }

void arrayList_(new, T)(arrayList(T)* list)
{
    list->length = 0;
    list->capacity = 4;
    list->data = malloc(list->capacity * sizeof(T));
}

void arrayList_(delete, T)(arrayList(T)* list)
{
    free(list->data);
}

void arrayList_(add, T)(arrayList(T)* list, T item)
{
    if (list->length == list->capacity)
    {
        list->capacity *= 2;
        list->data = realloc(list->data, list->capacity * sizeof(T));
    }

    list->data[list->length++] = item;
}

bool arrayList_(contains, T)(arrayList(T)* list, T item, bool equals(T a, T b))
{
    for (int i = 0; i < list->length; ++i)
    {
        if (equals(list->data[i], item))
            return true;
    }

    return false;
}

// }
#undef T

// codeFileSearcher.c

// #include "string.h"
// #include "codeFileSearcher.h"
// {
// #include "fileSearcher.h"
// {
#include <stdbool.h>

#if WIN32
#include <windows.h>
#else
#include <dirent.h>
#endif

typedef struct fileSearcher_s {
#if WIN32
    HANDLE _findHandle;
    WIN32_FIND_DATAA _findData;
#else
    DIR* _dir;
    struct dirent* _dirData;
#endif
    char* current;
} fileSearcher;

void fileSearcher_new(fileSearcher* searcher);
void fileSearcher_delete(fileSearcher* searcher);

bool fileSearcher_findNext(fileSearcher* searcher);
bool fileSearcher_findNextFile(fileSearcher* searcher);

// }

typedef struct codeFileSearcher_s {
    fileSearcher _searcher;
    char* fileName;
} codeFileSearcher;

void codeFileSearcher_new(codeFileSearcher* searcher);
void codeFileSearcher_delete(codeFileSearcher* searcher);

bool codeFileSearcher_findNext(codeFileSearcher* searcher);

// }

void codeFileSearcher_new(codeFileSearcher* searcher)
{
    fileSearcher_new(&searcher->_searcher);
}

void codeFileSearcher_delete(codeFileSearcher* searcher)
{
    fileSearcher_delete(&searcher->_searcher);
}

bool codeFileSearcher_findNext(codeFileSearcher* searcher)
{
    while (true)
    {
        bool foundNext = fileSearcher_findNextFile(&searcher->_searcher);
        if (!foundNext)
            return false;

        string fileName = string_fromStr(searcher->_searcher.current);
        if (string_endsWithString(fileName, string(".c")))
        {
            searcher->fileName = fileName.data;
            return true;
        }
    }
}

// fileLineReader.c

// #include "fileLineReader.h"
// {
#include <stdio.h>
#include <stdbool.h>
// #include "string.h"

#define T char
// #include "arrayList.h"
#undef T

typedef struct fileLineReader_s {
    FILE* _file;
    arrayList_char _list;
    string current;
} fileLineReader;

void fileLineReader_new(fileLineReader* reader, char* fileName);
void fileLineReader_delete(fileLineReader* reader);

bool fileLineReader_readLine(fileLineReader* reader);

// }

void fileLineReader_new(fileLineReader* reader, char* fileName)
{
    reader->_file = fopen(fileName, "r");
    arrayList_char_new(&reader->_list);
}

void fileLineReader_delete(fileLineReader* reader)
{
    fclose(reader->_file);
    arrayList_char_delete(&reader->_list);
}

bool fileLineReader_readLine(fileLineReader* reader)
{
    if (feof(reader->_file))
        return false;

    arrayList_char_delete(&reader->_list);
    arrayList_char_new(&reader->_list);

    while (true)
    {
        int c = fgetc(reader->_file);
        if (c == EOF || c == '\n')
            break;

        arrayList_char_add(&reader->_list, (char)c);
    }

    reader->current = string_from(reader->_list.data, reader->_list.length);
    return true;
}

// fileLineWriter.c

// #include "fileLineWriter.h"
// {
#include <stdio.h>
// #include "string.h"

typedef struct fileLineWriter_s {
    FILE* _file;
} fileLineWriter;

void fileLineWriter_new(fileLineWriter* writer, char* fileName);
void fileLineWriter_delete(fileLineWriter* writer);

void fileLineWriter_write(fileLineWriter* writer, string text);
void fileLineWriter_writeLine(fileLineWriter* writer, string text);

// }

void fileLineWriter_new(fileLineWriter* writer, char* fileName)
{
    writer->_file = fopen(fileName, "w");
}

void fileLineWriter_delete(fileLineWriter* writer)
{
    fclose(writer->_file);
}

void fileLineWriter_writeLine(fileLineWriter* writer, string text)
{
    for (int i = 0; i < text.length; ++i)
        fputc(text.data[i], writer->_file);

    fputc('\n', writer->_file);
}

void fileLineWriter_write(fileLineWriter* writer, string text)
{
    for (int i = 0; i < text.length; ++i)
        fputc(text.data[i], writer->_file);
}

// fileNameWithT.c

// #include "fileNameWithT.h"
// {
// #include "string.h"

string fileNameWithT_newFrom(string fileName, string definedT);

// }

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

// fileSearcher.c

// #include "fileSearcher.h"

void fileSearcher_new(fileSearcher* searcher)
{
#if WIN32
    searcher->_findHandle = NULL;
#else
    searcher->_dir = opendir(".");
#endif
}

void fileSearcher_delete(fileSearcher* searcher)
{
#if WIN32
    FindClose(searcher->_findHandle);
#else
    closedir(searcher->_dir);
#endif
}

bool fileSearcher_findNext(fileSearcher* searcher)
{
#if WIN32
        if (searcher->_findHandle == NULL)
        {
            searcher->_findHandle = FindFirstFileA("*", &searcher->_findData);
            if (searcher->_findHandle == INVALID_HANDLE_VALUE)
                return false;
        }
        else
        {
            bool foundNext = FindNextFileA(searcher->_findHandle, &searcher->_findData);
            if (!foundNext)
                return false;
        }

        searcher->current = searcher->_findData.cFileName;
        return true;
#else
        searcher->_dirData = readdir(searcher->_dir);
        if (searcher->_dirData == NULL)
            return false;

        searcher->current = searcher->_dirData->d_name;
        return true;
#endif
}

bool fileSearcher_findNextFile(fileSearcher* searcher)
{
    while (true)
    {
        bool foundNext = fileSearcher_findNext(searcher);
        if (!foundNext)
            return false;

#if WIN32
        if (!(searcher->_findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
            return true;
#else
        if (searcher->_dirData->d_type == DT_REG)
            return true;
#endif
    }
}

// main.c

#include <stdlib.h>
// #include "codeFileSearcher.h"
// #include "merger.h"
// {
// #include "string.h"
// #include "fileLineReader.h"
// #include "fileLineWriter.h"

#define T string
// #include "arrayList.h"
#undef T

typedef struct merger {
    fileLineWriter writer;
    arrayList_string includedFiles;
    string definedT;
} merger;

void merger_new(merger* this, char* outputFileName);
void merger_delete(merger* this);

void merger_merge(merger* this, char* fileName);

void merger_includeFile(merger* this, char* fileName);
void merger_mergeFile(merger* this, char* fileName);
void merger_mergeLine(merger* this, string line);
bool merger_handlePreprocessorLine(merger* this, string line);

bool merger_handleInclude(merger* this, string line);
bool merger_handleDefine(merger* this, splitIterator split);
bool merger_handleUndefine(merger* this, splitIterator split);
bool merger_handlePragma(merger* this, splitIterator split);

// }
// #include "args.h"
// #include "str.h"
// #include "main.h"
// {
void mergeAll(char* outputFileName);

// }

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
    codeFileSearcher searcher;
    codeFileSearcher_new(&searcher);

    merger merger;
    merger_new(&merger, outputFileName);

    while (codeFileSearcher_findNext(&searcher))
    {
        if (!str_equals(searcher.fileName, outputFileName))
            merger_merge(&merger, searcher.fileName);
    }

    merger_delete(&merger);
    codeFileSearcher_delete(&searcher);
}

// merger.c

#include <stdio.h>

#include <stdlib.h>
#include <string.h>
// #include "fileNameWithT.h"
// #include "merger.h"

void merger_new(merger* this, char* outputFileName)
{
    this->definedT = string_empty();
    fileLineWriter_new(&this->writer, outputFileName);
    arrayList_string_new(&this->includedFiles);
}

void merger_delete(merger* this)
{
    for (int i = 0; i < this->includedFiles.length; ++i)
        string_delete(this->includedFiles.data[i]);

    fileLineWriter_delete(&this->writer);
    arrayList_string_delete(&this->includedFiles);
}

void merger_merge(merger* this, char* fileName)
{
    fileLineWriter_write(&this->writer, string("// "));
    fileLineWriter_writeLine(&this->writer, string_fromStr(fileName));
    fileLineWriter_writeLine(&this->writer, string_empty());

    merger_mergeFile(this, fileName);
}

void merger_includeFile(merger* this, char* fileName)
{
    fileLineWriter_writeLine(&this->writer, string("// {"));
    merger_mergeFile(this, fileName);
    fileLineWriter_writeLine(&this->writer, string("// }"));
}

void merger_mergeFile(merger* this, char* fileName)
{
    fileLineReader reader;
    fileLineReader_new(&reader, fileName);
    
    while (fileLineReader_readLine(&reader))
        merger_mergeLine(this, reader.current);

    fileLineReader_delete(&reader);
}

void merger_mergeLine(merger* this, string line)
{
    if (merger_handlePreprocessorLine(this, line))
        return;

    fileLineWriter_writeLine(&this->writer, line);
}

bool merger_handlePreprocessorLine(merger* this, string line)
{
    splitIterator split = string_split(line);
    splitIterator_next(&split);

    if (string_equals(split.current, string("#include")))
        return merger_handleInclude(this, line);
    else if (string_equals(split.current, string("#define")))
        return merger_handleDefine(this, split);
    else if (string_equals(split.current, string("#undef")))
        return merger_handleUndefine(this, split);
    else if (string_equals(split.current, string("#pragma")))
        return merger_handlePragma(this, split);

    return false;
}

bool merger_handleInclude(merger* this, string line)
{
    int firstQuote = string_firstIndexOf(line, '"');
    int lastQuote = string_lastIndexOf(line, '"');

    if (firstQuote < 0 || lastQuote <= firstQuote)
        return false;

    string includedFileName = string_substringFromTo(line, firstQuote + 1, lastQuote);
    string fileNameWithT = fileNameWithT_newFrom(includedFileName, this->definedT);

    fileLineWriter_write(&this->writer, string("// "));
    fileLineWriter_writeLine(&this->writer, line);

    if (!arrayList_string_contains(&this->includedFiles, fileNameWithT, string_equals))
    {
        arrayList_string_add(&this->includedFiles, fileNameWithT);

        includedFileName.data[includedFileName.length] = '\0';
        merger_includeFile(this, includedFileName.data);
    }
    else
    {
        string_delete(fileNameWithT);
    }

    return true;
}

bool merger_handleDefine(merger* this, splitIterator split)
{
    splitIterator_next(&split);
    string symbol = split.current;

    splitIterator_next(&split);
    string value = split.current;

    if (string_equals(symbol, string("T")))
    {
        this->definedT = string_newClone(value);
    }

    return false;
}

bool merger_handleUndefine(merger* this, splitIterator split)
{
    splitIterator_next(&split);
    string symbol = split.current;

    if (string_equals(symbol, string("T")))
    {
        string_delete(this->definedT);
        this->definedT = string_empty();
    }

    return false;
}

bool merger_handlePragma(merger* this, splitIterator split)
{
    splitIterator_next(&split);
    if (!string_equals(split.current, string("once")))
        return false;

    fileLineWriter_write(&this->writer, string("// "));
    fileLineWriter_writeLine(&this->writer, split.source);
    return true;
}

// str.c

#include <string.h>
// #include "str.h"

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

// string.c

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
// #include "string.h"

string string_new(int length)
{
    string s;
    s.data = malloc(length * sizeof(char));
    s.length = length;
    return s;
}

string string_newClone(string source)
{
    string s = string_new(source.length);
    string_copyInto(source, s);
    return s;
}

string string_newConcat(string s1, string s2)
{
    string s = string_new(s1.length + s2.length);
    string_concatInto(s1, s2, s);
    return s;
}

string string_newConcat3(string s1, string s2, string s3)
{
    string s = string_new(s1.length + s2.length + s3.length);
    string_concat3Into(s1, s2, s3, s);
    return s;
}

void string_delete(string s)
{
    free(s.data);
}

string string_empty()
{
    string s;
    s.data = NULL;
    s.length = 0;
    return s;
}

string string_fromStr(char* str)
{
    string s;
    s.data = str;
    s.length = strlen(str);
    return s;
}

string string_from(char* data, int length)
{
    string s;
    s.data = data;
    s.length = length;
    return s;
}

string string_substring(string str, int index, int length)
{
    string s;
    s.data = str.data + index;
    s.length = length;
    return s;
}

string string_substringFrom(string s, int fromIndex)
{
    return string_substring(s, fromIndex, s.length - fromIndex);
}

string string_substringTo(string s, int toIndex)
{
    return string_substring(s, 0, toIndex);
}

string string_substringFromTo(string s, int fromIndex, int toIndex)
{
    return string_substring(s, fromIndex, toIndex - fromIndex);
}

void string_copyInto(string source, string out)
{
    string_copyIntoStr(source, out.data);
}

void string_concatInto(string s1, string s2, string out)
{
    string_concatIntoStr(s1, s2, out.data);
}

void string_concat3Into(string s1, string s2, string s3, string out)
{
    string_concat3IntoStr(s1, s2, s3, out.data);
}

void string_copyIntoStr(string source, char* out)
{
    strncpy(out, source.data, source.length);
}

void string_concatIntoStr(string s1, string s2, char* out)
{
    strncpy(out, s1.data, s1.length);
    strncpy(out + s1.length, s2.data, s2.length);
}

void string_concat3IntoStr(string s1, string s2, string s3, char* out)
{
    strncpy(out, s1.data, s1.length);
    strncpy(out + s1.length, s2.data, s2.length);
    strncpy(out + s1.length + s2.length, s3.data, s3.length);
}

int string_firstIndexOf(string s, char value)
{
    for (int i = 0; i < s.length; ++i)
    {
        if (s.data[i] == value)
            return i;
    }

    return -1;
}

int string_lastIndexOf(string s, char value)
{
    for (int i = s.length - 1; i >= 0; --i)
    {
        if (s.data[i] == value)
            return i;
    }

    return -1;
}

bool string_startsWith(string s, char value)
{
    if (s.length < 1)
        return false;

    return s.data[0] == value;
}

bool string_endsWith(string s, char value)
{
    if (s.length < 1)
        return false;

    return s.data[s.length - 1] == value;
}

bool string_startsWithString(string s, string value)
{
    if (value.length > s.length)
        return false;

    return string_equals(value, string_substringTo(s, value.length));
}

bool string_endsWithString(string s, string value)
{
    if (value.length > s.length)
        return false;

    return string_equals(value, string_substringFrom(s, s.length - value.length));
}

int string_compare(string s1, string s2)
{
    if (s1.length < s2.length)
        return -1;
    if (s1.length > s2.length)
        return +1;

    for (int i = 0; i < s1.length; ++i)
    {
        if (s1.data[i] < s2.data[i])
            return -1;
        if (s1.data[i] > s2.data[i])
            return +1;
    }

    return 0;
}

bool string_equals(string s1, string s2)
{
    if (s1.length != s2.length)
        return false;

    for (int i = 0; i < s1.length; ++i)
    {
        if (s1.data[i] != s2.data[i])
            return false;
    }

    return true;
}

void string_print(string s)
{
    for (int i = 0; i < s.length; ++i)
        putchar(s.data[i]);
}

void string_printLine(string s)
{
    string_print(s);
    putchar('\n');
}

splitIterator string_split(string s)
{
    splitIterator iterator;
    iterator.source = s;
    iterator.current = string_empty();
    iterator.index = 0;
    return iterator;
}

bool splitIterator_next(splitIterator* this)
{
    while (this->index < this->source.length && isspace(this->source.data[this->index]))
        ++this->index;

    int startIndex = this->index;

    while (this->index < this->source.length && !isspace(this->source.data[this->index]))
        ++this->index;

    int length = this->index - startIndex;
    if (length <= 0)
        return false;

    this->current = string_substring(this->source, startIndex, length);
    return true;
}

string splitIterator_rest(splitIterator* this)
{
    return string_substringFrom(this->source, this->index);
}

