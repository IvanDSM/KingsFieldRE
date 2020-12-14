#include "mapviewer.h"
#include <QMouseEvent>
#include <iostream>

#if __GNUC__ < 7
// Workaround for GCC versions that don't support C++17
constexpr QColor MapViewer::entityColor;
constexpr QColor MapViewer::mouseColor;
constexpr QColor MapViewer::objectColor;
constexpr QColor MapViewer::selectionColor;
constexpr QColor MapViewer::vfxColor;
#endif

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
}

void MapViewer::mousePressEvent(QMouseEvent *event)
{
    QWidget::mousePressEvent(event);
    processMouse(event);
}

void MapViewer::mouseReleaseEvent(QMouseEvent *event)
{
    QWidget::mouseReleaseEvent(event);
    if (curMode == MapViewerMode::MODE_FILL)
    {
        auto normalizedSelection = selection.normalized();
        for (auto line = normalizedSelection.top(); line < normalizedSelection.bottom(); line++)
            for (auto column = normalizedSelection.left(); column <  normalizedSelection.right(); column++)
            {
                KingsField::Tile &tile = mapPtr->getTile(column, line);
                switch(curBrushElement)
                {
                    case MapElement::MAP_COLLISIONTHING:
                        switch (curLayer)
                        {
                            case MapLayer::LAYER_1:
                                tile.Layer1CollisionSomething = curBrush;
                                break;
                            case MapLayer::LAYER_2:
                                tile.Layer2CollisionSomething = curBrush;
                        }
                        break;
                    case MapElement::MAP_ELEV:
                        switch (curLayer)
                        {
                            case MapLayer::LAYER_1:
                                tile.Layer1Elev = curBrush;
                                break;
                            case MapLayer::LAYER_2:
                                tile.Layer2Elev = curBrush;
                        }
                        break;
                    case MapElement::MAP_ROTATION:
                        switch (curLayer)
                        {
                            case MapLayer::LAYER_1:
                                tile.Layer1Rotation = curBrush;
                                break;
                            case MapLayer::LAYER_2:
                                tile.Layer2Rotation = curBrush;
                        }
                        break;
                    case MapElement::MAP_TILEID:
                        switch (curLayer)
                        {
                            case MapLayer::LAYER_1:
                                tile.Layer1TileID = curBrush;
                                break;
                            case MapLayer::LAYER_2:
                                tile.Layer2TileID = curBrush;
                        }
                        break;
                    case MapElement::MAP_ZONEDELIMITER:
                        switch (curLayer)
                        {
                            case MapLayer::LAYER_1:
                                tile.Layer1ZoneDelimiter = curBrush;
                                break;
                            case MapLayer::LAYER_2:
                                tile.Layer2ZoneDelimiter = curBrush;
                        }
                }
            }

        selection = QRect(-2, -2, 0, 0);
        repaint();
    }
    else if (curMode == MapViewerMode::MODE_MOVE)
    {
        heldEntities.clear();
        heldObjects.clear();
        heldVFX.clear();
    }
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
    drawSelection();
    drawVFX();

    drawMouse();

    painter.end();
}

void MapViewer::drawEntities()
{
    painter.setPen(entityColor);

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
            byte green = 0;
            byte blue = 0;
            if (curLayer == MapLayer::LAYER_1)
            {
                switch (curElement)
                {
                    case MapElement::MAP_ELEV:
                        green = mapPtr->getTile(line, column).Layer1Elev;
                        break;
                    case MapElement::MAP_COLLISIONTHING:
                        green = mapPtr->getTile(line, column).Layer1CollisionSomething;
                        break;
                    default:
                        KFMTError::warning(invalidElementWarning.arg(static_cast<unsigned>(curElement)));
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
                        break;
                    default:
                        KFMTError::warning(invalidElementWarning.arg(static_cast<unsigned>(curElement)));
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
    painter.setPen(mouseColor);
    painter.drawPoint(mousePos);
}

void MapViewer::drawObjects()
{
    painter.setPen(MapViewer::objectColor);

    for (auto objInstance : mapPtr->getObjectInstanceDeclarations())
        if (objInstance.ObjectID != KingsField::ObjectID::None &&
            ((objInstance.TileLayer == 1 && curLayer == MapLayer::LAYER_1) ||
             (objInstance.TileLayer == 2 && curLayer == MapLayer::LAYER_2)))
            painter.drawPoint(objInstance.WEXTilePos, objInstance.NSYTilePos);
}

void MapViewer::drawSelection()
{
    painter.fillRect(selection, selectionColor);
}

void MapViewer::drawVFX()
{
    painter.setPen(vfxColor);

    for (auto vfxInstance : mapPtr->getVFXInstanceDeclarations())
    {
        if (vfxInstance.TileLayer == static_cast<byte>(curLayer))
            painter.drawPoint(vfxInstance.TileWEX, vfxInstance.TileNSY);
    }
}

void MapViewer::processMouse(QMouseEvent *event)
{
    int trueX = qRound((static_cast<float>(event->pos().x()) / size().width()) * 80);
    int trueY = qRound((static_cast<float>(event->pos().y()) / size().height()) * 80);

    if (trueX < 0 || trueX > 79 || trueY < 0 || trueY > 79)
        return;

    setMousePos(trueX, trueY);

    if (event->buttons() != Qt::NoButton)
    {
        if (curMode == MapViewerMode::MODE_POKE)
        {
            size_t index = 0;
            for (const auto &entityInstance : mapPtr->getEntityInstances())
            {
                if (trueX == entityInstance.WEXTilePos && trueY == entityInstance.NSYTilePos &&
                    ((entityInstance.Layer == 1 && curLayer == MapLayer::LAYER_1) ||
                     (entityInstance.Layer == 2 && curLayer == MapLayer::LAYER_2)))
                    emit entityInstanceHovered(index);
                index++;
            }

            index = 0;
            for (const auto &objInstance : mapPtr->getObjectInstanceDeclarations())
            {
                if (trueX == objInstance.WEXTilePos && trueY == objInstance.NSYTilePos &&
                    ((objInstance.TileLayer == 1 && curLayer == MapLayer::LAYER_1) ||
                     (objInstance.TileLayer == 2 && curLayer == MapLayer::LAYER_2)))
                    emit objectInstanceHovered(index);
                index++;
            }

            for (const auto &vfx : vfxAt(trueX, trueY))
                emit vfxInstanceHovered(vfx);

            auto tile = mapPtr->getTile(trueX, trueY);
            switch(curLayer)
            {
                case MapLayer::LAYER_1:
                    emit hoveredTileInfo(tile.Layer1Elev,
                                         tile.Layer1Rotation,
                                         tile.Layer1CollisionSomething,
                                         tile.Layer1ZoneDelimiter,
                                         tile.Layer1TileID);
                    break;
                case MapLayer::LAYER_2:
                    emit hoveredTileInfo(tile.Layer2Elev,
                                         tile.Layer2Rotation,
                                         tile.Layer2CollisionSomething,
                                         tile.Layer2ZoneDelimiter,
                                         tile.Layer2TileID);
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
                        case MapElement::MAP_ROTATION:
                            mapPtr->getTile(trueX, trueY).Layer1Rotation = curBrush;
                            break;
                        case MapElement::MAP_TILEID:
                            mapPtr->getTile(trueX, trueY).Layer1TileID = curBrush;
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
                        case MapElement::MAP_ROTATION:
                            mapPtr->getTile(trueX, trueY).Layer2Rotation = curBrush;
                            break;
                        case MapElement::MAP_TILEID:
                            mapPtr->getTile(trueX, trueY).Layer2TileID = curBrush;
                            break;
                        case MapElement::MAP_ZONEDELIMITER:
                            mapPtr->getTile(trueX, trueY).Layer2ZoneDelimiter = curBrush;
                    }
            }
        }
        else if (curMode == MapViewerMode::MODE_FILL)
        {
            if (selection.x() < 0)
            {
                selection.setTopLeft(mousePos);
                selection.setBottomRight(mousePos);
            }
            else
                selection.setBottomRight(mousePos);
        }
        else if (curMode == MapViewerMode::MODE_MOVE)
        {
            if (event->type() == QEvent::Type::MouseMove)
            {
                if (mousePos.x() >= 0 && mousePos.y() >= 0)
                {
                    for (auto entity : heldEntities)
                    {
                        mapPtr->getEntityInstance(entity).WEXTilePos = mousePos.x();
                        mapPtr->getEntityInstance(entity).NSYTilePos = mousePos.y();
                    }

                    for (auto object : heldObjects)
                    {
                        mapPtr->getObjectInstance(object).WEXTilePos = mousePos.x();
                        mapPtr->getObjectInstance(object).NSYTilePos = mousePos.y();
                    }

                    for (auto vfx : heldVFX)
                    {
                        mapPtr->getVFXInstance(vfx).TileWEX = mousePos.x();
                        mapPtr->getVFXInstance(vfx).TileNSY = mousePos.y();
                    }
                }
            }
            else if (event->type() == QEvent::Type::MouseButtonPress)
            {
                heldEntities = entitiesAt(trueX, trueY);
                heldObjects = objectsAt(trueX, trueY);
                heldVFX = objectsAt(trueX, trueY);
            }
        }
    }

    repaint();
}

std::vector<size_t> MapViewer::entitiesAt(byte x, byte y)
{
    size_t index = 0;
    std::vector<size_t> entityIndices;

    for (auto entityInstance : mapPtr->getEntityInstances())
    {
        if (x == entityInstance.WEXTilePos && y == entityInstance.NSYTilePos &&
            ((entityInstance.Layer == 1 && curLayer == MapLayer::LAYER_1) ||
             (entityInstance.Layer == 2 && curLayer == MapLayer::LAYER_2)))
            entityIndices.push_back(index);
        index++;
    }

    return entityIndices;
}

std::vector<size_t> MapViewer::objectsAt(byte x, byte y)
{
    size_t index = 0;
    std::vector<size_t> objectIndices;
    for (auto objInstance : mapPtr->getObjectInstanceDeclarations())
    {
        if (x == objInstance.WEXTilePos && y == objInstance.NSYTilePos &&
            ((objInstance.TileLayer == 1 && curLayer == MapLayer::LAYER_1) ||
             (objInstance.TileLayer == 2 && curLayer == MapLayer::LAYER_2)))
            objectIndices.push_back(index);
        index++;
    }

    return objectIndices;
}

std::vector<size_t> MapViewer::vfxAt(byte x, byte y)
{
    size_t index = 0;
    std::vector<size_t> vfxIndices;
    for (auto vfxInstance : mapPtr->getVFXInstanceDeclarations())
    {
        if (x == vfxInstance.TileWEX && y == vfxInstance.TileNSY &&
            vfxInstance.TileLayer == static_cast<byte>(curLayer))
            vfxIndices.push_back(index);
        index++;
    }

    return vfxIndices;
}
