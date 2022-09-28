#ifndef KF2_TILE_H
#define KF2_TILE_H

#include <cstdint>

namespace KF2
{

// Structs

/*!
 * \brief King's Field 2 tile.
 */
struct Tile
{
    uint8_t TileID;
    uint8_t Elevation;
    uint8_t Rotation; ///< 0-3, each step is 90°
    uint8_t CollisionIndex;
    uint8_t Flags;

    bool getEnemyBlock() const { return (Flags & 0b01000000) != 0; }
    uint8_t getRenderParameterIndex() const { return Flags & 63u; }
    bool getSwitchLayer() const { return (Flags & 0b10000000) != 0; }

    void setEnemyBlock(bool newValue)
    {
        Flags = (Flags & 0b10111111) | (static_cast<uint8_t>(newValue) << 6);
    }
    void setSwitchLayer(bool newValue)
    {
        Flags = (Flags & 0b01111111) | (static_cast<uint8_t>(newValue) << 7);
    }

} __attribute__((packed, aligned(1)));

/*!
 * \brief King's Field 2 metatile.
 * A metatile contains two tiles structures for one position:
 * one for the 1st layer and one for the 2nd layer.
 */
struct MetaTile
{
    Tile layer1;
    Tile layer2;
} __attribute__((packed, aligned(1)));

}

#endif // KF2_TILE_H
