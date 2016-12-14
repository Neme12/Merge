#pragma once

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
