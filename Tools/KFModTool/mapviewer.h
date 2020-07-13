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
    explicit MapViewer(QWidget *parent = nullptr) : QWidget(parent)
    {
        setMouseTracking(true);
    }

    void setDrawZoneDelimiters(bool shouldDraw)
    {
        drawZoneDelimiters = shouldDraw;
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

signals:
    void entityInstanceHovered(byte instance);
    void objectInstanceHovered(size_t instance);

public slots:
    void leaveEvent(QEvent *event) override
    {
        QWidget::leaveEvent(event);
        mousePos = {-1,-1};
        repaint();
    }

    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    void drawEntities();
    void drawMap();
    void drawMouse();
    void drawObjects();

    void processMouse(QMouseEvent *event);

    bool drawZoneDelimiters = false;
    MapLayer curLayer = MapLayer::LAYER_1;
    QPainter painter;
    QPoint mousePos = QPoint(39, 39);
    std::shared_ptr<Map> mapPtr;

};

#endif // MAPVIEWER_H