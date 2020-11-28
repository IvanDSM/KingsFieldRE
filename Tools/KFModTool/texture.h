#ifndef TEXTURE_H
#define TEXTURE_H

#include "tfile.h"
#include <QImage>
#include <QPainter>

class Texture
{
public:
    explicit Texture(TFile &tFile, unsigned int index, QString name);

    enum class PixelMode {
        CLUT4Bit = 0,
        CLUT8Bit = 1,
        Direct15Bit = 2,
        Dir24Bit = 3,
        Mixed = 4
    };
    
    QPoint &getFramebufferCoordinate()
    {
        return framebufferCoordinate;
    }
    
    QImage &getImage() { return texture; }
    

private:
    
    void loadRTIM(const QByteArray &file);
    void loadTIM(const QByteArray &file);
    
    struct CLUT
    {
        quint32 bnum = 0;
        quint16 dx = 0;
        quint16 dy = 0;
        quint16 w = 0;
        quint16 h = 0;
        std::vector<QColor> clut {};

        CLUT() = default;
        CLUT(quint32 _bnum, quint16 _dx, quint16 _dy, quint16 _w, quint16 _h, PixelMode pColor) : 
            bnum(_bnum), dx(_dx), dy(_dy), h(_h)
        {
            if (pColor == PixelMode::CLUT4Bit)
                w = _w * 4;
            else if (pColor == PixelMode::CLUT8Bit)
                w = _w * 2;
            clut.reserve((_bnum - 12) / 2);
        }

        void addColor(quint16 clutEntry)
        {
            const quint8 r = (clutEntry & 31) * 8;
            const quint8 g = ((clutEntry >> 5) & 31) * 8;
            const quint8 b = ((clutEntry >> 10) & 31) * 8;
            const quint8 a = ((clutEntry >> 15) & 1 & (r | g | b)) * 255;
            clut.emplace_back(r, g, b, a);
        }

        const QColor &getColor(quint8 index)
        {
            return clut.at(index);
        }
    };

    QImage texture {};
    QPainter texPainter {};

    // TIM Header
    PixelMode pMode;
    bool cf;
    std::unique_ptr<CLUT> clut {nullptr};

    // Pixel buffer
    QPoint framebufferCoordinate {0,0};
};

#endif // TEXTURE_H
