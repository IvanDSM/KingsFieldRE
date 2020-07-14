#include "mapviewer.h"
#include <QMouseEvent>
#include <iostream>

void MapViewer::mouseMoveEvent(QMouseEvent *event)
{
    QWidget::mouseMoveEvent(event);
    processMouse(event);
}

void MapViewer::mousePressEvent(QMouseEvent *event)
{
    QWidget::mousePressEvent(event);
    processMouse(event);
}

void MapViewer::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QRect window(-1, -1, 81, 81);
    painter.begin(this);
    painter.setWindow(window);
    drawMap();
    drawEntities();
    drawObjects();
    drawMouse();
    painter.end();
}

void MapViewer::drawEntities()
{
    painter.setPen(QColor(255, 0, 0));
    for (auto entityInstance : mapPtr->getEntityInstances())
        if (entityInstance.EntityClass != 0xFF &&
            ((entityInstance.Layer == 1 && curLayer == MapLayer::LAYER_1) ||
             (entityInstance.Layer == 2 && curLayer == MapLayer::LAYER_2)))
            painter.drawPoint(entityInstance.WEXTilePos, entityInstance.NSYTilePos);
}

void MapViewer::drawMap()
{
    QColor curColor;
    for (unsigned short line = 0; line < 80; line++)
    {
        for (unsigned short column = 0; column < 80; column++)
        {
            byte green = 0, blue = 0;
            if (curLayer == MapLayer::LAYER_1)
            {
                switch (curElement)
                {
                    case MapElement::MAP_ELEV:
                        green = mapPtr->getTile(line, column).Layer1Elev;
                        break;
                    case MapElement::MAP_COLLISIONTHING:
                        green = mapPtr->getTile(line, column).Layer1CollisionSomething;
                }
                if (drawZoneDelimiters)
                    blue = mapPtr->getTile(line, column).Layer1ZoneDelimiter;
            }
            else
            {
                switch (curElement)
                {
                    case MapElement::MAP_ELEV:
                        green = mapPtr->getTile(line, column).Layer2Elev;
                        break;
                    case MapElement::MAP_COLLISIONTHING:
                        green = mapPtr->getTile(line, column).Layer2CollisionSomething;
                }
                if (drawZoneDelimiters)
                    blue = mapPtr->getTile(line, column).Layer2ZoneDelimiter;
            }
            curColor.setRgb(0, green, blue);
            painter.setPen(curColor);
            painter.drawPoint(line, column);
        }
    }
}

void MapViewer::drawMouse()
{
    painter.setPen(QColor(0xFF, 0xC8, 0x57));
    painter.drawPoint(mousePos);
}

void MapViewer::drawObjects()
{
    QColor curColor(0, 255, 255);

    painter.setPen(curColor);

    for (auto objInstance : mapPtr->getObjectInstanceDeclarations())
        if (objInstance.ItemID != KingsField::ItemID::None &&
            ((objInstance.TileLayer == 1 && curLayer == MapLayer::LAYER_1) ||
             (objInstance.TileLayer == 2 && curLayer == MapLayer::LAYER_2)))
            painter.drawPoint(objInstance.WEXTilePos, objInstance.NSYTilePos);
}

void MapViewer::processMouse(QMouseEvent *event)
{
    int trueX = qRound((static_cast<float>(event->pos().x()) / size().width()) * 80);
    int trueY = qRound((static_cast<float>(event->pos().y()) / size().height()) * 80);

    if (trueX < 0 || trueX > 79 || trueY < 0 || trueY > 79)
        return;

    mousePos.setX(trueX);
    mousePos.setY(trueY);

    if (event->buttons() != Qt::NoButton)
    {
        if (curMode == MapViewerMode::MODE_POKE)
        {
            size_t entityIndex = 0;
            for (auto entityInstance : mapPtr->getEntityInstances())
            {
                if (trueX == entityInstance.WEXTilePos && trueY == entityInstance.NSYTilePos &&
                    ((entityInstance.Layer == 1 && curLayer == MapLayer::LAYER_1) ||
                     (entityInstance.Layer == 2 && curLayer == MapLayer::LAYER_2)))
                    emit entityInstanceHovered(entityIndex);
                entityIndex++;
            }

            entityIndex = 0;
            for (auto objInstance : mapPtr->getObjectInstanceDeclarations())
            {
                if (trueX == objInstance.WEXTilePos && trueY == objInstance.NSYTilePos &&
                    ((objInstance.TileLayer == 1 && curLayer == MapLayer::LAYER_1) ||
                     (objInstance.TileLayer == 2 && curLayer == MapLayer::LAYER_2)))
                    emit objectInstanceHovered(entityIndex);
                entityIndex++;
            }

            auto tile = mapPtr->getTile(trueX, trueY);
            switch(curLayer)
            {
                case MapLayer::LAYER_1:
                    emit hoveredTileInfo(tile.Layer1Elev,
                                         tile.Layer1Rotation,
                                         tile.Layer1CollisionSomething,
                                         tile.Layer1ZoneDelimiter);
                    break;
                case MapLayer::LAYER_2:
                    emit hoveredTileInfo(tile.Layer2Elev,
                                         tile.Layer2Rotation,
                                         tile.Layer2CollisionSomething,
                                         tile.Layer2ZoneDelimiter);
            }
        }
        else if (curMode == MapViewerMode::MODE_PAINT)
        {
            switch(curLayer)
            {
                case MapLayer::LAYER_1:
                    switch(curBrushElement)
                    {
                        case MapElement::MAP_COLLISIONTHING:
                            mapPtr->getTile(trueX, trueY).Layer1CollisionSomething = curBrush;
                            break;
                        case MapElement::MAP_ELEV:
                            mapPtr->getTile(trueX, trueY).Layer1Elev = curBrush;
                            break;
                        case MapElement::MAP_ZONEDELIMITER:
                            mapPtr->getTile(trueX, trueY).Layer1ZoneDelimiter = curBrush;
                    }
                    break;
                case MapLayer::LAYER_2:
                    switch(curBrushElement)
                    {
                        case MapElement::MAP_COLLISIONTHING:
                            mapPtr->getTile(trueX, trueY).Layer2CollisionSomething = curBrush;
                            break;
                        case MapElement::MAP_ELEV:
                            mapPtr->getTile(trueX, trueY).Layer2Elev = curBrush;
                            break;
                        case MapElement::MAP_ZONEDELIMITER:
                            mapPtr->getTile(trueX, trueY).Layer2ZoneDelimiter = curBrush;
                    }
            }
            mapPtr->setChanged();
        }
    }

    repaint();
}
