#ifndef TEXTUREDB_H
#define TEXTUREDB_H

#include "tfile.h"
#include <QImage>
#include <QPainter>

class TextureDB
{
public:
    explicit TextureDB(TFile &tFile, unsigned int index);

    enum class PixelMode {
        CLUT4Bit = 0,
        CLUT8Bit = 1,
        Direct15Bit = 2,
        Dir24Bit = 3,
        Mixed = 4
    };
    
    QPoint getFramebufferCoordinate(size_t textureIndex);
    
    QImage &getTexture(size_t textureIndex);
    size_t getTextureCount() { return textures.size(); }
    

private:
    
    /*!
     * \brief Structure for representing a TIM-style CLUT.
     */
    struct CLUT;
    
    /*!
     * \brief Structure for representing a single texture (CLUT + Pixel Data).
     */
    struct Texture;
    
    void loadRTIM(const QByteArray &file);
    void loadTIM(const QByteArray &file);
    
    void readCLUT(QDataStream &stream, Texture &targetTex, bool isRtim = false);
    void readPixelData(QDataStream &stream, Texture &targetTex, bool isRtim = false);
    
    std::vector<Texture> textures;
};

struct TextureDB::CLUT
{
    uint32_t bnum = 0;
    uint16_t dx = 0;
    uint16_t dy = 0;
    uint16_t w = 0;
    uint16_t h = 0;
    std::vector<QColor> clut {};
    
    CLUT() = default;
    CLUT(uint32_t _bnum, uint16_t _dx, uint16_t _dy, uint16_t _w, uint16_t _h, PixelMode pColor) : 
            bnum(_bnum), dx(_dx), dy(_dy), h(_h)
    {
        if (pColor == PixelMode::CLUT4Bit)
        {
            w = _w * 4;
            clut.reserve(16);
        }
        else if (pColor == PixelMode::CLUT8Bit)
        {
            w = _w * 2;
            clut.reserve(255);
        }
    }
    
    void addColor(uint16_t clutEntry)
    {
        const uint8_t r = (clutEntry & 31) * 8;
        const uint8_t g = ((clutEntry >> 5) & 31) * 8;
        const uint8_t b = ((clutEntry >> 10) & 31) * 8;
        const uint8_t a = 255 - (((clutEntry >> 15) & 1 & (r || g || b)) * 127);
        clut.emplace_back(r, g, b, a);
    }
    
    const QColor &getColor(uint8_t index)
    {
        return clut.at(index);
    }
};

struct TextureDB::Texture
{
    // Info
    PixelMode pMode;
    bool cf;
    QPoint framebufferCoordinate {0,0};
    
    // CLUT + Pixel Data
    std::unique_ptr<CLUT> clut;
    QImage image;
};

#endif // TEXTUREDB_H
