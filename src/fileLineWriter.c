#include "fileLineWriter.h"

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
