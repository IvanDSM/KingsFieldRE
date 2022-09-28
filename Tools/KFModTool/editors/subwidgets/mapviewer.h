#ifndef MAPVIEWER_H
#define MAPVIEWER_H

#include "datahandlers/map.h"
#include "datahandlers/tileseticons.h"
#include <QPainter>
#include <QWidget>

class MapViewer : public QWidget
{
    Q_OBJECT
public:
    enum class MapLayer
    {
        Layer1 = 1,
        Layer2 = 2
    };

    enum class MapElement
    {
        CollisionIndex,
        Elevation,
        Rotation,
        TileID,
        Flags
    };

    explicit MapViewer(QWidget* parent = nullptr) : QWidget(parent) { setMouseTracking(true); }

    void refreshMapViewer()
    {
        updateMapImage();
        repaint();
    }

    void setBrush(uint8_t brush)
    {
        curBrush = brush;
    }

    void setBrushElement(MapElement element)
    {
        curBrushElement = element;
    }

    void setElement(MapElement element)
    {
        curElement = element;
        repaint();
    }

    void setLayer(MapLayer layer)
    {
        curLayer = layer;
        updateMapImage();
        repaint();
    }

    void setMap(Map& map_)
    {
        map = &map_;
        updateMapImage();
    }

    void setTileset(const TilesetIcons& icons_) { icons = &icons_; }

signals:
    void curMousePosChanged(qint8 x, qint8 y);
    void pickedTile(KF2::Tile& tile, uint8_t x, uint8_t y);

public slots:
    void leaveEvent(QEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    void drawEntities();
    void drawMap();
    void drawMouse();
    void drawObjects();
    void drawVFX();

    void updateMapImage();

    void setMousePos(qint8 trueX, qint8 trueY)
    {
        mousePos.setX(trueX);
        mousePos.setY(trueY);
    }
    void processMouse(QMouseEvent* event);

    Map* map;
    const TilesetIcons* icons;

    // Internal stuff
    uint8_t curBrush = 127;
    MapElement curBrushElement = MapElement::CollisionIndex;
    MapElement curElement = MapElement::CollisionIndex;
    MapLayer curLayer = MapLayer::Layer2;
    QImage mapImage{{80, 80}, QImage::Format::Format_RGB888};
    QPainter painter;
    QPoint mousePos{39, 39};
    QRect selection{-2, -2, 0, 0};
    std::vector<size_t> heldEntities;
    std::vector<size_t> heldObjects;
    std::vector<size_t> heldVFX;

    // Constants
    static constexpr QColor entityColor{255, 0, 0};
    static constexpr QColor objectColor{0, 255, 255};
    static constexpr QColor selectionColor{255, 255, 255, 127};
    static constexpr QColor vfxColor{230, 126, 34};

    static const QString invalidElemWarning;
};

#endif // MAPVIEWER_H
