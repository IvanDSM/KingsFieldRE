#include "mapviewer.h"
#include <cmath>
#include <iostream>
#include <QMenu>
#include <QMouseEvent>

const QString MapViewer::invalidElemWarning = QStringLiteral(
    "MapViewer: curElement set to something it shouldn't be (%1).");

void MapViewer::leaveEvent(QEvent *event)
{
    QWidget::leaveEvent(event);
    setMousePos(-2, -2);
    repaint();
}

void MapViewer::mouseMoveEvent(QMouseEvent *event)
{
    QWidget::mouseMoveEvent(event);
    processMouse(event);
    repaint();
}

void MapViewer::mousePressEvent(QMouseEvent *event)
{
    QWidget::mousePressEvent(event);
    processMouse(event);
}

void MapViewer::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    if (map == nullptr) return;

    painter.begin(this);

    painter.setWindow({0, 0, 80, 80});
    painter.drawImage(0, 0, mapImage);
    //painter.drawImage(QRectF(0, 0, 80, 80), mapImage, QRectF(0, 0, 80, 80));

    QRectF mouseRect{mousePos, QSizeF(1, 1)};
    painter.fillRect(mouseRect, Qt::white);

    painter.end();
}

void MapViewer::drawEntities()
{
    for (size_t i = 0; i < Map::entityInstancesSize; i++)
    {
        auto& entity = map->entityInstances[i];
        if (entity.EntityClass != 0xFF && static_cast<MapLayer>(entity.Layer) == curLayer)
            mapImage.setPixelColor(entity.WEXTilePos, entity.NSYTilePos, MapViewer::entityColor);
    }
}

void MapViewer::drawMap()
{
    QColor curColor;
    for (uint16_t y = 0; y < 80; y++)
    {
        for (uint16_t x = 0; x < 80; x++)
        {
            const auto& tile = map->getTile(x, y, static_cast<size_t>(curLayer));

            uint8_t value = 0;

            switch (curElement)
            {
                case MapElement::Elevation: value = tile.Elevation; break;
                case MapElement::CollisionIndex: value = tile.CollisionIndex; break;
                default:
                    KFMTError::warning(invalidElemWarning.arg(static_cast<unsigned>(curElement)));
            }

            curColor.setRed(tile.getSwitchLayer() ? value : 0);
            curColor.setGreen(value);
            curColor.setBlue(tile.getEnemyBlock() ? 127 : 0);

            mapImage.setPixelColor(x, y, curColor);
        }
    }
}

void MapViewer::drawObjects()
{
    for (size_t i = 0; i < Map::objectInstancesSize; i++)
    {
        auto& object = map->objectInstances[i];
        if (object.ID != KingsFieldII::ObjectID::None
            && static_cast<MapLayer>(object.TileLayer) == curLayer)
            mapImage.setPixelColor(object.WEXTilePos, object.NSYTilePos, MapViewer::objectColor);
    }
}

void MapViewer::drawVFX()
{
    for (size_t i = 0; i < Map::vfxInstancesSize; i++)
    {
        auto& vfx = map->vfxInstances[i];
        if (static_cast<MapLayer>(vfx.TileLayer) == curLayer)
            mapImage.setPixelColor(vfx.TileWEX, vfx.TileNSY, MapViewer::vfxColor);
    }
}

void MapViewer::updateMapImage()
{
    drawMap();
    drawEntities();
    drawObjects();
    drawVFX();
}

void MapViewer::processMouse(QMouseEvent *event)
{
    if (map == nullptr) return;

    uint8_t trueX = qRound((static_cast<float>(event->pos().x()) / size().width()) * 80);
    uint8_t trueZ = qRound((static_cast<float>(event->pos().y()) / size().height()) * 80);

    if (trueX < 0 || trueX > 79 || trueZ < 0 || trueZ > 79) return;

    setMousePos(trueX, trueZ);

    auto& tile = map->getTile(trueX, trueZ, static_cast<size_t>(curLayer));

    if ((event->buttons() & Qt::MouseButton::LeftButton) != 0) emit pickedTile(tile, trueX, trueZ);
}
