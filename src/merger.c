#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "str.h"
#include "fileNameWithT.h"
#include "merger.h"

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
    if (!fileLineReader_new(&reader, fileName))
    {
        fprintf(stderr, "Error: Cannot open file %s\n", fileName);
        return;
    }
    
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

        str_terminate(includedFileName.data, includedFileName.length);
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

    if (string_equals(symbol, string("TYPE")))
    {
        this->definedT = string_newClone(value);
    }

    return false;
}

bool merger_handleUndefine(merger* this, splitIterator split)
{
    splitIterator_next(&split);
    string symbol = split.current;

    if (string_equals(symbol, string("TYPE")))
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
