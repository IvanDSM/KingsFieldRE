#ifndef MAPVIEWER_H
#define MAPVIEWER_H

#include <QWidget>
#include <QPainter>
#include "map.h"



class MapViewer : public QWidget
{
    Q_OBJECT
public:
    enum class MapLayer
    {
        LAYER_1,
        LAYER_2
    };

    enum class MapElement
    {
        MAP_COLLISIONTHING,
        MAP_ELEV,
        MAP_ROTATION,
        MAP_TILEID,
        MAP_ZONEDELIMITER
    };

    enum class MapViewerMode
    {
        MODE_POKE,
        MODE_PAINT,
        MODE_FILL,
        MODE_MOVE
    };

    explicit MapViewer(QWidget *parent = nullptr) : QWidget(parent)
    {
        setMouseTracking(true);
    }

    void setDrawZoneDelimiters(bool shouldDraw)
    {
        drawZoneDelimiters = shouldDraw;
        repaint();
    }

    void setBrush(byte brush)
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
        repaint();
    }

    void setMap(std::shared_ptr<Map> newMap)
    {
        mapPtr = newMap;
        repaint();
    }

    void setMode(MapViewerMode mode)
    {
        curMode = mode;
    }

signals:
    void curMousePosChanged(qint8 x, qint8 y);
    void entityInstanceHovered(byte instance);
    void hoveredTileInfo(byte elevation, byte rotation, byte collisionThing, byte zoneDelimiter,
                         byte tileId);
    void objectInstanceHovered(size_t instance);

public slots:
    void leaveEvent(QEvent *event) override
    {
        QWidget::leaveEvent(event);
        setMousePos(-2, -2);
        repaint();
    }

    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    void drawEntities();
    void drawMap();
    void drawMouse();
    void drawObjects();
    void drawSelection();

    void setMousePos(qint8 trueX, qint8 trueY)
    {
        mousePos.setX(trueX);
        mousePos.setY(trueY);
        emit curMousePosChanged(trueX, trueY);
    }
    void processMouse(QMouseEvent *event);

    bool drawZoneDelimiters = false;
    byte curBrush = 127;
    MapElement curBrushElement = MapElement::MAP_COLLISIONTHING;
    MapElement curElement = MapElement::MAP_COLLISIONTHING;
    MapLayer curLayer = MapLayer::LAYER_1;
    MapViewerMode curMode = MapViewerMode::MODE_POKE;
    QPainter painter;
    QPoint mousePos = QPoint(39, 39);
    QRect selection = QRect(-2,-2,0,0);
    std::shared_ptr<Map> mapPtr;
    std::vector<size_t> heldEntities;
    std::vector<size_t> heldObjects;
};

#endif // MAPVIEWER_H
