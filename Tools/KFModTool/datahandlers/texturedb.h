#ifndef TEXTUREDB_H
#define TEXTUREDB_H

#include "datahandlers/kfmtdatahandler.h"
#include <QImage>
#include <QPainter>

class TextureDB : public KFMTDataHandler
{
public:
    enum TexDBType
    {
        RTIM,
        TIM
    };
    
    /*!
     * \brief Structure for representing a single texture (CLUT + Pixel Data).
     */
    struct Texture;

    enum class PixelMode
    {
        CLUT4Bit = 0,
        CLUT8Bit = 1,
        Direct15Bit = 2,
        Direct24Bit = 3,
        Mixed = 4
    };

    explicit TextureDB(KFMTFile& file_);

    QPoint getFramebufferCoordinate(size_t textureIndex);
    Texture &getTexture(size_t textureIndex);
    size_t getTextureCount() const { return textures.size(); }
    void replaceTexture(QImage& newTexture, size_t textureIndex, Qt::TransformationMode mode);
    void saveChanges() override;

private:
    
    void loadRTIM();
    void loadTIM();
    
    bool readCLUT(QDataStream &stream, Texture &targetTex);
    void readPixelData(QDataStream &stream, Texture &targetTex);
    
    void writeRTIM();
    void writeTIM();
        
    static void writeCLUT(QDataStream &stream, const Texture &targetTex, TexDBType type);
    static void writePixelData(QDataStream& stream, const Texture& targetTex, TexDBType type);

    std::vector<Texture> textures;
    TexDBType type;
};

struct TextureDB::Texture
{
    // Info
    PixelMode pMode;
    bool cf = true;
    QPoint framebufferCoordinate {0,0};
    
    // CLUT Data
    uint32_t clutSize;
    uint16_t clutVramX;
    uint16_t clutVramY;
    uint16_t clutWidth;
    uint16_t clutHeight;
    QVector<QRgb> clutColorTable {};
    
    // Pixel Data
    uint32_t pxDataSize;
    uint16_t pxVramX;
    uint16_t pxVramY;
    uint16_t pxWidth;
    uint16_t pxHeight;
    QImage image;
    
    std::vector<uint16_t> getCLUTEntries() const;
};

#endif // TEXTUREDB_H
