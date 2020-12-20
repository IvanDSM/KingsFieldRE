#ifndef TEXTUREDB_H
#define TEXTUREDB_H

#include "../common/tfile.h"
#include <QImage>
#include <QPainter>

class TextureDB
{
public:
    enum TexDBType
    {
        RTIM,
        MIX,
        TIM
    };
    
    /*!
     * \brief Structure for representing a single texture (CLUT + Pixel Data).
     */
    struct Texture;
    
    enum class PixelMode {
        CLUT4Bit = 0,
        CLUT8Bit = 1,
        Direct15Bit = 2,
        Dir24Bit = 3,
        Mixed = 4
    };
    
    explicit TextureDB(TFile &tFile_, unsigned int index);
    
    QPoint getFramebufferCoordinate(size_t textureIndex);
    Texture &getTexture(size_t textureIndex);
    size_t getTextureCount() { return textures.size(); }
    void replaceTexture(QImage &newTexture, size_t textureIndex, bool smooth);
    void writeChanges();
    
private:
    
    void loadRTIM(const QByteArray &file);
    void loadTIM(const QByteArray &file);
    
    void readCLUT(QDataStream &stream, Texture &targetTex);
    void readPixelData(QDataStream &stream, Texture &targetTex);
        
    TexDBType type;
    
    TFile &tFile;
    unsigned int fileIndex;
    
    std::vector<Texture> textures;
    QString fileId;
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
    
    std::vector<uint16_t> getCLUTEntries();
};

#endif // TEXTUREDB_H
