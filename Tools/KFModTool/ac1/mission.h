#ifndef AC1_MISSION_H
#define AC1_MISSION_H

#include <array>
#include <cstdint>

namespace AC1
{

struct SectionPlacement
{
    std::array<int16_t, 3> bboxMin;     // +0x00..+0x05: P0 world bbox min
    int16_t cellIndex;                  // +0x06..+0x07: cell/PVS index (-1 = table terminator)
    std::array<int16_t, 3> bboxMax;     // +0x08..+0x0D: P1 world bbox max
    int16_t pad0E;                      // +0x0E..+0x0F
    std::array<int16_t, 3> translation; // +0x10..+0x15: world = rotY(block_local * 0.25) + translation
    int16_t rotY;                       // +0x16..+0x17: PSX Y rotation (4096 = 360°, 0x0400 = 90°, 0x0800 = 180°)
    std::array<int16_t, 3> bboxMinCopy; // +0x18..+0x1D: copy of P0
    int16_t blockIndex;                 // +0x1E..+0x1F: geometry block index in Chunk 0
    std::array<int16_t, 3> bboxMaxCopy; // +0x20..+0x25: copy of P1
    int16_t zoneIndex;                  // +0x26..+0x27: zone/portal index
    uint8_t lightingIndex;              // +0x28: index into 104B lighting table
    uint8_t pad29;                      // +0x29
    uint16_t flags;                     // +0x2A..+0x2B: section flags
    std::array<uint8_t, 8> pad2C;       // +0x2C..+0x33: remaining 8 bytes (52 total)
} __attribute__((packed, aligned(1)));

static_assert(sizeof(SectionPlacement) == 52);

struct SpawnRecord
{
    int16_t posX;            // hw0 (+0x00)
    int16_t posY;            // hw1 (+0x02) (PSX Y is down)
    int16_t posZ;            // hw2 (+0x04)
    int16_t blockOrType;     // hw3 (+0x06): -1 = empty/none, 0 = PA00, >0 = Chunk 11 rec; also dispatch type
    int16_t hw4;             // hw4 (+0x08)
    int16_t rotation;        // hw5 (+0x0A): PSX angle (2048 = 180 deg)
    int16_t hw6;             // hw6 (+0x0C)
    int16_t resourceId;      // hw7 (+0x0E): resource/class ID (0..388)
    int16_t param8;          // hw8 (+0x10)
    int16_t param9;          // hw9 (+0x12)
    int16_t hw10;            // hw10 (+0x14)
    int16_t hp;              // hw11 (+0x16): entity HP
    int16_t param12;         // hw12 (+0x18)
    int16_t hw13;            // hw13 (+0x1A)
    int16_t hw14;            // hw14 (+0x1C)
    int16_t param15;         // hw15 (+0x1E)
    int16_t hw16;            // hw16 (+0x20)
    int16_t hw17;            // hw17 (+0x22)
    int16_t hw18;            // hw18 (+0x24)
    int16_t param19;         // hw19 (+0x26)

    bool isEmpty() const { return blockOrType == -1 && posX == 0 && posY == 0 && posZ == 0; }
} __attribute__((packed, aligned(1)));

static_assert(sizeof(SpawnRecord) == 40);

} // namespace AC1

#endif // AC1_MISSION_H
