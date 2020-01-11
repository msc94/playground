#pragma once

#include <string>

#include "libttf/ttf_tables.hpp"
#include "libutils/data.hpp"

class TTFFile
{
private:
    ByteBuffer _data;

    OffsetSubtable *_offsetSubtable = nullptr;
    TableEntry *_tableEntries = nullptr;

    HeaderTable *_headerTable = nullptr;
    MaxpTable *_maxpTable = nullptr;

    TableEntry *_glyphTableEntry = nullptr;

    TableEntry *_locationTableEntry = nullptr;
    LocationTableLong *_locationTableLong = nullptr;
    LocationTableShort *_locationTableShort = nullptr;

    TableEntry *getTableEntry(const std::string &name);
    GlyphTableEntry *getGlyphTableEntry(int index);

public:
    TTFFile(ByteBuffer data);

    static TTFFile loadFile(const std::string &path);

    void initializeTables();
};