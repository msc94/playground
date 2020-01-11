#include "ttf_file.hpp"

#include <spdlog/spdlog.h>

#include "libutils/file.hpp"

TTFFile::TTFFile(ByteBuffer data)
    : _data(std::move(data)) {}

TTFFile TTFFile::loadFile(const std::string &path)
{
    spdlog::debug("Loading ttf file {}", path);
    auto file = File(path);
    return TTFFile(file.readAll());
}

void TTFFile::initializeTables()
{
    _offsetSubtable = (OffsetSubtable *)_data.data();
    spdlog::debug("ScalerType = {:#010x}, NumTables = {}",
                  _offsetSubtable->scalerType,
                  _offsetSubtable->numTables);

    if (_offsetSubtable->scalerType != 0x74727565 &&
        _offsetSubtable->scalerType != 0x00010000) {
        throw std::runtime_error("Font is not a TrueType font");
    }

    _tableEntries = (TableEntry *)(_data.data() + sizeof(OffsetSubtable));

    auto *headerTableEntry = getTableEntry("head");
    _headerTable = (HeaderTable *)(_data.data() + headerTableEntry->offset);
    spdlog::debug("Font header table has offset {}", headerTableEntry->offset);
    spdlog::debug("Font direction hint {}", _headerTable->fontDirectionHint);

    auto *maxpTableEntry = getTableEntry("maxp");
    _maxpTable = (MaxpTable *)(_data.data() + maxpTableEntry->offset);
    spdlog::debug("Maxp header table has offset {}", maxpTableEntry->offset);
    spdlog::debug("Font has {} glyphs", _maxpTable->numGlyphs);

    _locationTableEntry = getTableEntry("loca");
    void *locationTable = _data.data() + _locationTableEntry->offset;
    if (_headerTable->indexToLocFormat == 0) {
        spdlog::debug("TTF has short index to location format");
        _locationTableShort = (LocationTableShort *)locationTable;
    } else if (_headerTable->indexToLocFormat == 1) {
        spdlog::debug("TTF has long index to location format");
        _locationTableLong = (LocationTableLong *)locationTable;
    } else {
        throw std::runtime_error("Unknown indexToLocFormat");
    }

    _glyphTableEntry = getTableEntry("glyph");
    _glyphTable = (GlyphTableEntry *)(_data.data() + _glyphTableEntry->offset);
}

TableEntry *TTFFile::getTableEntry(const std::string &name)
{
    for (int i = 0; i < _offsetSubtable->numTables; i++) {
        TableEntry *tableEntry = _tableEntries + i;
        auto tableName = std::string(tableEntry->identifier, 4);
        if (tableName == name) {
            return tableEntry;
        }
    }
    return nullptr;
}

GlyphTableEntry *TTFFile::getGlyphTableEntry(int index)
{
    // Look inside the loca table
    if (index < 0 || index > _maxpTable->numGlyphs) {
        throw std::runtime_error("Index out of bounds");
    }

    auto locationTableLength = _locationTableEntry->length;
    if (_locationTableLong &&
        index * sizeof(LocationTableLong) > locationTableLength) {
        throw std::runtime_error("Index out of bounds");
    }
    if (_locationTableShort &&
        index * sizeof(LocationTableShort) > locationTableLength) {
        throw std::runtime_error("Index out of bounds");
    }

    uint32_t offset = 0;
    if (_locationTableLong) {
        offset = _locationTableLong[index].offset;
    } else if (_locationTableShort) {
        offset = _locationTableShort[index].offset * 2;
    }

    if (offset > _glyphTableEntry->length) {
        throw std::runtime_error("Location table offset bigger than GlyphTableEntry length");
    }

    return (GlyphTableEntry *)(_data.data() + _glyphTableEntry->offset + offset);
}
