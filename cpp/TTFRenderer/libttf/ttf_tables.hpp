#pragma once

#include <arpa/inet.h>
#include <cstdint>
#include <spdlog/spdlog.h>

template <class T>
class __attribute__((packed))
BigEndian
{
private:
    T _val;

public:
    operator T() const
    {
        if constexpr (sizeof(T) == 4) {
            return htonl(_val);
        } else if constexpr (sizeof(T) == 2) {
            return htons(_val);
        } else {
            return _val;
        }
    }
};

static_assert(sizeof(BigEndian<uint32_t>) == sizeof(uint32_t));

struct __attribute__((packed))
OffsetSubtable {
    BigEndian<uint32_t> scalerType;
    BigEndian<uint16_t> numTables;
    BigEndian<uint16_t> searchRange;
    BigEndian<uint16_t> entrySelector;
    BigEndian<uint16_t> rangeShift;
};

struct __attribute__((packed))
TableEntry {
    char identifier[4];
    BigEndian<uint32_t> checksum;
    BigEndian<uint32_t> offset;
    BigEndian<uint32_t> length;
};

struct __attribute__((packed))
HeaderTable {
    BigEndian<uint32_t> version;
    BigEndian<uint32_t> fontRevision;
    BigEndian<uint32_t> checksumAdjustment;
    BigEndian<uint32_t> magicNumber;
    BigEndian<uint16_t> flags;
    BigEndian<uint16_t> unitsPerEm;

    BigEndian<uint32_t> created_1;
    BigEndian<uint32_t> created_2;

    BigEndian<uint32_t> modified_1;
    BigEndian<uint32_t> modified_2;

    BigEndian<uint16_t> xMin;
    BigEndian<uint16_t> yMin;
    BigEndian<uint16_t> xMax;
    BigEndian<uint16_t> yMax;

    BigEndian<uint16_t> macStyle;
    BigEndian<uint16_t> lowestRecPPEM;

    BigEndian<uint16_t> fontDirectionHint;
    BigEndian<uint16_t> indexToLocFormat;
    BigEndian<uint16_t> glyphDataFormat;
};

struct __attribute__((packed))
MaxpTable {
    BigEndian<uint32_t> version;
    BigEndian<uint16_t> numGlyphs;
    // ...
};

struct __attribute__((packed))
SimpleGlyph {

};

struct __attribute__((packed))
CompoundGlyph {

};

struct __attribute__((packed))
GlyphTableEntry {
    BigEndian<uint16_t> numContours;
    BigEndian<uint16_t> xMin;
    BigEndian<uint16_t> yMin;
    BigEndian<uint16_t> xMax;
    BigEndian<uint16_t> yMax;

    union {
        SimpleGlyph simpleGlyph;
        CompoundGlyph compoundGlyph;
    };
};

template <class T>
struct __attribute__((packed))
LocationTable {
    T offset;
};
using LocationTableShort = LocationTable<BigEndian<uint16_t>>;
using LocationTableLong = LocationTable<BigEndian<uint32_t>>;