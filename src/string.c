#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "string.h"

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
    strncpy(out.data, source.data, source.length);
}

void string_concatInto(string s1, string s2, string out)
{
    strncpy(out.data, s1.data, s1.length);
    strncpy(out.data + s1.length, s2.data, s2.length);
}

void string_concat3Into(string s1, string s2, string s3, string out)
{
    strncpy(out.data, s1.data, s1.length);
    strncpy(out.data + s1.length, s2.data, s2.length);
    strncpy(out.data + s1.length + s2.length, s3.data, s3.length);
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
