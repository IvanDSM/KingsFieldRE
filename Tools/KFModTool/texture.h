#ifndef TEXTURE_H
#define TEXTURE_H

#include <QObject>
#include <QImage>
#include <QPainter>

class Texture : public QObject
{
    Q_OBJECT
public:
    explicit Texture (QObject *parent = nullptr) : QObject(parent)
    {

    }

    enum class PMode {
        CLUT_4BIT = 0,
        CLUT_8BIT = 1,
        DIR_15BIT = 2,
        DIR_24BIT = 3,
        MIXED = 4
    };

signals:

protected:
    struct CLUT
    {
        quint32 bnum;
        quint16 dx;
        quint16 dy;
        quint16 w;
        quint16 h;
        std::vector<QColor> clut;

        CLUT() = default;

        CLUT(quint32 _bnum, quint16 _dx, quint16 _dy, quint16 _w, quint16 _h, PMode pColor) : bnum(_bnum),
            dx(_dx), dy(_dy), h(_h)
        {
            if (pColor == PMode::CLUT_4BIT)
                w = _w * 4;
            else if (pColor == PMode::CLUT_8BIT)
                w = _w * 2;
            clut.reserve(_bnum);
        }

        void addColor(quint16 clutEntry)
        {
            const quint8 r = clutEntry & 31,
                         g = (clutEntry >> 5) & 31,
                         b = (clutEntry >> 10) & 31,
                         a = ((clutEntry >> 15) & 1 & (r | g | b)) * 255;
            clut.emplace_back(r, g, b, a);
        }

        const QColor &getColor(quint8 index)
        {
            return clut.at(index);
        }
    };

    QImage texture;
    QPainter texPainter;

    // TIM Header
    quint32 id;
    quint32 flags;
    PMode pMode;
    bool cf;
    CLUT clut;

    // Pixel buffer
    std::vector<quint8> clutPixelBuffer;
};

#endif // TEXTURE_H
