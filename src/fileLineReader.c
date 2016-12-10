#include "fileLineReader.h"

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
        char c = fgetc(reader->_file);
        if (c == EOF || c == '\n')
            break;

        arrayList_char_add(&reader->_list, c);
    }

    reader->current = string_from(reader->_list.data, reader->_list.length);
    return true;
}
